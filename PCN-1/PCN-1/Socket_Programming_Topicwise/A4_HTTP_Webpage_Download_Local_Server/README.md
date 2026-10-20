# A4 — HTTP Webpage Download Using TCP Sockets

## Exact exam question
Develop an HTTP client using TCP sockets to download a webpage from a local HTTP server.

## Files
- `http_client.py` — the client implemented using Python sockets.
- `webroot/index.html` — the test webpage served locally (create this file as below).

## Setup
In this topic folder, create `webroot` and then create `index.html` with:
```html
<html><body><h1>Hello from local HTTP server</h1></body></html>
```

## Run on Windows PowerShell
Terminal 1, from this topic folder:
```powershell
py -m http.server 8000 --directory webroot
```
Terminal 2, from this same topic folder:
```powershell
py http_client.py
```

## Expected output
- Response headers include `HTTP/1.0 200 OK` or equivalent success status.
- The client reports that it saved the body to `downloaded.html`.
- `downloaded.html` contains the HTML body.

## How to verify
Open `downloaded.html` in a browser or text editor. Check that the heading appears.

## Performance metrics (if asked)
- Download time = time when full response received − time request sent.
- Application throughput = body bytes × 8 / download time in seconds.
- Note: this simple client reads until the server closes the connection and requests `Connection: close`.

## Viva questions
See `VIVA.md`.
## Metrics printed by the code
HTTP client prints download time, downloaded body bytes and application throughput.
