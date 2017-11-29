//  unix_socket_srv.c
//  
//  Unix server socket, using tmpfs, for ipc on the same host.  Listens
//  and echos what the client sends.
//
//  Use this in conjunctions with: unix_socket_clnt.c

#include "unix_socket.h"
#define BACKLOG 5

void die(char *msg) {
    printf("%s\n", msg);
    exit(5);
}

int main(int argc, char *argv[]) {
    struct sockaddr_un addr;
    int socketfd, connectfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    socketfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socketfd == -1) 
        die("socket error");

    if (strlen(SOCKET_PATH) > sizeof(addr.sun_path) - 1) 
       die("Server socket path too long");

    if (remove(SOCKET_PATH) == -1 && errno != ENOENT)
        die("remove error");

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (bind(socketfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
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
