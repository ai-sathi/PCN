import socket, time
HOST, PORT = "127.0.0.1", 53535
domain = input("Enter domain (e.g. example.com): ").strip()
start = time.perf_counter()
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client:
    client.settimeout(3); client.sendto(domain.encode(), (HOST, PORT))
    try:
        reply, _ = client.recvfrom(1024); elapsed = time.perf_counter() - start
        answer = reply.decode(); print("DNS response:", answer)
        success = not answer.startswith("ERROR:")
        print(f"Lookup response time: {elapsed*1000:.2f} ms")
        print(f"Lookup success rate for this query: {100 if success else 0:.0f}%")
    except socket.timeout:
        elapsed = time.perf_counter() - start
        print("DNS server timed out.")
        print(f"Lookup response time until timeout: {elapsed*1000:.2f} ms")
        print("Lookup success rate for this query: 0%")
