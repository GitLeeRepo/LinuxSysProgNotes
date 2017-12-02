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

# Terminology and Concepts

* **APB** - ensures a **binary** compatible interface between applications.  They deal with calling conventions, byte order, register usage, linking, architecture dependent system call methods, etc.
* **API** - ensures a **source** compatible interface between applications.
* **glibc** - the C library on **GNU/Linux** system.  It provides the wrapper functions for the System Calls, among other standard libraries.

# Linux/Unix System Calls

System calls are the primary way in which the operating system kernel exposes the functionality it offers to the **user mode** programs.  It provides the mechanism to run operations in **kernel mode** in order to peform instructions which operate on the hardware, cpu, system memory, etc. that would otherwise be hidden from the **user mode** program.  The system call is moved to within the context of the user program's stack, which eliminates the need of an expensive context switch between the two modes.

At the lower level, system calls in x86 architectures are handled by interupt 0x80, with the **ax** register containing the system call number.  If the sys call has five or less parameters they are passed in registers **ebx, ecx, edx, esi, and edi**.  In the rare case there are more han five a single register is used to point to a memory buffer is user space that contains the paramenters.

At the higher level, these system calls are wrapped in calls handled by the C library (libc, i.e., **glibc** on Linux).  Most higher level languages access the system calls through the **glibc** library, not just C and C++ programs.  Many of the higher level languages and interpreters are written in C and/or C++.

Based on two Unix standards:
* **POSIX** - Portable Operating System Interface for Unix.  Linux supports **POSIX 2008**.
* **SUS** - Single Unix specification. Linux suppors **SUSv4**.

With regards to the C standards, the **gcc C compiler** is **ISO C99** complient, with some support for **C11**, in addition it supports C language extensions, such as inline assembly, tha are referred to as **GNU C**

## Types of System Calls

Linux has a level of abstraction that treats almost everything related to system calls as files, in addition to what are termed **regular files**.  It interfaces with many things, including **sockets**, and **devices**, using **file descriptors** to open and use them.

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

# Files

While Unix/Linux treat many things as files, inlcuding devices and sockets, this section is concerned with **regular files**, **directories**, and **links**.

A linux file system is a **byte oriented** file system, unlike some file systems such as IBM's MVS which is record oriented.  File sizes are mesured in bytes and can have its length adjusted (both increased and decreased) using **truncation**, which in the case of lengthening zero (null) fills the added space.

A single file can be opened multiple times, either from multiple processes or within the same process, with each opened instance of a file given its own **file descriptor**, with a single **file descriptor** also capable of being shared across multiple processes (i.e., opened by one process, but read/written by other processes).

Files and directories are directly accessed by **inodes**, not the filename itself.  Filenames are linked to **inodes** in the **directory** file (remembering the the directory is itself a file, which must also be linked to an **inode**).  The **indode** contains all other information on a file, except for its filename, such as its size, permissions, owner, timestamps, and pointers to the actual disk blocks that contain the files data (a large file will have many pointers to various blocks of data on disk).  **Inodes** are unique to the filesystem, but not unique across filesystems.

**Inodes** for files and directories can be list using the **ls -i** or **ls -li** options.  The number of **inodes** on a given file system is limitted.  You can see the total number and avaiable number of **inodes** on a given filesystem with the following command:

```bash
df -i
```

## Links

* **Hard links** map multiple filenames to the same **inode**, which maintains a count of the number of links to it.  When a **delete** operation is performed on a **filename** it does an **unlink** between a filename and the inode and decrements the link count.  When this link count reaches zero, the **inode** itself is removed.  Because **inodes** can not span multiple filesystems, **hard links** can only be made to files on the same file system.
* **Symbolic links** - a **symbolic link** has its own **inode** and contains the complete path to the file being linked to.  They can link to files on other filesystems.  They can also link to non-existent files which is called a **broken link**

## Special Files

As mentioned earlier, this section is concerned with **regular files*, **directories**, and **links**, but a list of other types of files, called **special files** is mentioned briefly here, they will be dealt with in more detail in their own sections.

Special files are of four types:

