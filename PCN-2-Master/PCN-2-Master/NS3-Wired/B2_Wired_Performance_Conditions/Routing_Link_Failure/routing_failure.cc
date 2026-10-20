#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include <iostream>
using namespace ns3;

static void LinkDown(Ptr<NetDevice> dev)
{
    Ptr<Node> node = dev->GetNode();
    Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();
    int32_t iface = ipv4->GetInterfaceForDevice(dev);
    if (iface >= 0) {
        ipv4->SetDown(iface);
        std::cout << "Link/interface brought DOWN at " << Simulator::Now().GetSeconds() << " s\n";
    }
}

int main(int argc, char *argv[])
{
    double failTime = 8.0;
    CommandLine cmd(__FILE__);
    cmd.AddValue("failTime", "Time to bring the primary link interface down", failTime);
    cmd.Parse(argc, argv);

    NodeContainer n; n.Create(6); // 4 end hosts + 2 routers
    InternetStackHelper internet;
    Ipv4GlobalRoutingHelper globalRouting;
    internet.SetRoutingHelper(globalRouting);
    internet.Install(n);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("5ms"));

    NetDeviceContainer a = p2p.Install(n.Get(0), n.Get(4));
    NetDeviceContainer b = p2p.Install(n.Get(1), n.Get(4));
    NetDeviceContainer c = p2p.Install(n.Get(4), n.Get(5)); // primary router link
    NetDeviceContainer d = p2p.Install(n.Get(5), n.Get(2));
    NetDeviceContainer e = p2p.Install(n.Get(5), n.Get(3));

    Ipv4AddressHelper ip;
    ip.SetBase("10.1.1.0","255.255.255.0"); ip.Assign(a);
    ip.SetBase("10.1.2.0","255.255.255.0"); ip.Assign(b);
    ip.SetBase("10.1.3.0","255.255.255.0"); ip.Assign(c);
    ip.SetBase("10.1.4.0","255.255.255.0"); ip.Assign(d);
    ip.SetBase("10.1.5.0","255.255.255.0"); Ipv4InterfaceContainer dst = ip.Assign(e);
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // UDP traffic tests the route. The link failure demonstrates route disruption.
    uint16_t port = 9000;
    PacketSinkHelper sink("ns3::UdpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), port));
    auto sinkApp = sink.Install(n.Get(3));
    sinkApp.Start(Seconds(0)); sinkApp.Stop(Seconds(15));

    OnOffHelper source("ns3::UdpSocketFactory",
        InetSocketAddress(dst.GetAddress(1), port));
    source.SetAttribute("DataRate", StringValue("1Mbps"));
    source.SetAttribute("PacketSize", UintegerValue(512));
    source.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    source.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    auto srcApp = source.Install(n.Get(0));
    srcApp.Start(Seconds(1)); srcApp.Stop(Seconds(14));

    // Global routing can react to interface events in supported ns-3 releases.
    Config::SetDefault("ns3::Ipv4GlobalRouting::RespondToInterfaceEvents", BooleanValue(true));
    Simulator::Schedule(Seconds(failTime), &LinkDown, c.Get(0));
    FlowMonitorHelper fm; auto monitor = fm.InstallAll();
    Simulator::Stop(Seconds(15));
    Simulator::Run(); monitor->CheckForLostPackets();
    std::cout << "\nRouting experiment finished. Check packet delivery before/after link failure.\n";
    std::cout << "Note: This is a global-routing link-failure demonstration, not an OSPF implementation.\n";
    monitor->SerializeToXmlFile("routing-flowmon.xml", true, true);
    Simulator::Destroy();
    return 0;
}
