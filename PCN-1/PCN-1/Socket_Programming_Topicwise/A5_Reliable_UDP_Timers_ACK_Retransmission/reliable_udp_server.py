import socket

HOST, PORT = "127.0.0.1", 5003
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server:
    server.bind((HOST, PORT))
    print(f"Reliable-UDP receiver listening on {HOST}:{PORT}")
    while True:
        packet, addr = server.recvfrom(4096)
        try:
            seq_text, payload = packet.decode().split("|", 1)
            seq = int(seq_text)
        except (ValueError, UnicodeDecodeError):
            server.sendto(b"BAD", addr)
            continue
        print(f"Received sequence={seq}, payload={payload!r}")
        server.sendto(f"ACK|{seq}".encode(), addr)
        if payload == "QUIT":
            print("Receiver stopping.")
            break
