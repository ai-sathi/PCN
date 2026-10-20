# W5. Routing protocol behavior under link failure

## Important accuracy note
This exam-friendly example demonstrates **NS-3 global routing** and what happens when a router interface is brought down. It is **not an OSPF implementation**. NS-3 routing modules vary by version; only claim a comparison of RIP/OLSR/AODV/other protocols if that module is installed and configured.

## Topology and behavior
- Four end hosts and two routers.
- UDP traffic from Node 0 to Node 3.
- The router-to-router link interface is brought down at 8 seconds by default.
- FlowMonitor writes `routing-flowmon.xml`.

## Run
Copy `routing_failure.cc` into `scratch/`, then from the NS-3 root:
```bash
./ns3 run scratch/routing_failure
./ns3 run "scratch/routing_failure --failTime=6"
```

## What to observe
Compare packet delivery before and after the interface failure. A single-path topology can lose traffic after the link fails because there is no alternate route. This example is a link-failure demonstration, not a fair comparison between two protocols. To compare protocols, keep topology and traffic the same and change only the routing helper.

## Metrics / viva
FlowMonitor XML contains flow counters and delay statistics. Questions:
- What is routing?
- What is a routing table?
- What is global routing in NS-3?
- What is a link failure?
- Why can packets be lost after a link goes down?
- What is the difference between a routing protocol and a routing algorithm?
- Is this OSPF? No; it demonstrates global routing.
