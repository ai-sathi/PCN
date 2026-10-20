# Viva Questions — A4 HTTP Webpage Download Local Server

**Q1. Why is HTTP download a socket-programming question?**

The client uses a TCP socket to send an HTTP request and receive the HTTP response.

**Q2. What is HTTP GET?**

A request method used to retrieve a resource.

**Q3. Why use CRLF in HTTP headers?**

HTTP/1.x lines are terminated with carriage-return and line-feed; a blank line ends the headers.

**Q4. What does HTTP 200 OK mean?**

The request succeeded.

**Q5. What is the purpose of Connection: close?**

It asks the server to close the connection after the response, making the end of the response easier to detect in this simple client.

