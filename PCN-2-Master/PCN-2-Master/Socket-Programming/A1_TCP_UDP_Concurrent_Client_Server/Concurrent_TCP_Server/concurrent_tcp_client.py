import socket, time
HOST, PORT = "127.0.0.1", 5002
message = input("Enter message: ").encode()
start = time.perf_counter()
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect((HOST, PORT))
    client.sendall(message)
    reply = client.recv(4096)
elapsed = time.perf_counter() - start
print("Server:", reply.decode(errors="replace"))
print(f"Response time (connect/send/reply): {elapsed*1000:.2f} ms")
print(f"Application throughput (reply bytes / elapsed time): {len(reply)/elapsed/1024:.2f} KiB/s" if elapsed else "Throughput: N/A")
