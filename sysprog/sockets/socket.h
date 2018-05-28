// The include for programs in sockets project 
 
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H   

#include <sys/types.h>  
#include <stdio.h>      
#include <stdlib.h>     
                       
#include <unistd.h>    
#include <errno.h>      
#include <string.h>     


#endif

#define SOCKET_PATH "/tmp/unix_socket"
#define INET_PORT 5025
#define BUF_SIZE 120
