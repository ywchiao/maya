
#include <netdb.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>


#define BUF_SIZE 128

int main(int argc, char **argv) {
    int fd_socket;

    char buf_send[BUF_SIZE];
    char buf_recv[BUF_SIZE];

    struct sockaddr_in servaddr;

    fd_socket=socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(4004);

    inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));

    connect(fd_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1) {
        memset(buf_send, 0, BUF_SIZE);
        memset(buf_recv, 0, BUF_SIZE);

        fgets(buf_send, BUF_SIZE, stdin);

        write(fd_socket, buf_send, strlen(buf_send)+1);
        read(fd_socket, buf_recv, BUF_SIZE);
        printf("%s\n", buf_recv);
    } // while
} // main

// client.c
