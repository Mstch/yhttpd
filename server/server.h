#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 6666
#define THREAD_NUM(num) th##num

struct Args{
    int sockfd;
};

int Socket(int __domain, int __type, int __protocol);
int Bind(int __sockfd, const struct sockaddr* __addr, socklen_t __addrlen);
int Listen(int __sockfd, int __backlog);
int Accept(int __sockfd, struct sockaddr* __addr, socklen_t* __addrlen);
void* server_thread(void* args);
// int SendMsg(int __sockfd, const struct msghdr* __msg, int __flags);
// int RecvMsg(int __sockfd, const struct msghdr* __msg, int __flags);
// int Close(int __fd);
