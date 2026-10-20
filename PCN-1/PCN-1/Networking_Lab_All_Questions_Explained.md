# Networking Lab Exam --- All Practice Questions Explained

One reference file for Socket Programming, NS-3 Wired and NS-3 Wireless

Purpose: This file explains what each listed practice question asks you
to build, the main steps, the outputs/metrics to prepare, and the key
concepts to know. It is a question guide, not a replacement for the
individual program code or your NS-3 cheat sheet.

## A. Socket Programming --- 9 practice questions

### S1. TCP client-server

What the question asks: Develop a TCP server and client that establish a
connection, exchange a message, and return a reply.

Main steps:

1.  Create a TCP socket on the server, bind it to an IP address and
    port, listen, and accept a connection.

2.  The client connects to the server and sends a message.

3.  The server receives the message, processes it, sends a response, and
    closes the connection cleanly.

Expected demonstration: client message and server reply appear in the
terminal. Know TCP's connection-oriented, reliable byte-stream behavior.

Metrics to prepare: RTT (time for request and response) and optional
application throughput.

### S2. UDP client-server

What the question asks: Develop a UDP client and server that exchange
datagrams without establishing a TCP-style connection.

Main steps:

1.  Create UDP sockets on both sides.

2.  The client sends a datagram to the server's IP address and port.

3.  The server receives it and replies to the sender's address.

Expected demonstration: the server prints the received message and the
client prints the reply. UDP is connectionless and does not itself
guarantee delivery or order.

Metrics to prepare: RTT; if sending multiple packets, packet delivery
ratio (PDR), packet loss and throughput.

### S3. Concurrent TCP server for multiple clients

What the question asks: Extend a TCP server so multiple clients can be
served at the same time instead of handling only one client at a time.

Main steps:

1.  The server listens for incoming connections.

2.  For each accepted client, create a separate thread or equivalent
    concurrent handler.

3.  Run multiple clients and show that the server responds to each.

Expected demonstration: two or more clients connect and exchange
messages without waiting for the previous client to finish. Know the
purpose of threads and client handlers.

Metrics to prepare: response time, approximate throughput, and number of
clients/requests handled.

### S4. HTTP webpage download using TCP sockets and a local HTTP server

What the question asks: Build a socket-based HTTP client that connects
to a local HTTP server, sends an HTTP GET request and saves the webpage
response.

Main steps:

1.  Create an index.html page in a local directory.

2.  Start a local HTTP server and connect to its host and port with a
    TCP socket.

3.  Send a correctly formatted GET request, read the response, separate
    headers from the body, and save the HTML body to a file.

Expected demonstration: the client downloads the local webpage and the
saved file contains the HTML. Understand HTTP request lines, headers,
response status and TCP transport.

Metrics to prepare: download duration, bytes downloaded and approximate
throughput.

### S5. Timers, ACKs, timeouts and retransmissions

What the question asks: Implement a simple reliable-transfer
demonstration on top of UDP, where the sender resends data if an
acknowledgement is not received in time.

Main steps:

1.  Attach a sequence number to each data packet.

2.  The receiver replies with an ACK for the sequence number.

3.  The sender starts a timer; if the ACK arrives, proceed to the next
    packet, otherwise timeout and retransmit.

Expected demonstration: ACKs are printed; a timeout can trigger a
retransmission. Know why UDP needs extra logic for reliability and how
sequence numbers help identify packets.

Metrics to prepare: RTT, retransmission count, PDR and approximate
throughput. A teaching demo is not a full implementation of TCP.

### S6. DNS database, name resolution and error handling

What the question asks: Create a simplified DNS-like service that maps
domain names to IP addresses and reports unknown names.

Main steps:

1.  Store domain-to-IP entries in a server-side dictionary or database.

2.  The client sends a domain name to the server.

3.  The server returns the matching IP address or a clear
    not-found/error response.

Expected demonstration: a known domain returns its configured IP; an
unknown domain returns an error. This is a simulation, not a complete
standards-compliant DNS server.

Metrics to prepare: lookup response time and success rate.

### S7. Checksum

What the question asks: Use a checksum to detect whether data changed
during transmission.

Main steps:

1.  The sender calculates a checksum from the message and sends both the
    message and checksum.

2.  The receiver recalculates or verifies the checksum.

3.  The receiver reports whether the received data passes validation.

