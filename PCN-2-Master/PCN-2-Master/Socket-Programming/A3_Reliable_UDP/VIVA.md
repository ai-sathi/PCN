# Viva Questions — A5 Reliable UDP Timers ACK Retransmission

**Q1. What is an ACK?**

An acknowledgement indicating that a message or sequence number was received.

**Q2. Why use a timeout?**

To detect that a reply may be missing and decide whether to retransmit.

**Q3. Why use sequence numbers?**

To identify messages and help detect duplicates or out-of-order delivery.

**Q4. What is RTT?**

The elapsed time between sending a request and receiving its response/ACK.

**Q5. Does UDP retransmit automatically?**

No. Retransmission logic must be implemented by the application or another protocol.

