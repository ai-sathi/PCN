#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include <iostream>
#include <iomanip>

using namespace ns3;

int main(int argc, char *argv[])
{
    std::string bottleneckRate = "2Mbps";
    std::string accessRate = "10Mbps";
    std::string accessDelay = "2ms";
    std::string bottleneckDelay = "10ms";
    std::string queueSize = "50p";
    double udpRateMbps = 1.0;
    double simTime = 20.0;
    bool pcap = true;

    CommandLine cmd(__FILE__);
    cmd.AddValue("bottleneckRate", "Bottleneck bandwidth, e.g. 2Mbps, 5Mbps, 10Mbps", bottleneckRate);
    cmd.AddValue("accessRate", "Access link bandwidth", accessRate);
    cmd.AddValue("accessDelay", "Access link delay", accessDelay);
    cmd.AddValue("bottleneckDelay", "Bottleneck delay", bottleneckDelay);
    cmd.AddValue("queueSize", "DropTail queue size, e.g. 50p", queueSize);
    cmd.AddValue("udpRateMbps", "UDP application rate in Mbps", udpRateMbps);
    cmd.AddValue("simTime", "Simulation duration in seconds", simTime);
    cmd.AddValue("pcap", "Enable PCAP trace files (1/0)", pcap);
    cmd.Parse(argc, argv);

    // W4 experiments: vary the command-line parameters and compare outputs.
    NodeContainer n;
    n.Create(6);
    InternetStackHelper internet;
    internet.Install(n);

    PointToPointHelper access;
    access.SetDeviceAttribute("DataRate", StringValue(accessRate));
    access.SetChannelAttribute("Delay", StringValue(accessDelay));
    access.SetQueue("ns3::DropTailQueue<Packet>", "MaxSize", StringValue(queueSize));

    PointToPointHelper bottleneck;
    bottleneck.SetDeviceAttribute("DataRate", StringValue(bottleneckRate));
    bottleneck.SetChannelAttribute("Delay", StringValue(bottleneckDelay));
    bottleneck.SetQueue("ns3::DropTailQueue<Packet>", "MaxSize", StringValue(queueSize));

    NetDeviceContainer d0r0 = access.Install(n.Get(0), n.Get(4));
    NetDeviceContainer d1r0 = access.Install(n.Get(1), n.Get(4));
    NetDeviceContainer dr0r1 = bottleneck.Install(n.Get(4), n.Get(5));
    NetDeviceContainer dr1n2 = access.Install(n.Get(5), n.Get(2));
    NetDeviceContainer dr1n3 = access.Install(n.Get(5), n.Get(3));

    Ipv4AddressHelper ip;
    Ipv4InterfaceContainer i0r0, i1r0, ir0r1, ir1n2, ir1n3;
    ip.SetBase("10.1.1.0", "255.255.255.0"); i0r0 = ip.Assign(d0r0);
    ip.SetBase("10.1.2.0", "255.255.255.0"); i1r0 = ip.Assign(d1r0);
    ip.SetBase("10.1.3.0", "255.255.255.0"); ir0r1 = ip.Assign(dr0r1);
    ip.SetBase("10.1.4.0", "255.255.255.0"); ir1n2 = ip.Assign(dr1n2);
    ip.SetBase("10.1.5.0", "255.255.255.0"); ir1n3 = ip.Assign(dr1n3);
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    uint16_t tcpPort = 5000, udpPort = 6000;
    PacketSinkHelper tcpSink("ns3::TcpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), tcpPort));
    ApplicationContainer tcpSinkApp = tcpSink.Install(n.Get(3));
    tcpSinkApp.Start(Seconds(0.0)); tcpSinkApp.Stop(Seconds(simTime));

    PacketSinkHelper udpSink("ns3::UdpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), udpPort));
    ApplicationContainer udpSinkApp = udpSink.Install(n.Get(2));
    udpSinkApp.Start(Seconds(0.0)); udpSinkApp.Stop(Seconds(simTime));

    OnOffHelper tcpSource("ns3::TcpSocketFactory",
        InetSocketAddress(ir1n3.GetAddress(1), tcpPort));
    tcpSource.SetAttribute("DataRate", StringValue("2Mbps"));
    tcpSource.SetAttribute("PacketSize", UintegerValue(1024));
    tcpSource.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    tcpSource.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    ApplicationContainer tcpSourceApp = tcpSource.Install(n.Get(0));
    tcpSourceApp.Start(Seconds(1.0)); tcpSourceApp.Stop(Seconds(simTime - 1));

    OnOffHelper udpSource("ns3::UdpSocketFactory",
        InetSocketAddress(ir1n2.GetAddress(1), udpPort));
    udpSource.SetAttribute("DataRate", DataRateValue(DataRate(std::to_string((uint64_t)(udpRateMbps * 1000000)) + "bps")));
    udpSource.SetAttribute("PacketSize", UintegerValue(512));
    udpSource.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    udpSource.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    ApplicationContainer udpSourceApp = udpSource.Install(n.Get(1));
    udpSourceApp.Start(Seconds(1.0)); udpSourceApp.Stop(Seconds(simTime - 1));

    if (pcap) {
        bottleneck.EnablePcap("wired-bottleneck", dr0r1, true);
    }

    FlowMonitorHelper flowHelper;
    Ptr<FlowMonitor> monitor = flowHelper.InstallAll();
    Simulator::Stop(Seconds(simTime));
    Simulator::Run();
    monitor->CheckForLostPackets();

    Ptr<Ipv4FlowClassifier> classifier =
        DynamicCast<Ipv4FlowClassifier>(flowHelper.GetClassifier());
    auto stats = monitor->GetFlowStats();

    std::cout << "\n=== NS-3 WIRED PERFORMANCE SUMMARY ===\n";
    std::cout << "Access=" << accessRate << ", bottleneck=" << bottleneckRate
              << ", queue=" << queueSize << ", UDP rate=" << udpRateMbps
              << " Mbps, simulation=" << simTime << " s\n";

    for (const auto &entry : stats) {
        Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(entry.first);
        const FlowMonitor::FlowStats &s = entry.second;
        if (s.txPackets == 0) continue;
        double duration = (s.timeLastRxPacket - s.timeFirstTxPacket).GetSeconds();
        double throughputMbps = (duration > 0)
            ? (s.rxBytes * 8.0 / duration / 1000000.0) : 0.0;
        double avgDelayMs = (s.rxPackets > 0)
            ? (s.delaySum.GetSeconds() * 1000.0 / s.rxPackets) : 0.0;
        uint64_t lost = (s.txPackets > s.rxPackets) ? (s.txPackets - s.rxPackets) : 0;
        double lossPct = (s.txPackets > 0) ? (100.0 * lost / s.txPackets) : 0.0;

        std::string proto = (t.protocol == 6) ? "TCP" : ((t.protocol == 17) ? "UDP" : "Other");
        std::cout << "\nFlow " << entry.first << " (" << proto << ") "
                  << t.sourceAddress << ":" << t.sourcePort << " -> "
                  << t.destinationAddress << ":" << t.destinationPort << "\n";
        std::cout << "  Tx packets: " << s.txPackets << "\n";
        std::cout << "  Rx packets: " << s.rxPackets << "\n";
        std::cout << "  Lost/unreceived estimate: " << lost << "\n";
        std::cout << "  Loss percentage estimate: " << std::fixed << std::setprecision(2) << lossPct << "%\n";
        std::cout << "  Throughput: " << throughputMbps << " Mbps\n";
        std::cout << "  Average end-to-end delay: " << avgDelayMs << " ms\n";
        std::cout << "  Jitter sum: " << s.jitterSum.GetMilliSeconds() << " ms\n";
    }
    std::cout << "\nPCAP file prefix: wired-bottleneck (open with Wireshark if generated).\n";
    std::cout << "Note: FlowMonitor loss is an estimate; TCP retransmissions should be inspected in PCAP/TCP traces.\n";
    monitor->SerializeToXmlFile("wired-flowmon.xml", true, true);
    Simulator::Destroy();
    return 0;
}
