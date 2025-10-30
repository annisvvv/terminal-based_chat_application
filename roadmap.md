# Roadmap for Learning C Socket Programming

## 1. Understand the Basics

*   **What is a Socket?** A socket is one endpoint of a two-way communication link between two programs running on the network.
*   **Client-Server Model:** Most network communication happens between a *server* (a program that provides a service) and a *client* (a program that connects to the server to use that service).
*   **IP Addresses and Ports:** An IP address identifies a machine on a network, and a port number identifies a specific application or service on that machine. Think of the IP address as the address of an apartment building and the port number as the apartment number.
*   **TCP vs. UDP:**
    *   **TCP (Transmission Control Protocol):** Provides reliable, ordered, and error-checked delivery of a stream of bytes. It's like making a phone call; you establish a connection, and the conversation flows back and forth.
    *   **UDP (User Datagram Protocol):** Provides a much simpler, connectionless model. It's like sending a postcard; you send it off and hope it gets there, but there's no guarantee.

## 2. The Core Functions and Headers

On Windows, you'll need to include the `winsock2.h` header and link against the `ws2_32.lib` library. The core functions you'll use are:

*   `WSAStartup()`: Initializes the Winsock library.
*   `socket()`: Creates a new socket.
*   `bind()`: Associates a socket with a specific IP address and port.
*   `listen()`: Puts a server socket in a state where it is listening for incoming connections.
*   `accept()`: Accepts an incoming connection from a client.
*   `connect()`: Establishes a connection to a server.
*   `send()` and `recv()`: Send and receive data over a socket.
*   `closesocket()`: Closes a socket.
*   `WSACleanup()`: Cleans up and terminates the use of the Winsock library.

## 3. Byte Order

*   Understand the difference between Big-endian and Little-endian byte order.
*   Learn about the functions `htons()`, `htonl()`, `ntohs()`, `ntohl()` for converting between host and network byte order.

## 4. Building a Simple TCP Client & Server

*   **Server Steps:**
    1.  Create a socket.
    2.  Bind the socket to an IP address and port.
    3.  Listen for incoming connections.
    4.  Accept a connection.
    5.  Receive data from the client.
    6.  Send a response to the client.
    7.  Close the connection.
*   **Client Steps:**
    1.  Create a socket.
    2.  Connect to the server's IP address and port.
    3.  Send data to the server.
    4.  Receive a response from the server.
    5.  Close the connection.

## 5. Building a Simple UDP Client & Server

*   Learn the key differences in implementation for UDP (it's connectionless).
*   Use the `sendto()` and `recvfrom()` functions for communication.
