import socket, time
HOST, PORT = "127.0.0.1", 5003
TIMEOUT_SECONDS, MAX_RETRIES = 1.0, 5
messages = ["First message", "Second message", "Third message", "QUIT"]
total_sent = total_acked = retransmissions = 0
rtts = []; total_bytes = 0
start_all = time.perf_counter()
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client:
    client.settimeout(TIMEOUT_SECONDS)
    for seq, message in enumerate(messages, start=1):
        packet = f"{seq}|{message}".encode(); acknowledged = False
        for attempt in range(1, MAX_RETRIES + 1):
            start = time.perf_counter(); client.sendto(packet, (HOST, PORT)); total_sent += 1
            if attempt > 1: retransmissions += 1
            print(f"Sent seq={seq}, attempt={attempt}")
            try:
                reply, _ = client.recvfrom(1024); elapsed = time.perf_counter() - start
                if reply.decode() == f"ACK|{seq}":
                    print(f"ACK {seq} received; RTT={elapsed*1000:.2f} ms")
                    rtts.append(elapsed); total_acked += 1; total_bytes += len(packet); acknowledged = True; break
            except socket.timeout: print(f"Timeout for seq={seq}; retransmitting...")
        if not acknowledged:
            print(f"Failed after {MAX_RETRIES} attempts; stopping."); break
elapsed_all = time.perf_counter() - start_all
print("\n--- Performance metrics ---")
print(f"Messages acknowledged: {total_acked}/{len(messages)}")
print(f"PDR (ACKed messages / unique messages attempted): {total_acked/len(messages)*100:.2f}%")
print(f"Total transmissions: {total_sent}; retransmissions: {retransmissions}")
print(f"Average RTT: {sum(rtts)/len(rtts)*1000:.2f} ms" if rtts else "Average RTT: N/A")
print(f"Application throughput: {total_bytes/elapsed_all/1024:.2f} KiB/s" if elapsed_all else "Throughput: N/A")