Expected demonstration: valid data passes; altered data should fail the
check. Know that checksum detects errors but does not generally correct
them.

Metrics to prepare: validation/detection success; timing only if
specifically requested.

### S8. CRC (Cyclic Redundancy Check)

What the question asks: Implement CRC using modulo-2 division and a
generator bit pattern to detect transmission errors.

Main steps:

1.  Represent the message as bits.

2.  Append zero bits as required by the generator degree and perform
    modulo-2 division using XOR.

3.  Append the remainder to form the transmitted codeword; at the
    receiver, divide/check the received codeword and inspect the
    remainder.

Expected demonstration: a valid codeword produces a zero remainder under
the chosen convention; a changed bit should normally be detected. Know
the generator polynomial and XOR-based division.

Metrics to prepare: error-detection success; timing only if requested.

### S9. Hamming code

What the question asks: Add parity bits to data so a receiver can
identify and correct a single-bit error under the standard Hamming-code
assumptions.

Main steps:

1.  Place parity bits at power-of-two positions.

2.  Calculate the parity bits and form the codeword.

3.  At the receiver, recalculate parity checks to obtain the syndrome
    and correct the indicated bit if the syndrome identifies one.

Expected demonstration: a deliberately flipped single bit is located and
corrected. Know the parity positions, syndrome and the limitation that
basic Hamming code corrects one-bit errors.

Metrics to prepare: correction success; timing only if requested.

## B. NS-3 Wired --- 6 practice questions

### W1. Create wired nodes, links, IP addressing and routing

What the question asks: Create a wired topology with multiple nodes and
point-to-point links, install the Internet stack, assign IP subnets and
configure routing.

Main steps:

1.  Create nodes using NodeContainer.

2.  Connect nodes with PointToPointHelper and configure DataRate and
    Delay.

3.  Install InternetStackHelper, assign addresses with
    Ipv4AddressHelper, and populate routes.

Expected demonstration: the topology is configured and traffic can
travel between reachable nodes. Understand nodes, NetDevices, channels,
interfaces and routing tables.

### W2. Simulate TCP/UDP traffic and enable tracing

What the question asks: Generate TCP and UDP application traffic over
the wired topology and record packet-level behavior.

Main steps:

1.  Install suitable sender and receiver applications, such as
    OnOff/PacketSink or UDP echo applications.

2.  Configure ports, packet sizes, data rates and start/stop times.

3.  Enable PCAP tracing and/or FlowMonitor, then run the simulation.

Expected demonstration: traffic flows from sender to receiver and trace
files are generated. PCAP is useful for packet inspection in Wireshark;
FlowMonitor gives flow-level statistics.

### W3. Calculate throughput, delay, packet loss and retransmissions

What the question asks: Collect and report network performance measures
from the simulation.

Main steps:

1.  Use FlowMonitor statistics to inspect transmitted/received packets,
    delay sum and received bytes.

2.  Calculate throughput as received bits divided by observation time.

3.  Calculate average delay as delay sum divided by received packets.

4.  Calculate PDR as received packets divided by transmitted packets
    times 100; interpret lost-packet counters carefully.

5.  Inspect TCP packet traces for retransmissions if the question
    specifically asks for them.

Expected demonstration: print measured values and explain what they
mean. Important: FlowMonitor's basic IP-level counters do not provide a
reliable exact TCP retransmission count; do not equate Tx minus Rx with
retransmissions.

### W4. Vary bottleneck bandwidth, queue size and propagation delay

What the question asks: Run the same topology under different network
settings and compare the results.

Main steps:

1.  Change one variable at a time, for example bottleneck bandwidth 2, 5
    and 10 Mbps.

2.  Test different queue sizes such as 20, 50 and 100 packets.

3.  Test propagation delays such as 5, 10, 20 and 50 ms.

4.  Record throughput, delay, packet loss and TCP trace behavior for
    every run.

Expected observation: a tighter bottleneck can increase congestion;
larger queues can reduce drops but may increase queueing delay. Actual
values must come from execution.

### W5. Compare routing protocols under congestion or link failures

What the question asks: Compare routing behavior while keeping topology
and traffic consistent, and change the routing protocol or failure
condition.

Main steps:

1.  Use a routing helper supported by the installed NS-3 version.

2.  Run the same topology/traffic under each supported protocol or under
    a specified link-failure condition.

