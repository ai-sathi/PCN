# C2 — Simulate node mobility and evaluate performance (R2)

## Run a static baseline
```bash
./ns3 run "scratch/wifi_topology_metrics --mode=static"
```

## Run moving nodes
```bash
./ns3 run "scratch/wifi_topology_metrics --mode=randomwalk --speed=2 --pause=1"
```

The current code's RandomWalk speed is set in the mobility model to a constant 2 m/s for exam simplicity. To change the speed, edit the `ConstantRandomVariable[Constant=2.0]` string in the source to the desired value; the `--speed` argument is accepted for command-line familiarity but isn't yet wired to the mobility model.

## Compare
Run both cases and record:
- Throughput (Mbps)
- PDR (%)
- Average delay (ms)
- Lost packets

Keep the node count, UDP rate, duration and routing protocol the same so the mobility setting is the main change.

## Interpretation
Movement can change distances and channel conditions. Throughput may decrease, delay may rise and packet loss may increase, but results depend on placement, PHY settings, routing and simulation seed.
