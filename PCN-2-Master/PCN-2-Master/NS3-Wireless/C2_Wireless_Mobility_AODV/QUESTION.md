# C2 — Wireless mobility and routing performance

## Exam question
Add node mobility and AODV routing, then analyze route changes, packet delivery, delay and packet loss under changing network conditions.

## What the program does
- Creates ad-hoc Wi-Fi nodes.
- Assigns random starting positions and RandomWalk2d mobility.
- Installs AODV routing and IP addresses.
- Sends UDP traffic from the first node to the last.
- Collects packet delivery, loss estimate, throughput and delay.
- Enables PCAP and FlowMonitor output for inspecting traffic as nodes move.

## Metrics
Throughput, average end-to-end delay, PDR, estimated packet loss. Route changes can be investigated from AODV logging/traces if enabled in the installed NS-3 version.
