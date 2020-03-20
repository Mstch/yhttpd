#include "client.h"

int Socket(int __domain, int __type, int __protocol)
{
    int fd = socket(__domain, __type, __protocol);
    if (fd == -1) {
        printf("Socket error!\n");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int Connect(int __sockfd, const struct sockaddr* __addr, socklen_t __addrlen)
{
    int ret = connect(__sockfd, __addr, __addrlen);
    if (ret < 0) {
        printf("Connect error!\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("%s: %s [ip_addr]", argv[0], argv[0]);
        exit(EXIT_SUCCESS);
    }
    int socket_fd, inet_pton_ret;
    char buff[4096] = { '\0' };
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton_ret = inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    if (inet_pton_ret < 0) {
        printf("Inet_pton error!\n");
        exit(EXIT_FAILURE);
    }
    
    socket_fd = Socket(AF_INET, SOCK_STREAM, 0);
    Connect(socket_fd, (struct sockaddr*)&server_addr, (socklen_t)sizeof(server_addr));
    recv(socket_fd, buff, 4096, 0);
    printf("%s\n", buff);
    exit(EXIT_SUCCESS);
}