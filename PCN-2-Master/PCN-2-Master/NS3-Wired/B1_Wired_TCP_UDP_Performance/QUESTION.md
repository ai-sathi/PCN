# B1 — Wired network simulation with TCP/UDP and performance analysis

## Exam question
Create a multi-node topology with point-to-point links, IP addressing and routing. Generate TCP and UDP traffic, enable tracing and FlowMonitor, and calculate throughput, delay, packet loss, PDR and retransmission-related metrics.

## Base topology
- Four end hosts and two intermediate routers.
- TCP flow from Node 0 to Node 3.
- UDP flow from Node 1 to Node 2.
- Access links: 10 Mbps, 2 ms.
- Bottleneck: 2 Mbps, 10 ms.
- DropTail queue: 50 packets.
- TCP packet: 1024 bytes; UDP packet: 512 bytes at 1 Mbps.
- Simulation time: 20 seconds.

## Metrics
The code prints Tx/Rx packets, estimated unreceived packets/loss percentage, throughput, average end-to-end delay and jitter sum. It writes a FlowMonitor XML report and a PCAP trace for the bottleneck.

**Retransmissions:** FlowMonitor's IP-level packet counters do not provide a reliable exact TCP retransmission count. Inspect the PCAP/TCP traces; do not treat Tx − Rx as the retransmission count.
