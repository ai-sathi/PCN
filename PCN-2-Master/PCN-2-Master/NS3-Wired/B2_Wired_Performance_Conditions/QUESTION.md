# B2 — Evaluate wired network performance under different conditions

## Exam question
Modify the base simulation to vary bottleneck bandwidth, queue size and propagation delay. Compare routing protocols and TCP congestion-control algorithms where supported.

## Three practical parts
1. `Parameter_Variation/`: change bottleneck bandwidth, queue size, bottleneck delay and UDP rate; compare performance metrics.
2. `Routing_Link_Failure/`: demonstrate what happens when a router interface/link goes down. This example uses NS-3 global routing and is **not an OSPF implementation**.
3. `TCP_Congestion_Control/`: select a TCP congestion-control TypeId and compare the same TCP flow under each controller that is actually available in your NS-3 build.

## Metrics
Throughput, average end-to-end delay, packet counters/loss estimate, and packet-trace inspection for retransmissions. Keep topology and traffic fixed while changing one parameter/algorithm at a time.
