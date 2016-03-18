
#include <netdb.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>

#define BUF_SIZE 128

int login() {
    int fd_socket;

    struct sockaddr_in servaddr;

    fd_socket=socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(4004);

    inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));

    connect(fd_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));

    return fd_socket;
} // login()

void msg_recv(int comm, char *msg, int size) {
    memset(msg, 0, size);

    read(comm, msg, size);
    printf("recv <- %s", msg);
} // msg_recv

void msg_send(int comm, char *msg, int size) {
    write(comm, msg, strlen(msg) + 1);
    printf("send -> %s\n", msg);
} // msg_send()

int main(int argc, char **argv) {
    int fd_socket;

    char buf_send[BUF_SIZE];
    char buf_recv[BUF_SIZE];

    fd_socket = login();

    while (1) {
        msg_recv(fd_socket, buf_recv, BUF_SIZE);

        memset(buf_send, 0, BUF_SIZE);
        fgets(buf_send, BUF_SIZE - 1, stdin);

        msg_send(fd_socket, buf_send, strlen(buf_send) + 1);
    } // while
} // main

// client.c
