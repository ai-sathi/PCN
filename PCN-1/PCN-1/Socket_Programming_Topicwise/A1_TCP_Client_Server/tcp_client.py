import socket, time
HOST, PORT = "127.0.0.1", 5000
message = b"Hello from TCP client"
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect((HOST, PORT))
    start = time.perf_counter()
    client.sendall(message)
    reply = client.recv(4096)
    elapsed = time.perf_counter() - start
print("Server:", reply.decode(errors="replace"))
print(f"RTT (send to reply): {elapsed*1000:.2f} ms")
print(f"Application throughput (reply bytes / RTT): {len(reply)/elapsed/1024:.2f} KiB/s" if elapsed else "Throughput: not measurable")
