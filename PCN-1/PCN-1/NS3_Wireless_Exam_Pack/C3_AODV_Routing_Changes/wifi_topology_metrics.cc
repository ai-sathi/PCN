#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/aodv-module.h"
#include "ns3/olsr-module.h"

using namespace ns3;

int
main(int argc, char *argv[])
{
    uint32_t nWifi = 6;
    double simulationTime = 20.0;
    double speed = 0.0;
    double pause = 1.0;
    std::string udpRate = "1Mbps";
    std::string mode = "static"; // static or randomwalk
    std::string routing = "olsr"; // olsr or aodv

    CommandLine cmd(__FILE__);
    cmd.AddValue("nWifi", "Number of Wi-Fi stations", nWifi);
    cmd.AddValue("simulationTime", "Simulation duration in seconds", simulationTime);
    cmd.AddValue("speed", "Mobility speed in m/s for randomwalk mode", speed);
    cmd.AddValue("pause", "Pause time for mobility", pause);
    cmd.AddValue("udpRate", "UDP offered rate", udpRate);
    cmd.AddValue("mode", "Mobility mode: static or randomwalk", mode);
    cmd.AddValue("routing", "Routing protocol: olsr or aodv", routing);
    cmd.Parse(argc, argv);

    NodeContainer wifiStaNodes;
    wifiStaNodes.Create(nWifi);
    NodeContainer wifiApNode;
    wifiApNode.Create(1);

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211g);
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                 "DataMode", StringValue("ErpOfdmRate24Mbps"),
                                 "ControlMode", StringValue("ErpOfdmRate6Mbps"));

    WifiMacHelper mac;
    Ssid ssid = Ssid("exam-wifi-network");

    mac.SetType("ns3::StaWifiMac",
                "Ssid", SsidValue(ssid),
                "ActiveProbing", BooleanValue(false));
    NetDeviceContainer staDevices = wifi.Install(phy, mac, wifiStaNodes);

    mac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid));
    NetDeviceContainer apDevices = wifi.Install(phy, mac, wifiApNode);

    if (mode == "static")
    {
        MobilityHelper mobility;
        Ptr<ListPositionAllocator> positions = CreateObject<ListPositionAllocator>();
        positions->Add(Vector(0.0, 0.0, 0.0)); // AP
        for (uint32_t i = 0; i < nWifi; ++i)
        {
            positions->Add(Vector(5.0 + 5.0 * i, 0.0, 0.0));
        }
        NodeContainer all;
        all.Add(wifiApNode);
        all.Add(wifiStaNodes);
        mobility.SetPositionAllocator(positions);
        mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
        mobility.Install(all);
    }
    else if (mode == "randomwalk")
    {
        NodeContainer all;
        all.Add(wifiApNode);
        all.Add(wifiStaNodes);
        MobilityHelper mobility;
        mobility.SetPositionAllocator("ns3::GridPositionAllocator",
            "MinX", DoubleValue(0.0), "MinY", DoubleValue(0.0),
            "DeltaX", DoubleValue(10.0), "DeltaY", DoubleValue(10.0),
            "GridWidth", UintegerValue(3), "LayoutType", StringValue("RowFirst"));
        mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel",
            "Bounds", RectangleValue(Rectangle(-20, 100, -20, 100)),
            "Speed", StringValue("ns3::ConstantRandomVariable[Constant=2.0]"),
            "Time", TimeValue(Seconds(pause)));
        mobility.Install(all);
    }
    else
    {
        std::cerr << "Use --mode=static or --mode=randomwalk\n";
        return 1;
    }

    InternetStackHelper internet;
    if (routing == "aodv")
    {
        AodvHelper aodv;
        Ipv4ListRoutingHelper list;
        list.Add(aodv, 10);
        internet.SetRoutingHelper(list);
    }
    else if (routing == "olsr")
    {
        OlsrHelper olsr;
        Ipv4ListRoutingHelper list;
        list.Add(olsr, 10);
        internet.SetRoutingHelper(list);
    }
    else
    {
        std::cerr << "Use --routing=olsr or --routing=aodv\n";
        return 1;
    }
    internet.Install(wifiStaNodes);
    internet.Install(wifiApNode);

    Ipv4AddressHelper address;
    address.SetBase("10.3.0.0", "255.255.255.0");
    Ipv4InterfaceContainer staInterfaces = address.Assign(staDevices);
    Ipv4InterfaceContainer apInterfaces = address.Assign(apDevices);

    // Install an application on station 0 and send to station 1.
    // The Wi-Fi AP is infrastructure; station-to-station forwarding depends on routing and network setup.
    // To keep the lab demo simple and reliable, the receiver is the AP itself.
    uint16_t port = 9000;
    PacketSinkHelper sinkHelper("ns3::UdpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), port));
    ApplicationContainer sink = sinkHelper.Install(wifiApNode.Get(0));
    sink.Start(Seconds(0.5));
    sink.Stop(Seconds(simulationTime));

    OnOffHelper source("ns3::UdpSocketFactory",
        InetSocketAddress(apInterfaces.GetAddress(0), port));
    source.SetAttribute("DataRate", StringValue(udpRate));
    source.SetAttribute("PacketSize", UintegerValue(512));
    source.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    source.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    ApplicationContainer app = source.Install(wifiStaNodes.Get(0));
    app.Start(Seconds(1.0));
    app.Stop(Seconds(simulationTime - 0.5));

    FlowMonitorHelper flowHelper;
    Ptr<FlowMonitor> monitor = flowHelper.InstallAll();
    Simulator::Stop(Seconds(simulationTime));
    Simulator::Run();
    monitor->CheckForLostPackets();

    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowHelper.GetClassifier());
    std::cout << "\n=== NS-3 Wireless Metrics ===\n";
    std::cout << "Stations: " << nWifi << " | mode: " << mode << " | routing: " << routing
              << " | UDP rate: " << udpRate << "\n";
    std::cout << "Flow\tProtocol\tTx\tRx\tLost\tPDR(%)\tAvgDelay(ms)\tThroughput(Mbps)\n";
    for (const auto &entry : monitor->GetFlowStats())
    {
        auto tuple = classifier->FindFlow(entry.first);
        const auto &s = entry.second;
        double pdr = s.txPackets ? 100.0 * s.rxPackets / s.txPackets : 0.0;
        double delay = s.rxPackets ? 1000.0 * s.delaySum.GetSeconds() / s.rxPackets : 0.0;
        double duration = s.timeLastRxPacket.GetSeconds() - s.timeFirstTxPacket.GetSeconds();
        double throughput = duration > 0 ? s.rxBytes * 8.0 / duration / 1e6 : 0.0;
        std::cout << entry.first << "\t" << (tuple.protocol == 17 ? "UDP" : (tuple.protocol == 6 ? "TCP" : "Other"))
                  << "\t" << s.txPackets << "\t" << s.rxPackets << "\t" << s.lostPackets
                  << "\t" << pdr << "\t" << delay << "\t" << throughput << "\n";
    }

    monitor->SerializeToXmlFile("wireless-flowmon.xml", true, true);
    Simulator::Destroy();
    return 0;
}
