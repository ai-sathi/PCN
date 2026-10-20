import socket, time
HOST, PORT = "127.0.0.1", 8000
PATH = "/index.html"
start = time.perf_counter()
with socket.create_connection((HOST, PORT), timeout=5) as client:
    request = (f"GET {PATH} HTTP/1.1\r\nHost: {HOST}:{PORT}\r\nConnection: close\r\n\r\n")
    client.sendall(request.encode("ascii"))
    chunks = []
    while True:
        data = client.recv(4096)
        if not data: break
        chunks.append(data)
elapsed = time.perf_counter() - start
response = b"".join(chunks)
headers, sep, body = response.partition(b"\r\n\r\n")
print(headers.decode("iso-8859-1", errors="replace"))
if b" 200 " not in headers: print("Warning: server did not return HTTP 200 OK.")
with open("downloaded.html", "wb") as f: f.write(body)
print(f"Saved {len(body)} body bytes to downloaded.html")
print(f"Download time (including connection): {elapsed*1000:.2f} ms")
print(f"Application throughput (body size / elapsed time): {len(body)/elapsed/1024:.2f} KiB/s" if elapsed else "Throughput: N/A")
