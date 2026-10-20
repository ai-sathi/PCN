import socket

HOST, PORT = "127.0.0.1", 5000
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT))
    server.listen()
    print(f"TCP server listening on {HOST}:{PORT}")
    conn, addr = server.accept()
    with conn:
        print("Connected by", addr)
        data = conn.recv(4096)
        print("Client:", data.decode(errors="replace"))
        conn.sendall(b"Hello from TCP server")
        print("Reply sent.")
