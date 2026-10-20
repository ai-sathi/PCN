# B2 run instructions

Each subfolder contains a separate program and README.

## Parameter variation
Copy `Parameter_Variation/wired_simulation.cc` to `scratch/wired_simulation.cc`, then run:
```bash
./ns3 run "scratch/wired_simulation --bottleneckRate=2Mbps"
./ns3 run "scratch/wired_simulation --bottleneckRate=5Mbps"
./ns3 run "scratch/wired_simulation --bottleneckRate=10Mbps"
./ns3 run "scratch/wired_simulation --queueSize=20p"
./ns3 run "scratch/wired_simulation --queueSize=100p"
./ns3 run "scratch/wired_simulation --bottleneckDelay=20ms"
```

## Routing failure
Copy `Routing_Link_Failure/routing_failure.cc` to `scratch/routing_failure.cc`, then run:
```bash
./ns3 run scratch/routing_failure
```

## TCP congestion control
Copy `TCP_Congestion_Control/tcp_congestion.cc` to `scratch/tcp_congestion.cc`, then run:
```bash
./ns3 run scratch/tcp_congestion
./ns3 run "scratch/tcp_congestion --tcpType=ns3::TcpNewReno"
```
Cubic/BBR are only usable if registered in your NS-3 build. See the nested README before claiming those algorithms were tested.
