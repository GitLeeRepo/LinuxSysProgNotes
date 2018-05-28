//  unix_socket_clnt.c
//  
//  Unix client socket, using tmpfs, for ipc on the same host.  Waits for stdio
//  and sends it to the server.
//
//  Use this in conjunctions with: unix_socket_srv.c

#include "../commonlib/common.h"
#include "socket.h"

int main(int argc, char *argv[]) {
    struct sockaddr_un addr;
    int socketfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    // create socket
    socketfd = socket(AF_UNIX, SOCK_STREAM, 0);      
    if (socketfd == -1)
        die("socket error");

    // initialize address structure
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // connect socket to address
    if (connect(socketfd, (struct sockaddr *) &addr,
                sizeof(struct sockaddr_un)) == -1)
        die("connect error");


    // read from stdin and write to the socket
    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
        if (write(socketfd, buf, numRead) != numRead)
            die("write error");

    if (numRead == -1)
        die("read error");

    exit(0);         
}

