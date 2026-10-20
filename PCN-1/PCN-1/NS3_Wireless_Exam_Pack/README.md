# NS-3 Wireless Exam Pack — R1 to R4

## Folders
- `C1_WiFi_Topology_Traffic/` — R1
- `C2_Mobility_Performance/` — R2
- `C3_AODV_Routing_Changes/` — R3
- `C4_Wireless_Conditions_Sweep/` — R4

Each folder has its own `.cc` file, `README.md` with run commands and metrics, and `VIVA.md`.

## How to run
1. Use Linux or WSL with ns-3 installed.
2. Copy one `.cc` file into your ns-3 `scratch/` directory.
3. Run the command shown in that topic's README from the ns-3 source root.
4. Record the actual output; do not invent metrics before running.

## Metrics
- Throughput (Mbps) = received bytes × 8 / receive interval / 1,000,000
- Average delay = total delay of received packets / received packet count
- PDR (%) = received packets / transmitted packets × 100
- Packet loss = transmitted packets − received packets

## Important limitations
- The files have not been compiled against the exact ns-3 version on your lab machine.
- AODV/OLSR module support and API details can differ by ns-3 release.
- The supplied minimal scenario uses infrastructure Wi-Fi and sends from a station to the AP; it is not a complete multi-hop ad hoc routing demonstration. The README for R3 explains this.
- The `--speed` command-line argument is currently not wired to the RandomWalk mobility model; to change speed, edit the constant in the source. The README for R2 explains this.
