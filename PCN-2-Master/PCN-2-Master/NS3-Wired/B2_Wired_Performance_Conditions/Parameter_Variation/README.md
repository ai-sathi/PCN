# W4. Vary bandwidth, queue size and propagation delay

## What this program does
Uses command-line parameters to change bottleneck bandwidth, queue capacity, link delay and UDP rate without editing code.

## Topology
- Node 0: TCP sender
- Node 1: UDP sender
- Node 2: UDP receiver
- Node 3: TCP receiver
- Node 4 and Node 5: routers
- Access links: 10 Mbps, 2 ms
- Bottleneck link: 2 Mbps, 10 ms
- Queue: DropTail, 50 packets
- TCP packet size: 1024 bytes; UDP packet size: 512 bytes; UDP rate: 1 Mbps
- Simulation: 20 seconds

## How to run
1. Copy `wired_simulation.cc` into your NS-3 `scratch/` directory.
2. From the NS-3 root folder, run:

```bash
./ns3 run scratch/wired_simulation
```

Run the three bandwidth cases and compare the printed metrics.

## Useful W4 commands
```bash
./ns3 run "scratch/wired_simulation --bottleneckRate=2Mbps"
./ns3 run "scratch/wired_simulation --bottleneckRate=5Mbps"
./ns3 run "scratch/wired_simulation --bottleneckRate=10Mbps"
./ns3 run "scratch/wired_simulation --queueSize=20p"
./ns3 run "scratch/wired_simulation --queueSize=100p"
./ns3 run "scratch/wired_simulation --bottleneckDelay=20ms"
./ns3 run "scratch/wired_simulation --udpRateMbps=2"
```

## Metrics printed
- Tx packets and Rx packets
- Estimated unreceived packets and loss percentage
- Throughput (Mbps)
- Average end-to-end delay (ms)
- Jitter sum
- TCP retransmissions are **not directly counted by FlowMonitor** in this program; inspect PCAP/TCP traces for retransmissions.

## Expected output shape
Actual numbers vary by NS-3 version and run. The terminal prints a summary, then a block for each detected flow with protocol, addresses, packet counts, loss estimate, throughput and delay. It also writes `wired-flowmon.xml` and bottleneck PCAP files if tracing is enabled.

## Viva
- What is a NodeContainer?
- Why do we install InternetStackHelper?
- What does Ipv4AddressHelper do?
- Why is a bottleneck link used?
- What is DropTail?
- What is FlowMonitor?
- What is throughput? How is it calculated?
- What is end-to-end delay?
- Why is loss shown as an estimate?
- Why must TCP retransmissions be checked with a packet trace?
