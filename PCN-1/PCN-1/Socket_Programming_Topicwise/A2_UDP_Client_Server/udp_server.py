import socket
HOST, PORT = "127.0.0.1", 5001
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server:
    server.bind((HOST, PORT))
    print(f"UDP echo server listening on {HOST}:{PORT}")
    while True:
        data, addr = server.recvfrom(4096)
        if data == b"STOP":
            break
        server.sendto(data, addr)
