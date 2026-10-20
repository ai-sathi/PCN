# Viva Questions — A2 UDP Client Server

**Q1. What is UDP?**

A connectionless transport protocol that sends datagrams without built-in delivery or ordering guarantees.

**Q2. TCP vs UDP?**

TCP provides reliable ordered delivery; UDP has lower protocol overhead but no built-in reliability.

**Q3. What does recvfrom() return?**

The received datagram and the sender's address.

**Q4. Why can UDP lose messages?**

UDP itself does not retransmit lost datagrams or guarantee delivery.

