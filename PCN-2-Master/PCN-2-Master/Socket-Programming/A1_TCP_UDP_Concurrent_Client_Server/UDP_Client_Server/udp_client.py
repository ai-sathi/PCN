import socket, time
HOST, PORT = "127.0.0.1", 5001
TOTAL = 10
received, rtts, received_bytes = 0, [], 0
start_all = time.perf_counter()
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client:
    client.settimeout(1)
    for seq in range(1, TOTAL + 1):
        packet = f"packet-{seq}".encode()
        start = time.perf_counter()
        client.sendto(packet, (HOST, PORT))
        try:
            data, _ = client.recvfrom(4096)
            elapsed = time.perf_counter() - start
            if data == packet:
                received += 1; rtts.append(elapsed); received_bytes += len(data)
                print(f"Packet {seq}: ACK/echo received, RTT={elapsed*1000:.2f} ms")
            else:
                print(f"Packet {seq}: unexpected reply")
        except socket.timeout:
            print(f"Packet {seq}: lost (timeout)")
elapsed_all = time.perf_counter() - start_all
loss = TOTAL - received
print(f"Sent={TOTAL}, Received={received}, Lost={loss}")
print(f"PDR: {received/TOTAL*100:.2f}%")
print(f"Packet loss: {loss/TOTAL*100:.2f}%")
print(f"Average RTT: {sum(rtts)/len(rtts)*1000:.2f} ms" if rtts else "Average RTT: N/A")
print(f"Application throughput: {received_bytes/elapsed_all/1024:.2f} KiB/s" if elapsed_all else "Throughput: N/A")
