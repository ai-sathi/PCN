# Socket Programming — Topic-wise Lab Exam Pack

Each topic has its own folder with:
- the exact exam question,
- only the code files needed for that topic,
- `README.md` with setup, run commands, expected output, verification and metrics,
- `VIVA.md` with short question-and-answer revision.

## Topics
1. `A1_TCP_Client_Server`
2. `A2_UDP_Client_Server`
3. `A3_Concurrent_TCP_Multiple_Clients`
4. `A4_HTTP_Webpage_Download_Local_Server`
5. `A5_Reliable_UDP_Timers_ACK_Retransmission`
6. `A6_DNS_Simulation`
7. `A7_Checksum_Error_Detection`
8. `A8_CRC_Error_Detection`
9. `A9_Hamming_Code_Error_Correction`

## Environment
Windows 10/11, PowerShell, Python 3.10+ recommended. No pip packages are required.
Check Python with `py --version`. If `py` is unavailable, try `python --version` and replace `py` with `python` in commands.

## Important
- Run the server in one terminal and the client in another.
- All examples use `127.0.0.1` for local practice.
- The HTTP client requires a local server started using the command in its topic README.
- The DNS program is a simplified teaching simulation, not a full DNS implementation.
- The error-detection server handles one request and exits; restart it before each checksum/CRC/Hamming test.
- ARP is intentionally excluded.
