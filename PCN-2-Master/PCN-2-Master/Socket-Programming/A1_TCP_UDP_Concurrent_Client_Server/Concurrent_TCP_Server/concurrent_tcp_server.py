import socket, threading
HOST, PORT = "127.0.0.1", 5002
count_lock = threading.Lock()
clients_handled = 0

def handle_client(conn, addr):
    global clients_handled
    with conn:
        print("Connected:", addr)
        data = conn.recv(4096)
        if data:
            message = data.decode(errors="replace")
            conn.sendall(("Echo: " + message).encode())
            with count_lock:
                clients_handled += 1
                print(f"Clients handled so far: {clients_handled}")
        print("Disconnected:", addr)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT)); server.listen()
    print(f"Concurrent TCP server listening on {HOST}:{PORT}")
    print("Run multiple clients in separate terminals.")
    while True:
        conn, addr = server.accept()
        threading.Thread(target=handle_client, args=(conn, addr), daemon=True).start()
