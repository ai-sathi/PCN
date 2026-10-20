# Performance Metrics — Socket Programming

Use these only when the question asks for performance measurement.

- **RTT:** response/ACK receive time − request send time.
- **Average RTT:** sum of RTT samples / number of samples.
- **Throughput (bit/s):** successfully received payload bits / elapsed seconds.
- **PDR (%):** unique messages/packets received / messages/packets sent × 100%.
- **Packet loss rate (%):** lost packets / packets sent × 100%.
- **Retransmission count:** number of repeated sends after a timeout.
- **HTTP body throughput:** downloaded body bytes × 8 / download time.
- **DNS success rate (%):** successful lookups / total lookups × 100%.
- **Error detection rate (%):** corrupted messages detected / corrupted messages tested × 100%.

For a meaningful rate, run multiple trials and report measured values; do not invent results.


The updated socket examples now print the relevant metrics where applicable. These are application-level measurements on localhost, useful for the lab demonstration; they are not substitutes for network-wide measurements from Wireshark/NS-3. RTT and throughput can vary between runs.
