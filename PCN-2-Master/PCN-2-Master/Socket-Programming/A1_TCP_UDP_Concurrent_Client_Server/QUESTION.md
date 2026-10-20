# A1 — TCP and UDP client-server communication

## Exam question
Develop TCP and UDP client-server applications to exchange messages. Extend the TCP server to handle multiple clients concurrently.

## What this master question covers
- TCP connection-oriented communication: `TCP_Client_Server/`
- UDP datagram communication: `UDP_Client_Server/`
- Multiple clients handled simultaneously by a threaded TCP server: `Concurrent_TCP_Server/`

## How to prepare
These are three related implementations, not one combined Python file. Practise running each server in one terminal and its client in another. For concurrent TCP, run the server once and start two or more clients.

## Metrics to explain
- TCP: round-trip time (RTT) and approximate application throughput.
- UDP: RTT; for multiple datagrams, packet delivery ratio (PDR), packet loss and throughput.
- Concurrent TCP: per-client response time, total requests handled and approximate throughput.

Open the README.md inside each subfolder for exact commands and its VIVA.md for question-specific viva.
