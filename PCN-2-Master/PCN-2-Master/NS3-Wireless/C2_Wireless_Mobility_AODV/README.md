# C2 run instructions

Copy `aodv_mobility.cc` to `scratch/aodv_mobility.cc` and run from the NS-3 root:
```bash
./ns3 run scratch/aodv_mobility
./ns3 run "scratch/aodv_mobility --nNodes=10"
./ns3 run "scratch/aodv_mobility --simTime=40"
```
Output files: `aodv-mobile-*.pcap` and `aodv-mobile-flowmon.xml`.

Viva:
- What is AODV?
- What is reactive/on-demand routing?
- How does node mobility affect routing?
- What are route discovery and route maintenance?
- Define PDR, throughput, delay and packet loss.
- Why can packet loss increase when nodes move?
