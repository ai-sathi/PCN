# A7 — Checksum Error Detection Using Sockets

## Exact exam question
Implement checksum-based error detection and send the message/checksum to a receiver using sockets.

## Files
- `error_client.py`
- `error_server.py`

These files are shared with the CRC and Hamming topics. Run only one test at a time; restart the server before each test because it handles one request and exits.

## Run on Windows PowerShell
Terminal 1:
```powershell
py error_server.py
```
Terminal 2:
```powershell
py error_client.py
```
Choose `1`, then enter a message.

## Expected output
The receiver prints the transmitted checksum and its calculated checksum. If they agree, it reports `VALID`.

## How to verify
Run a normal message first. To demonstrate corruption, alter the received data or checksum before the receiver compares them; the comparison should fail.

## Performance metrics (if asked)
- Detection rate = corrupted messages detected / corrupted messages tested × 100%.
- Processing time = verification finish time − verification start time.
- These require repeated test cases to measure meaningfully.

## Viva questions
See `VIVA.md`.
## Metrics printed by the code
Client prints processing/round-trip time and whether checksum validation succeeded or corruption was detected.
