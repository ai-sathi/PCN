#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include <iostream>
#include <iomanip>
using namespace ns3;

int main(int argc, char *argv[])
{
    uint32_t nNodes = 6;
    double simTime = 20.0;
    double dataRateMbps = 1.0;
    CommandLine cmd(__FILE__);
    cmd.AddValue("nNodes", "Number of Wi-Fi nodes (minimum 2)", nNodes);
    cmd.AddValue("simTime", "Simulation duration in seconds", simTime);
    cmd.AddValue("dataRateMbps", "UDP source rate in Mbps", dataRateMbps);
    cmd.Parse(argc, argv);
    if (nNodes < 2) { std::cerr << "Need at least 2 nodes\n"; return 1; }

    NodeContainer nodes; nodes.Create(nNodes);
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());
    WifiHelper wifi;
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
        "DataMode", StringValue("OfdmRate6Mbps"),
        "ControlMode", StringValue("OfdmRate6Mbps"));
    WifiMacHelper mac;
    mac.SetType("ns3::AdhocWifiMac");
    NetDeviceContainer devices = wifi.Install(phy, mac, nodes);

    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(nodes);
    for (uint32_t i=0; i<nNodes; ++i) {
        auto m = nodes.Get(i)->GetObject<MobilityModel>();
        m->SetPosition(Vector(10.0*i, 0.0, 0.0));
    }

    InternetStackHelper internet; internet.Install(nodes);
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    uint16_t port=9000;
    PacketSinkHelper sink("ns3::UdpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(),port));
    auto sinkApps=sink.Install(nodes.Get(nNodes-1));
    sinkApps.Start(Seconds(0.5)); sinkApps.Stop(Seconds(simTime));

    OnOffHelper source("ns3::UdpSocketFactory",
        InetSocketAddress(interfaces.GetAddress(nNodes-1),port));
    uint64_t rate = static_cast<uint64_t>(dataRateMbps*1000000.0);
    source.SetAttribute("DataRate", DataRateValue(DataRate(rate)));
    source.SetAttribute("PacketSize", UintegerValue(512));
    source.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    source.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    auto sourceApps=source.Install(nodes.Get(0));
    sourceApps.Start(Seconds(1.0)); sourceApps.Stop(Seconds(simTime-1.0));

    phy.EnablePcap("wifi-basic", devices, true);
    FlowMonitorHelper fm; auto monitor=fm.InstallAll();
    Simulator::Stop(Seconds(simTime)); Simulator::Run(); monitor->CheckForLostPackets();

    std::cout << "\n=== WI-FI PERFORMANCE ===\n";
    std::cout << "Nodes=" << nNodes << " UDP rate=" << dataRateMbps << " Mbps\n";
    auto classifier=DynamicCast<Ipv4FlowClassifier>(fm.GetClassifier());
    for (const auto &x : monitor->GetFlowStats()) {
        auto tuple=classifier->FindFlow(x.first);
        if (tuple.protocol != 17 || x.second.txPackets==0) continue;
        const auto &s=x.second;
        double duration=(s.timeLastRxPacket-s.timeFirstTxPacket).GetSeconds();
        double throughput=(duration>0)?(s.rxBytes*8.0/duration/1e6):0.0;
        double delay=(s.rxPackets>0)?(s.delaySum.GetSeconds()*1000.0/s.rxPackets):0.0;
        uint64_t lost=(s.txPackets>s.rxPackets)?s.txPackets-s.rxPackets:0;
        double pdr=100.0*s.rxPackets/s.txPackets;
        std::cout << "Tx=" << s.txPackets << " Rx=" << s.rxPackets
                  << " Lost estimate=" << lost << " PDR=" << pdr << "%\n";
        std::cout << "Throughput=" << throughput << " Mbps AvgDelay=" << delay << " ms\n";
    }
    monitor->SerializeToXmlFile("wifi-flowmon.xml",true,true);
    std::cout << "PCAP prefix: wifi-basic; FlowMonitor file: wifi-flowmon.xml\n";
    Simulator::Destroy(); return 0;
}
