# C1 run instructions

Copy `wifi_basic.cc` to your NS-3 root's `scratch/` folder and run:
```bash
./ns3 run scratch/wifi_basic
./ns3 run "scratch/wifi_basic --nNodes=8"
./ns3 run "scratch/wifi_basic --dataRateMbps=2"
```
Output files: `wifi-basic-*.pcap` and `wifi-flowmon.xml`. Open the PCAP files in Wireshark if available.

Viva:
- What is an ad-hoc Wi-Fi network?
- What is the role of WifiHelper and WifiMacHelper?
- Why is mobility configured?
- Define throughput, delay, PDR and packet loss.
- What is FlowMonitor?