* **block devices** - accessed as an **array of bytes** and are typically **storage devices** such as harddisks, cdroms, and flash memory.  Block devices do not need to be accessed in a linear manner, but can be accessed based on the **location within the array of bytes**.
* **character devices** - accessed as a stream of bytes using a queue (FIFO) in a **linear** manner.   They include **keyboards** and **terminals**.
* **named pipes** - a **regular pipe** as used when piping data between programs on the command line is stored in memory, whereas a **named pipe** is a **special file** that can be accessed on the filesystem by multiple processes for **IPC (interprocess communication** purposes.
* **Unix domain sockets** - sockets in general are an **IPC** mechanism for communicating between two proceses, whether on the same host or across a network.  **Unix domain sockets** are used to communicate on the same host and use a **special file** on the file system, whereas **network sockets** are NOT special files on the file system, but rather an address to a host and port.

## Filesystems and Namespaces

A **filesystem** is a collection of files and directories contained within a hierchial **namespace**.  There is a single (root) namespace in which all filesystems are **mounted** to a **mount point** within the root namespace.  There is only one required **root filesystem**, but a system will typically have multiple filesystems.  A filesystem does not have to reside on disk, it can exist in memory or in another network location.

**Filesystems** are block devices with the smallest addressable unit being a **sector**, which must be a **power of 2** size, with **512 bytes** being typical.  The smallest **logically addressable** unit is a **block** which is typically a **power of 2** multiple of the sector size, with **512**, **1024** and **4096** bytes being typical.  The **block** size must be smaller than the **page** sized which is the **virtual memory** swapable files.

# Processes

Processes are executable object code, and its associated data and resources, they keep track of the following:

* **Address Space** - the virutal address space of the process (shown here from lowest to highest memory locations)
  * **Code** - stored in the **text segment** of memory and originating in the binary excuatble file.
  * **Initialized Data** - stored in the **data segment** of memory with the initial values loaded from the binary file.
  * **Uninitialized Data** - stored in the **bss segement** of memory, but not found in the binary file since they are all initilized to zero.
  * **Heap** - dynamically allocated memory
  * **Stack** - local variables and function return addresses
  * **Kernel SysCall table** - stored in **user space** to facilitate calls into **kernel space**
* **User Ids** - for ownership and permissions available to the process
* **File Descriptors** - integer references to open files
* **Environment** - environment variables
* **Current Directory** 
* **Root Directory**

Because Linux is a **pre-emptive multitasking** and **virtual memory** operating system, each process appears to have sole control of the system resources and memory, although the kenel is give multiple process access to the system and its memory through the **scheduler** which gives each process a slice of processor time.

Process are created using a hierarch of process in a parent/child relationship, with all processes being a decendent of the **init** process.  New processes are create with the **fork()** system call which creates a copy of the parent (details in subsequent section).  When the child terminates it returns its status to the parent.  If the parent terminated first, by not properly waiting on the child process to terminate first, the child becomes a **zombie** process that becomes the responsibilty of the **init** process to eventually terminate.

## Threads

Most Unix programs have been **single threaded** since process creation typically has low overhead, and because of IPC mechanism that facilitate interprocess communications.  A **thread** has its own **stack** for storing local variables, processor state and instruction pointer to the current line of execution, but most of the remaining resources are **shared** with other threads in the process, including its virtual address space, meaning they access the same non-locally stored stack data.

## Virtual Memory and Processes

The kernel maintains a **page table** for every processes, which describes the virtual memory of each process, as to whether a page is currently in physical memory or has been swapped to disk.  Pages on x86-32bit are 4096 bytes in size.  On IA-64 they are variable in length, with 16,384 bytes being typical.

## Process Ownership

Each process is associated with a UID (user id) and has the privileges and permissions of that user.  The process actually divides this into three different ids, the **real id** of the owner, the **effective id** which determines the privileges, and the **saved id** which is which is set by **exec** to match the **effective id**.  This division allows certain programs to run with a different privilege if the executable's binary file has a **setuid** bit set. This allows a program to perform a specific task that would otherwise require elevated privileges, without having to give the user themselves those privileges.

## Creation of New Processes

New processes are creating by making a copy of the parent process (stack, data, heap, and text segments, along with file descriptors, environemnt, etc), using **fork()**.  On the other hand **exec()** type functions discards the existing programs stack, data, heap, and text segments.  A **fork()** is often followed by an **exec()** type function, but this is not always the case, and in several cases it is useful to do just a **fork()**.

Note that with the **fork()** even though it receives the parents data, environment, etc., it is a copy, and while they start the same they diverge as each process makes its own changes.  However, the code (text segment) is the same for the two processes and does not diverge.  It is also important to note that each is running in its own **virtual memory space**.

Note for efficiency the actual data itself is not copied from parent to child, but a table of references to the parent data.  So they are initially pointing to the same physical memory location (or page file location) and will remain so as long as the data is not changed by either process.  But once a change does occur these storage locations must diverge into separate physical locations.  This is handled by marking the pages in the new process as **copy on write** which means they will be copied to the new location if they are changed by either process.

Functions for controlling processes:

* **fork()** - the parent process creating a new child process, they both continue run the same program code
* **execve()** - this does NOT create a new proceess, but loads a new program into an existing processes memory, such as in the case of a newly forked child process.  The parents original code and data are discard with a new executable loaded.  It does retain the parents environment and file descriptors.  
* **wait()** - used by a parent to wait on the termination of a child process
* **exit()** - terminates the process

# Signals

**Signals** are a means of **asynchronous notification** to a process to inform it of some event.  They are the means by which the kernel signals the programs of events such as **segmentation faults**.  They can also be used by processes to send a signal to another process.

**Signals** stop the execution of the program performing either a predefined action, such as terminating a program, or calling a user defined handler for that signal.  Some signals such as **SIGKILL** and **SIGSTOP** will always terminate or stop the process, but many other can be handled by the process, including choosing to ignore the signal.

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


