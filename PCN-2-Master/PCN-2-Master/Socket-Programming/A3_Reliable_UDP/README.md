# A5 — Reliable UDP Using Timers, ACKs and Retransmissions

## Exact exam question
Implement a simple reliable data-transfer mechanism over UDP using sequence numbers, ACKs, a timeout and retransmission if an ACK is not received.

## Files
- `reliable_udp_server.py`
- `reliable_udp_client.py`

## Run on Windows PowerShell
Terminal 1:
```powershell
py reliable_udp_server.py
```
Terminal 2:
```powershell
py reliable_udp_client.py
```

## Expected output
The client prints sequence numbers, ACK receipt and an RTT estimate. If the server is stopped or does not reply, the client times out and retries up to five times.

## How to verify
Run normally to see ACKs. For a timeout demonstration, stop the server, then run the client in another terminal.

## Performance metrics
- RTT = ACK arrival time − packet send time.
- Retransmission count = number of sends repeated after timeout.
- PDR = unique messages acknowledged / messages sent × 100%.
- Goodput = useful payload bits delivered / elapsed time.

## Limitations to mention
This teaching example demonstrates timeout and retransmission, but it does not implement full duplicate suppression or a production-grade reliable protocol.

## Viva questions
See `VIVA.md`.
## Metrics printed by the code
Client prints per-message RTT, total transmissions, retransmission count, message-level PDR and application throughput. This is a localhost demonstration; loss is only observed if a timeout actually occurs.
