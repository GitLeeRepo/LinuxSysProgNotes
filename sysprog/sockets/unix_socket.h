#include <sys/un.h>
#include <sys/socket.h>
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

#define BUF_SIZE 120
