//  tcp_socket_srv.c
//  
//  Network socket, currently set to localhost, for ipc on the same host.  Listens
//  and echos what the client sends.
//
//  Use this in conjunctions with: tcp_socket_clnt.c

#include "unix_socket.h"
#define BACKLOG 5  // size of queued requests

void die(char *msg) {
    printf("%s\n", msg);
    exit(5);
}

int main(int argc, char *argv[]) {
    struct sockaddr_in addr;
    int socketfd, connectfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) 
        die("socket error");

    
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = INET_PORT;

    if (bind(socketfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1)
        die("bind error");

    if (listen(socketfd, BACKLOG) == -1)
        die("listen error");

    while (1) {      

        // Listen on socketfd, creating a new socket connectfd on client connection
        connectfd = accept(socketfd, NULL, NULL);
        if (connectfd == -1)
            die("accept error");

        while ((numRead = read(connectfd, buf, BUF_SIZE)) > 0)
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                die("partial/failed write");

        if (numRead == -1)
            die("read error");

        if (close(connectfd) == -1)
            die("close error");
    }
}
