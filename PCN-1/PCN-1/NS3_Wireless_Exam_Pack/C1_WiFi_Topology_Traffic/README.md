# C1 — Create a Wi-Fi topology and generate traffic (R1)

## What it covers
- Wi-Fi stations and one access point
- Wi-Fi PHY/MAC configuration
- IP addressing and routing helper
- UDP traffic
- Throughput, average end-to-end delay, PDR and packet loss

## Run
Copy `wifi_topology_metrics.cc` to `scratch/` in your ns-3 directory. From the ns-3 root:

```bash
./ns3 run scratch/wifi_topology_metrics
```

## Useful variations
```bash
./ns3 run "scratch/wifi_topology_metrics --nWifi=10 --udpRate=2Mbps"
./ns3 run "scratch/wifi_topology_metrics --routing=aodv"
```

## Metrics printed
- PDR (%) = received packets / transmitted packets × 100
- Packet loss = transmitted − received packets
- Average delay = sum of delays / received packets
- Throughput (Mbps) = received bytes × 8 / receive interval / 1,000,000

## Important topology note
This basic example sends UDP traffic from a station to the AP, which is the receiver. It demonstrates Wi-Fi access and traffic metrics without relying on station-to-station forwarding through the AP. If the exam specifically asks station-to-station or multi-hop routing, the topology needs to be extended accordingly.
