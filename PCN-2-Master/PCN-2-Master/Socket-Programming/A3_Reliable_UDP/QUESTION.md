# A3 — Reliable data transfer over UDP

## Exam question
Implement timers, acknowledgements, timeouts and retransmissions to handle lost packets.

## What to demonstrate
- The sender includes a sequence number in each data packet.
- The receiver replies with an ACK.
- If an ACK is not received before timeout, the sender retransmits.
- The output shows RTT and retransmission count.

## Metrics
RTT, retransmission count, packet delivery ratio (PDR), and approximate throughput. This is a teaching demo; it does not reproduce all features of TCP.
