//  tcp_socket_clnt.c
//  
//  Network socket, currently using localhost, for ipc on the same host.  Waits for stdio
//  and sends it to the server.
//
//  Use this in conjunctions with: tcp_socket_srv.c

#include "unix_socket.h"


void die(char *msg) {
    printf("%s\n", msg);
    exit(5);
}

int main(int argc, char *argv[]) {
    struct sockaddr_in addr;
    int socketfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);      
    if (socketfd == -1)
        die("socket error");


    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr =  inet_addr("127.0.0.1");
    addr.sin_port = INET_PORT;

    if (connect(socketfd, (struct sockaddr *) &addr,
                sizeof(struct sockaddr_un)) == -1)
        die("connect error");


    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
        if (write(socketfd, buf, numRead) != numRead)
            die("write error");

    if (numRead == -1)
        die("read error");

    exit(0);         
}
