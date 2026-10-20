import socket

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

def crc_check_remainder(codeword: str, polynomial: str) -> str:
    work = list(codeword)
    poly = list(polynomial)
    for i in range(len(codeword) - len(polynomial) + 1):
        if work[i] == "1":
            for j in range(len(poly)):
                work[i + j] = str(int(work[i + j]) ^ int(poly[j]))
    return "".join(work[-(len(poly) - 1):])

def hamming_encode(data_bits: str) -> str:
    m = len(data_bits)
    r = 0
    while 2**r < m + r + 1:
        r += 1
    n = m + r
    bits = ["0"] * (n + 1)  # 1-based positions
    data_i = 0
    for pos in range(1, n + 1):
        if pos & (pos - 1):
            bits[pos] = data_bits[data_i]
            data_i += 1
    for p in [2**i for i in range(r)]:
        parity = 0
        for pos in range(1, n + 1):
            if pos & p and pos != p:
                parity ^= int(bits[pos])
        bits[p] = str(parity)
    return "".join(bits[1:])

def hamming_correct(code: str):
    bits = ["0"] + list(code)
    n = len(code)
    syndrome = 0
    p = 1
    while p <= n:
        parity = 0
        for pos in range(1, n + 1):
            if pos & p:
                parity ^= int(bits[pos])
        if parity:
            syndrome += p
        p *= 2
    if 0 < syndrome <= n:
        bits[syndrome] = "1" if bits[syndrome] == "0" else "0"
    corrected = "".join(bits[1:])
    data = "".join(corrected[pos-1] for pos in range(1, n+1) if pos & (pos-1))
    return syndrome, corrected, data

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT))
    server.listen()
    print(f"Error-detection server listening on {HOST}:{PORT}")
    conn, addr = server.accept()
    with conn:
        raw = conn.recv(8192).decode()
        mode, payload = raw.split("|", 1)
        if mode == "CHECKSUM":
            sent = int(payload.split("|", 1)[0])
            data = payload.split("|", 1)[1].encode()
            calculated = ones_complement_checksum(data)
            result = f"Received checksum={sent}; calculated checksum={calculated}; " + ("VALID" if sent == calculated else "ERROR DETECTED")
        elif mode == "CRC":
            polynomial, codeword = payload.split("|", 1)
            remainder = crc_check_remainder(codeword, polynomial)
            result = f"Received codeword={codeword}; remainder={remainder}; " + ("NO ERROR DETECTED" if set(remainder) <= {"0"} else "ERROR DETECTED")
        elif mode == "HAMMING":
            syndrome, corrected, data = hamming_correct(payload)
            result = f"Syndrome={syndrome}; corrected codeword={corrected}; extracted data={data}"
        else:
            result = "ERROR: unknown mode"
        conn.sendall(result.encode())
        print(result)
