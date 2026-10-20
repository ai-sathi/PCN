# C4 — Measure wireless metrics under changing conditions (R4)

## Run the baseline
```bash
./ns3 run "scratch/wifi_topology_metrics --mode=static --nWifi=6 --udpRate=1Mbps"
```

## Vary offered traffic and node count
```bash
./ns3 run "scratch/wifi_topology_metrics --mode=static --nWifi=6 --udpRate=500Kbps"
./ns3 run "scratch/wifi_topology_metrics --mode=static --nWifi=6 --udpRate=2Mbps"
./ns3 run "scratch/wifi_topology_metrics --mode=static --nWifi=10 --udpRate=1Mbps"
./ns3 run "scratch/wifi_topology_metrics --mode=randomwalk --nWifi=6 --udpRate=1Mbps"
```

## Metrics
The program prints throughput, PDR, delay and packet loss for each flow.

| Run | Mode | Stations | UDP rate | Throughput | PDR | Avg delay | Lost |
|---|---|---:|---:|---:|---:|---:|---:|
| 1 | static | 6 | 1 Mbps | | | | |
| 2 | static | 6 | 500 Kbps | | | | |
| 3 | static | 6 | 2 Mbps | | | | |
| 4 | static | 10 | 1 Mbps | | | | |
| 5 | randomwalk | 6 | 1 Mbps | | | | |

## Interpretation
Higher offered load can increase contention and packet loss. More stations may increase channel competition. Mobility may change link quality. These are expected trends, not guaranteed numeric outcomes.
