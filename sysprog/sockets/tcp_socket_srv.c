//  tcp_socket_srv.c
//  
//  Network socket, currently set to localhost, for ipc on the same host.  Listens
//  and echos what the client sends.
//
//  Use this in conjunctions with: tcp_socket_clnt.c

#include "../commonlib/common.h"
#include "socket.h"
#define BACKLOG 5  // size of queued requests

int main(int argc, char *argv[]) {
    struct sockaddr_in addr;
    int socketfd, clientfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    // create socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) 
        die("socket error");


    // initialize address structure
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // alternative use const INADDR_ANY (0.0.0.0)
    addr.sin_port = htons(INET_PORT);  //htons to ensure network and host byte order the same

    // bind socket to address
    if (bind(socketfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1)
        die("bind error");

    // listen on this socket
    if (listen(socketfd, BACKLOG) == -1)
        die("listen error");

    while (1) {      

        // accept a client connectin, giving it a file descriptor
        // execution pauses here until client accepted
        clientfd = accept(socketfd, NULL, NULL);
        if (clientfd == -1)
            die("accept error");

        // read from the client socket
        // execution stays here until client closes connection
        while ((numRead = read(clientfd, buf, BUF_SIZE)) > 0)
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                die("write error");

        if (numRead == -1)
            die("read error");

        if (close(clientfd) == -1)
            die("close error");
    }
}

