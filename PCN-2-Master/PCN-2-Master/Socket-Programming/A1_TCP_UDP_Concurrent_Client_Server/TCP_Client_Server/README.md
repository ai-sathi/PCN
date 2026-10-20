# A1 — TCP Client-Server

## Exact exam question
Develop a TCP client-server application. The client sends a message to the server, and the server replies.

## Files
- `tcp_server.py` — listens, accepts one client, receives a message and replies.
- `tcp_client.py` — connects, sends a message and prints the reply.

## Run on Windows PowerShell
Open two terminals in this folder.

Terminal 1:
```powershell
py tcp_server.py
```
Terminal 2:
```powershell
py tcp_client.py
```

## Expected output
Client:
```text
Server: Hello from TCP server
```
Server shows the connection and the client's message.

## How to verify
The client prints the server reply and the server prints the client's message.

## Performance metrics (if asked)
- RTT = response receive time − request send time.
- Throughput (bit/s) = successfully received payload bits / elapsed seconds.
- For a single exchange, explain the measurement method; do not invent a value.

## Viva questions
See `VIVA.md`.
## Metrics printed by the code
TCP client prints application-level RTT and reply throughput.
