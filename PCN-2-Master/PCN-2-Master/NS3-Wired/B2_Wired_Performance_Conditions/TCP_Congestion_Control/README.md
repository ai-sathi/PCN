# W6. Compare TCP congestion-control algorithms

## What it does
Runs a TCP flow through a bottleneck and prints throughput, average delay and packet counters. Select a TCP TypeId through a command-line argument. Support for Cubic/BBR depends on the installed NS-3 build.

## Run
Copy `tcp_congestion.cc` into `scratch/`, then run from the NS-3 root:
```bash
./ns3 run scratch/tcp_congestion
./ns3 run "scratch/tcp_congestion --tcpType=ns3::TcpNewReno"
./ns3 run "scratch/tcp_congestion --tcpType=ns3::TcpCubic"
./ns3 run "scratch/tcp_congestion --tcpType=ns3::TcpBbr"
```
If Cubic or BBR is not registered, the program prints an error and exits. Do not claim that a controller was tested if the installed version does not support it.

## Metrics
- Throughput (Mbps)
- Average end-to-end delay (ms)
- Tx/Rx packet counts and estimated unreceived packets
- PCAP trace for inspecting retransmissions
- FlowMonitor XML

## Viva
- What is congestion control?
- What is the difference between flow control and congestion control?
- What does TCP do after packet loss?
- What is a congestion window?
- What is TCP NewReno?
- Are Cubic and BBR guaranteed to exist in every NS-3 release? No; check the installed build.
- Why should all other parameters remain the same when comparing algorithms?
