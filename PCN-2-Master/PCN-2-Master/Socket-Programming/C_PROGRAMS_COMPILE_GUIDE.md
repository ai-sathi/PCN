# C Socket Programs — Compile and Run (Linux/Ubuntu/WSL)

All Python socket programs in this package have been replaced with C source files. NS-3 programs were already C++ (`.cc`) and remain unchanged.

## Requirements
Install GCC and pthread support (usually included): `sudo apt install build-essential`.

## Run rule
Open two terminals in the same experiment folder. Compile each source file, run the server first, then run the client. Example TCP:

```bash
gcc tcp_server.c -o tcp_server
./tcp_server
```

In the second terminal:

```bash
gcc tcp_client.c -o tcp_client
./tcp_client
```

For the concurrent TCP server, compile with `-pthread`:

```bash
gcc concurrent_tcp_server.c -o concurrent_tcp_server -pthread
./concurrent_tcp_server
```

Compile the matching client in another terminal. For each experiment, use the filenames in that folder, for example `gcc dns_server.c -o dns_server`.

## Important
These socket examples use POSIX sockets and are intended for Linux/Ubuntu/WSL (common for networking labs and NS-3). They do not compile unchanged with native Windows MSVC because Windows uses Winsock.
