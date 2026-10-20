# NS-3 Wired — 6 Practice Questions

Each question has its own folder, C++ file, README with run instructions, metrics and viva questions.

## Folder map
1. `W1_Multi_Node_Topology` — multi-node wired topology, IP addressing and global routing
2. `W2_TCP_UDP_Packet_Tracing` — TCP/UDP flows and PCAP packet tracing
3. `W3_Performance_Metrics` — throughput, delay, loss and FlowMonitor
4. `W4_Vary_Network_Parameters` — vary bandwidth, queue size and delay
5. `W5_Routing_Link_Failure` — global-routing link-failure demonstration
6. `W6_TCP_Congestion_Control` — selectable TCP controller, if available in the installed NS-3 version

## General run procedure
- Use a compatible installed NS-3 source tree.
- Copy the `.cc` file for one question into the NS-3 `scratch/` folder.
- Open a terminal in the NS-3 root folder.
- Run the exact command in that question's README, for example `./ns3 run scratch/wired_simulation`.
- On Windows, NS-3 is commonly run through a Linux environment/WSL; the launcher may be `./ns3` inside the NS-3 directory.

## Important notes
- These are separate practice programs, not six entirely different topologies. W1–W4 deliberately reuse the same base topology so you can learn one program and vary parameters.
- The default routed topology follows the user's prior lab assignment: four end hosts and two routers; 10 Mbps / 2 ms access links; 2 Mbps / 10 ms bottleneck; 50-packet DropTail queue; 20 seconds; TCP 1024 bytes and UDP 512 bytes at 1 Mbps.
- FlowMonitor gives flow-level counters, throughput and delay. PCAP is for packet-level inspection.
- TCP retransmissions are not directly counted by the FlowMonitor output in these examples; inspect TCP packet traces. Do not report `Tx - Rx` as a precise retransmission count.
- OSPF is not supplied as a general built-in protocol in every NS-3 setup. W5 is explicitly a global-routing interface-failure demonstration, not OSPF. Use only protocol modules actually available in your NS-3 version.
- TCP Cubic/BBR availability depends on the NS-3 version/build; W6 checks whether the requested TypeId exists.
