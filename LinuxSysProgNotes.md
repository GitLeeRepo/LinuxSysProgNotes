# Overview

Notes on Linux System Programming.

# References

## Online Books

* [Linux Device Drivers v3](https://lwn.net/Kernel/LDD3/) - print version of the O'Reilly book available [here](https://www.amazon.com/Linux-Device-Drivers-Jonathan-Corbet/dp/0596005903/ref=cm_cr_arp_d_product_top?ie=UTF8).

## YouTube Videos

* [Unix System Calls](https://www.youtube.com/watch?v=xHu7qI1gDPA&t=2422s) - two part series

## My Other Notes

* [UbuntuNotes](https://github.com/GitLeeRepo/UbuntuNotes/blob/master/UbuntuNotes.md#overview) - General Ubuntu info.
* [linux_syscalls.txt](https://github.com/GitLeeRepo/LinuxSysProgNotes/blob/master/linux_syscalls.txt) - list of syscalls.

# Linux/Unix System Calls

System calls are the primary way in which the operating system kernel exposes the functionality it offers to the **user mode** programs.  It provides the mechanism to run operations in **kernel mode** in order to peform instructions which operate on the hardware, cpu, system memory, etc. that would otherwise be hidden from the **user mode** program.  The system call is moved to within the context of the user program's stack, which eliminates the need of an expensive context switch between the two modes.

Based on two standards:
* **POSIX** - Portable Operating System Interface for Unix
* **SUS** - Single Unix specification

## Types of System Calls

System calls typically used to deal with the following:

* **Processes** 
* **Files**
* **IPC - Interprocess Communication**
  * **Sockets**
  * **Pipes**
  * **Semaphores**
  * **Shared Memory**
  * **Message Queues**
* **Signals**
* **Terminals**
* **Threads**
* **Devices**

## Complete List of Linux System Calls

These are the raw (no wrapper) system calls made through interupt 0x80, setting the AX register to the id of the corresponding system call.

Refer to: [linux_syscalls.txt](https://github.com/GitLeeRepo/LinuxSysProgNotes/blob/master/linux_syscalls.txt) for the complete list.

# Processes

Processes keep track of the following:

* **Address Space** - the virutal address space of the process (shown here from lowest to highest memory locations)
  * **Code**
  * **Initialized Data**
  * **Uninitialized Data**
  * **Heap**
  * **Stack**
  * **Kernel SysCall table**
* **User Ids**
* **File Descriptors**
* **Environment**
* **Current Directory**
* **Root Directory**

## Virtual Memory and Processes

The kernel maintains a **page table** for every processes, which describes the virtual memory of each process, as to whether a page is currently in physical memory or has been swapped to disk.  Pages on x86-32bit are 4096 bytes in size.  On IA-64 they are variable in length, with 16,384 bytes being typical.

## Creation of New Processes

New processes are creating by making a copy of the parent process (file descriptors, environemnt, etc), using **fork()**.  Note that actual data itself is not copied, but a table of references to the parent data, therefore it is a fairly efficient call.

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

## Host and Network Byte Ordering

Because different systems across a network may use different byte ordering of numeric data (big endian vs little endian) there needs to be a mechanism to make sure this numeric data is consistent between host and network.

* **htonl()** - host to network long (32-bit).  Use for IP address assignment on x86/x64 Linux (or use **inet_addr()**).
* **htons()** - host to network short (16-bit).  Use for port assignment on x86/x64 Linux.
* **ntohl()** - network to host long (32-bit)
* **ntohs()** - network to host short (16-bit)

Note: if you don't use **htons()** for the port assignment on x86/x54 Linux the port assigned will not match the port displayed by the **netstat** utility.  For example, assigning port **5025** will display as port **41235** to netstat.  This is easy to see using hex notation, **5025** is **0x13a1 hex**, and **41235** is **0xa113 hex**.  Since every two digits of hex represent a byte you can see the **13** and **a1** are reversed between the two.  But as long as you use this function, the **netstat** result will match the port number assigned.

Note: if you use **inet_addr()** to assign the IP address, you don't need to use **htonl**, since **inet_addr()** performs the conversion for you.

Note: on systems where the network and host order are the same, these functions do not peform any conversion, simply passing the number on unchanged.  Therefore, these functions should be used regardless to provide the greatest portability.


