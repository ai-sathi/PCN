import socket

HOST, PORT = "127.0.0.1", 53535
DNS_DB = {
    "example.com": "93.184.216.34",
    "localhost": "127.0.0.1",
    "college.local": "192.168.1.10",
}
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server:
    server.bind((HOST, PORT))
    print(f"Toy DNS server listening on {HOST}:{PORT}")
    print("Database:", DNS_DB)
    while True:
        data, addr = server.recvfrom(1024)
        domain = data.decode(errors="replace").strip().lower()
        result = DNS_DB.get(domain)
        reply = result if result else "ERROR: domain not found"
        print(f"{domain} -> {reply}")
        server.sendto(reply.encode(), addr)
