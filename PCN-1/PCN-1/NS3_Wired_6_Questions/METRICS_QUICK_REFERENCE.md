# NS-3 Wired Metrics Quick Reference

- **Throughput (Mbps)** = received payload bytes × 8 / observation time / 1,000,000.
- **Average end-to-end delay (ms)** = FlowMonitor delay sum / received packets × 1000.
- **Packet delivery ratio (PDR)** = received packets / transmitted packets × 100%.
- **Packet loss estimate** = transmitted packets − received packets (interpret carefully; FlowMonitor lost-packet accounting has its own timeout behavior).
- **TCP retransmissions**: inspect TCP PCAP/trace information. FlowMonitor's IP-level packet counts alone do not give a reliable exact retransmission count.
- **Queueing delay**: can rise as a bottleneck queue fills; larger queues may reduce drops but can increase delay.
- **RTT**: time between sending a TCP segment and receiving its acknowledgement; inspect TCP packet trace or add a TCP trace source if the lab specifically asks for RTT.

Use actual output values from your run. Do not memorize fabricated metric numbers.
