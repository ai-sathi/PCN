import socket, time

HOST, PORT = "127.0.0.1", 5004

def ones_complement_checksum(data: bytes) -> int:
    if len(data) % 2:
        data += b"\x00"
    total = 0
    for i in range(0, len(data), 2):
        total += (data[i] << 8) + data[i + 1]
        total = (total & 0xffff) + (total >> 16)
    return (~total) & 0xffff

def crc_remainder(bits: str, polynomial: str) -> str:
    work = list(bits + "0" * (len(polynomial) - 1))
    poly = list(polynomial)
    for i in range(len(bits)):
        if work[i] == "1":
            for j in range(len(poly)):
                work[i + j] = str(int(work[i + j]) ^ int(poly[j]))
    return "".join(work[-(len(poly) - 1):])

def hamming_encode(data_bits: str) -> str:
    m, r = len(data_bits), 0
    while 2**r < m + r + 1:
        r += 1
    n = m + r
    bits = ["0"] * (n + 1)
    i = 0
    for pos in range(1, n + 1):
        if pos & (pos - 1):
            bits[pos] = data_bits[i]
            i += 1
    for p in [2**i for i in range(r)]:
        parity = 0
        for pos in range(1, n + 1):
            if pos & p and pos != p:
                parity ^= int(bits[pos])
        bits[p] = str(parity)
    return "".join(bits[1:])

print("Choose: 1=Checksum, 2=CRC, 3=Hamming")
choice = input("Choice: ").strip()
if choice == "1":
    message = input("Message text: ")
    checksum = ones_complement_checksum(message.encode())
    request = f"CHECKSUM|{checksum}|{message}"
elif choice == "2":
    data = input("Data bits (e.g. 1101): ").strip()
    polynomial = input("Generator bits (e.g. 1011): ").strip()
    codeword = data + crc_remainder(data, polynomial)
    print("Transmitted CRC codeword:", codeword)
    request = f"CRC|{polynomial}|{codeword}"
elif choice == "3":
    data = input("Data bits (e.g. 1011): ").strip()
    codeword = hamming_encode(data)
    print("Transmitted Hamming codeword:", codeword)
    flip = input("Flip a bit position to simulate error (1-based; 0=no error): ").strip()
    if flip.isdigit() and int(flip) > 0:
        pos = int(flip)
        if pos <= len(codeword):
            idx = pos - 1
            codeword = codeword[:idx] + ("1" if codeword[idx] == "0" else "0") + codeword[idx+1:]
    print("Received codeword:", codeword)
    request = f"HAMMING|{codeword}"
else:
    raise SystemExit("Invalid choice")

start = time.perf_counter()
with socket.create_connection((HOST, PORT), timeout=5) as client:
    client.sendall(request.encode())
    receiver = client.recv(4096).decode()
elapsed = time.perf_counter() - start
print("Receiver:", receiver)
print(f"Processing/round-trip time: {elapsed*1000:.2f} ms")
if choice == "1":
    print("Detection result:", "PASS (valid data)" if "VALID" in receiver else "PASS (corruption detected)" if "ERROR DETECTED" in receiver else "CHECK RESULT")
elif choice == "2":
    print("Detection result:", "PASS (no error detected)" if "NO ERROR DETECTED" in receiver else "PASS (corruption detected)" if "ERROR DETECTED" in receiver else "CHECK RESULT")
else:
    print("Correction result:", "single-bit error corrected / no error found" if "Syndrome=" in receiver else "CHECK RESULT")
