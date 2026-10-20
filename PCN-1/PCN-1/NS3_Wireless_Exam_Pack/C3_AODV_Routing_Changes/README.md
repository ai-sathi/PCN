# C3 — Configure AODV and examine routing changes (R3)

## Run
```bash
./ns3 run "scratch/wifi_topology_metrics --routing=aodv --mode=randomwalk"
```

Compare against OLSR:
```bash
./ns3 run "scratch/wifi_topology_metrics --routing=olsr --mode=randomwalk"
```

## What to observe
The program prints per-flow Tx/Rx/loss/PDR/delay/throughput and writes `wireless-flowmon.xml`. AODV is reactive: it discovers routes when needed. OLSR is proactive: it maintains routes using periodic control information.

## Important limitation
The included minimal traffic goes from a Wi-Fi station to the AP itself. That is enough to exercise Wi-Fi and show the protocol selection, but it is **not a strong multi-hop route-discovery demonstration**. For meaningful AODV route changes, use a multi-hop ad hoc Wi-Fi topology with a destination several hops away and trace route-request/route-reply events. Do not claim that this simple station-to-AP run proves multi-hop AODV route discovery.
