# Viva Questions — A3 Concurrent TCP Multiple Clients

**Q1. What is concurrency?**

Handling multiple client connections during overlapping periods.

**Q2. Why use a thread per client?**

A client can be handled without blocking the server from accepting another connection.

**Q3. What is a race condition?**

A result that depends on the unpredictable timing of concurrent operations.

**Q4. What is the limitation of thread-per-client?**

It can consume too many resources with many clients; production servers often use bounded pools or asynchronous I/O.

