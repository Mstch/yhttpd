#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 6666

int Socket(int __domain, int __type, int __protocol);
int Connect(int __sockfd, const struct sockaddr* __addr, socklen_t __addrlen);