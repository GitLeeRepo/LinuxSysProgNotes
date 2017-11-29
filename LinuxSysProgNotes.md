# Overview

Notes on Linux System Programming.

# References

## Online Books

* [Linux Device Drivers v3](https://lwn.net/Kernel/LDD3/) - print version of the O'Reilly book available [here](https://www.amazon.com/Linux-Device-Drivers-Jonathan-Corbet/dp/0596005903/ref=cm_cr_arp_d_product_top?ie=UTF8).

## My Other Notes

* [UbuntuNotes](https://github.com/GitLeeRepo/UbuntuNotes/blob/master/UbuntuNotes.md#overview) - General Ubuntu info.
* [linux_syscalls.txt](https://github.com/GitLeeRepo/LinuxSysProgNotes/blob/master/linux_syscalls.txt) - list of syscalls.

# Linux System Calls

## Complete List of Linux System Calls

These are the raw (no wrapper) system calls made through interupt 0x80, setting the AX register to the id of the corresponding system call.

Refer to: [linux_syscalls.txt](https://github.com/GitLeeRepo/LinuxSysProgNotes/blob/master/linux_syscalls.txt) for the complete list.

# Sockets

Sockets are an IPC (interprocess communication) mechanism that allows data to be exchanged between application, whether on the same host (as in AF_UNIX Unix Domain type socket) or between different hosts over a network (as in the AF_INET and AF_INET6 type sockets for the IPv4 and IPv6 domains respectively).

## Socket Communication Domains

* **AF_UNIX** - for communicating between applications on the same host using the **sockaddr_un** C address structure.  Referred to as the **UNIX Domain**.  It uses a **path name** instead of the **IP/Port** combination of network addresses.
* **AF_INET** - for communicating between applications on different host (or the same host using the localhost) over the **IPv4** protocol, using the **sockaddr_in** C address structure. It uses **IP/Port** combination for addressing instead of the **path name** addressing of **AF_UNIX**.
* **AF_INET6** - for communicating between applications on different host (or the same host using the localhost) over the **IPv6** protocol, using the **sockaddr_in6** C address structure. It uses **IP/Port** combination for addressing instead of the **path name** addressing of **AF_UNIX**.

## Socket Types

* **Stream sockets** - specified with the (**SOCK_STREAM**) constant, providing reliable, bidirectional, byte stream communications.  Used by the **TCP** protocol and with the **AF_UNIX** UNIX domain file sockets. These are referred to as **connection-oriented** sockets.  They have no concept of **message boundaries**
* **Datagram sockets** - specified with the (**SOCK_DGRAM**) constant.  These maintain **message boundaries** but are unreliable, unordered, containing duplicates.  They are referred to as **connectionless** sockets and are associated with the **UDP (User Datagram Protocol)** and can be used with the **AF_UNIX** UNIX domain file sockets

## Key Socket System Calls

* **socket()** - creates the new socket returning a file descriptor
* **bind()** - binds the address to a socket, through the sockaddr structure (the generic struct cast to by the specific domain ones) and the socket's file descriptor.  Typically used by server (passive socket), rather than **connect()**
* **listen()** - used by stream sockets to accept incomming connections from other sockets
* **accept()** - accepts the connection from a peer, creating a local socket reference to the peer socket.  It is a blocking call that will block further execution until a connection is accepted.
* **connect()** - establishes the connection with another socket. Typically used by client (active socket), rather than **bind()**

I/O is performed with **read()** and **write()**, along with socket specific **send()** and **recv()**.

Typical call sequences:

**Passive socket (server)** call sequence: **socket() -> bind() -> listen() -> accept() -> read() -> (write()** if bidirectional**)**

**Active socket (client)** call sequence: **socket() -> connect() -> write() -> (read()** if bidirectional**)**

