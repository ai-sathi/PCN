# A6 — DNS Database and Name Resolution

## Exact exam question
Develop an application that simulates DNS using a database, name resolution and error handling for unknown domain names.

## Files
- `dns_server.py` — holds a small domain-to-IP dictionary and answers UDP requests.
- `dns_client.py` — sends a domain name and prints the result.

## Run on Windows PowerShell
Terminal 1:
```powershell
py dns_server.py
```
Terminal 2:
```powershell
py dns_client.py
```

Try:
- `example.com` → `93.184.216.34`
- `localhost` → `127.0.0.1`
- `unknown.invalid` → `ERROR: domain not found`

## How to verify
Run all three lookups and confirm that known names return their configured addresses and unknown names return an error.

## Performance metrics (if asked)
- Lookup response time = response arrival time − query send time.
- Success rate = successful lookups / total lookups × 100%.
- Query throughput = completed lookups / elapsed time.

## Limitation
This is a simplified DNS-like lookup over UDP, not the complete DNS protocol.

## Viva questions
See `VIVA.md`.
## Metrics printed by the code
DNS client prints lookup response time and success rate for its single query (0% or 100%).
