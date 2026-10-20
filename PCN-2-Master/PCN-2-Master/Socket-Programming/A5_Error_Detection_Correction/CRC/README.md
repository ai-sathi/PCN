# A8 — CRC Error Detection Using Sockets

## Exact exam question
Implement CRC-based error detection and exchange the CRC codeword through sockets.

## Files
- `error_client.py`
- `error_server.py`

These files are shared with checksum and Hamming. Restart the server before each test.

## Run on Windows PowerShell
Terminal 1:
```powershell
py error_server.py
```
Terminal 2:
```powershell
py error_client.py
```
Choose `2`; enter data bits such as `1101` and generator bits such as `1011`.

## Expected output
The client displays the CRC codeword. The receiver checks the remainder and reports `NO ERROR DETECTED` when the remainder is all zero.

## How to verify
For an error test, flip one bit in the transmitted codeword before the receiver checks it. Many bit errors will produce a nonzero remainder.

## Viva questions
See `VIVA.md`.
## Metrics printed by the code
Client prints processing/round-trip time and whether CRC validation succeeded or corruption was detected.
