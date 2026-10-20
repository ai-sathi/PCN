#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include <iostream>
using namespace ns3;

int main(int argc, char *argv[])
{
    std::string tcpType = "ns3::TcpNewReno";
    std::string bottleneckRate = "2Mbps";
    double simTime = 20.0;
    CommandLine cmd(__FILE__);
    cmd.AddValue("tcpType", "TCP TypeId, e.g. ns3::TcpNewReno or ns3::TcpCubic (if supported)", tcpType);
    cmd.AddValue("bottleneckRate", "Bottleneck data rate", bottleneckRate);
    cmd.AddValue("simTime", "Simulation duration", simTime);
    cmd.Parse(argc, argv);

    // Fail with a readable message if the requested congestion-control TypeId is absent.
    TypeId tid;
    if (!TypeId::LookupByNameFailSafe(tcpType, &tid)) {
        std::cerr << "ERROR: TCP type '" << tcpType << "' is not registered in this NS-3 build.\n";
        std::cerr << "Use ns3::TcpNewReno, or check whether TcpCubic/TcpBbr is supported by your version.\n";
        return 1;
    }
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(tid));

    NodeContainer n; n.Create(4); // source, router 0, router 1, destination
    InternetStackHelper internet; internet.Install(n);

    PointToPointHelper access;
    access.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    access.SetChannelAttribute("Delay", StringValue("2ms"));
    PointToPointHelper bottleneck;
    bottleneck.SetDeviceAttribute("DataRate", StringValue(bottleneckRate));
    bottleneck.SetChannelAttribute("Delay", StringValue("10ms"));
    bottleneck.SetQueue("ns3::DropTailQueue<Packet>", "MaxSize", StringValue("50p"));

    NetDeviceContainer d0 = access.Install(n.Get(0), n.Get(1));
    NetDeviceContainer d1 = bottleneck.Install(n.Get(1), n.Get(2));
    NetDeviceContainer d2 = access.Install(n.Get(2), n.Get(3));
    Ipv4AddressHelper ip;
    ip.SetBase("10.1.1.0","255.255.255.0"); ip.Assign(d0);
    ip.SetBase("10.1.2.0","255.255.255.0"); ip.Assign(d1);
    ip.SetBase("10.1.3.0","255.255.255.0"); Ipv4InterfaceContainer dst = ip.Assign(d2);
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    uint16_t port=5000;
    PacketSinkHelper sink("ns3::TcpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(),port));
    auto sinkApp=sink.Install(n.Get(3)); sinkApp.Start(Seconds(0)); sinkApp.Stop(Seconds(simTime));

    OnOffHelper source("ns3::TcpSocketFactory", InetSocketAddress(dst.GetAddress(1),port));
    source.SetAttribute("DataRate", StringValue("5Mbps"));
    source.SetAttribute("PacketSize", UintegerValue(1024));
    source.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    source.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    auto srcApp=source.Install(n.Get(0)); srcApp.Start(Seconds(1)); srcApp.Stop(Seconds(simTime-1));

    bottleneck.EnablePcap("tcpcc-bottleneck",d1,true);
    FlowMonitorHelper fm; auto monitor=fm.InstallAll();
    Simulator::Stop(Seconds(simTime)); Simulator::Run(); monitor->CheckForLostPackets();
    std::cout << "\nTCP congestion control: " << tcpType << "\n";
    std::cout << "Bottleneck: " << bottleneckRate << "\n";
    Ptr<Ipv4FlowClassifier> classifier=DynamicCast<Ipv4FlowClassifier>(fm.GetClassifier());
    for (const auto &x: monitor->GetFlowStats()) {
        auto tuple=classifier->FindFlow(x.first);
        if (tuple.protocol!=6 || x.second.txPackets==0) continue;
        double duration=(x.second.timeLastRxPacket-x.second.timeFirstTxPacket).GetSeconds();
        double throughput=(duration>0)?(x.second.rxBytes*8.0/duration/1e6):0;
        double delay=(x.second.rxPackets>0)?(x.second.delaySum.GetSeconds()*1000.0/x.second.rxPackets):0;
        std::cout << "TCP Tx=" << x.second.txPackets << " Rx=" << x.second.rxPackets
                  << " Lost/unreceived estimate=" << (x.second.txPackets>x.second.rxPackets?x.second.txPackets-x.second.rxPackets:0)
                  << " Throughput=" << throughput << " Mbps"
                  << " AvgDelay=" << delay << " ms\n";
    }
    std::cout << "Inspect tcpcc-bottleneck PCAP for retransmissions and congestion behavior.\n";
    monitor->SerializeToXmlFile("tcpcc-flowmon.xml",true,true);
    Simulator::Destroy();
    return 0;
}