3.  Compare delivery, delay, loss and route recovery behavior.

Expected demonstration: explain whether the chosen routing method can
find or recover a route after a failure. Do not claim a protocol was
tested unless its module is actually configured. A global-routing
link-failure demo is not automatically an OSPF implementation.

### W6. Compare TCP congestion-control algorithms, where supported

What the question asks: Compare the performance of TCP
congestion-control algorithms while holding the network and traffic
settings constant.

Main steps:

1.  Select a TCP socket type supported by the NS-3 build, such as
    TcpNewReno; try Cubic or BBR only if available.

2.  Run the same topology, bottleneck, packet size and duration for each
    controller.

3.  Compare throughput, delay, loss and TCP trace/retransmission
    behavior.

Expected demonstration: a comparison table with the algorithm names and
actual measured results. Availability of Cubic/BBR depends on the NS-3
version; do not invent results for unsupported controllers.

## C. NS-3 Wireless --- 4 practice questions

### R1. Create a Wi-Fi topology and generate traffic

What the question asks: Build a wireless network, configure Wi-Fi
devices, install IP networking and send traffic between nodes.

Main steps:

1.  Create nodes and configure YansWifiChannelHelper and
    YansWifiPhyHelper.

2.  Configure Wi-Fi MAC and station manager with WifiHelper.

3.  Install InternetStackHelper, assign IP addresses and set initial
    node positions.

4.  Install sender/receiver applications and enable PCAP/FlowMonitor.

Expected demonstration: wireless traffic is received and performance
metrics are printed. Know the roles of Wi-Fi PHY, MAC, channel and
mobility models.

### R2. Simulate node mobility and evaluate performance

What the question asks: Make wireless nodes move during the simulation
and observe how movement affects communication.

Main steps:

1.  Configure a MobilityHelper and a mobility model such as
    RandomWalk2dMobilityModel.

2.  Set movement bounds, speed and simulation duration.

3.  Generate traffic and measure performance while nodes move.

Expected observation: movement may change connectivity, route
availability, loss, delay and throughput depending on the topology and
radio conditions.

### R3. Configure AODV and examine routing changes

What the question asks: Configure AODV routing in a wireless ad-hoc
network and examine how routes are discovered or maintained.

Main steps:

1.  Install AodvHelper through InternetStackHelper before installing the
    stack.

2.  Assign IP addresses and generate traffic between nodes that may need
    multi-hop forwarding.

3.  Enable suitable AODV logs/traces where supported and inspect packet
    delivery before/after topology changes.

Expected demonstration: explain AODV as reactive/on-demand routing and
describe route discovery/maintenance. Route changes should be evidenced
by traces/logs, not inferred only from a final metric.

### R4. Measure throughput, PDR, delay and packet loss under changing wireless conditions

What the question asks: Change a wireless condition and compare measured
performance across runs.

Main steps:

1.  Choose a variable such as node count, mobility speed, traffic rate
    or simulation duration.

2.  Keep other settings fixed while changing the selected variable.

3.  Use FlowMonitor to collect sent/received packets, throughput and
    delay.

4.  Calculate PDR = received packets / transmitted packets × 100%;
    calculate loss carefully and compare actual results.

Expected demonstration: a comparison table and a short explanation of
how the selected wireless condition affected delivery and performance.

## Performance metric formulas

-   Throughput (Mbps) = successfully received bits / observation time /
    1,000,000.

-   Average end-to-end delay = sum of packet delays / number of received
    packets.

-   PDR (%) = received packets / transmitted packets × 100.

-   Packet loss estimate = transmitted packets − received packets, with
    care about FlowMonitor accounting and simulation stop time.

-   RTT = time from sending a request/packet until its reply/ACK is
    received.

-   Retransmission count = count retransmitted packets from appropriate
    protocol traces/logs; do not infer it from Tx − Rx.

## Quick preparation checklist

-   For each socket question, know the socket type, client/server flow,
    exact run commands and expected terminal output.

-   For each NS-3 question, know the topology, helper classes,
    application setup, trace setup and relevant metrics.

-   Run the program and record actual output rather than memorizing
    fabricated numerical values.

-   For parameter comparisons, change one setting at a time and keep the
    other settings identical.

-   Treat the supplied cheat sheet and the exact lab instructions as the
    authority for your exam's required syntax and version.
