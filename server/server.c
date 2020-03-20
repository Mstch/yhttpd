#include "server.h"

int Socket(int __domain, int __type, int __protocol)
{
    int fd = socket(__domain, __type, __protocol);
    if (fd == -1) {
        printf("Socket error!\n");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int Bind(int __sockfd, const struct sockaddr* __addr, socklen_t __addrlen)
{
    int ret = bind(__sockfd, __addr, __addrlen);
    if (ret == -1) {
        printf("Bind error!\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Listen(int __sockfd, int __backlog)
{
    int ret = listen(__sockfd, __backlog);
    if (ret == -1) {
        printf("Listen error!\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Accept(int __sockfd, struct sockaddr* __addr, socklen_t* __addrlen)
{
    int fd = accept(__sockfd, __addr, __addrlen);
    if (fd == -1) {
        printf("Accept error!\n");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void* server_thread(void* args)
{
    char* buff = "Hello!\n";
    struct Args* arg = (struct Args*)args;
    send(arg->sockfd, buff, strlen(buff), 0);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int socket_count = 0;
    int server_fd, client_fd;
    struct sockaddr_in servaddr;
    struct Args th_args;
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&th_args, 0, sizeof(th_args));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    server_fd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(server_fd, (struct sockaddr*)&servaddr, (socklen_t)sizeof(servaddr));
    Listen(server_fd, 10);

    while (1) {
        client_fd = Accept(server_fd, (struct sockaddr*)NULL, (socklen_t*)NULL);
        socket_count++;
        th_args.sockfd = dup(client_fd);
        pthread_t THREAD_NUM(socket_count);
        pthread_create(&THREAD_NUM(socket_count), NULL, server_thread, &th_args);
    }
    close(server_fd);
    close(client_fd);
    exit(EXIT_SUCCESS);
}