
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>

#define BUF_SIZE 128

int login(char *ip, char *port) {
    int fd_socket;
    long port_number = strtol(port, NULL, 0);

    struct sockaddr_in servaddr;

    fd_socket=socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port_number);

//    inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));
    inet_pton(AF_INET, ip, &(servaddr.sin_addr));

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

int main(int argc, char *argv[]) {
    int fd_socket;

    char buf_send[BUF_SIZE];
    char buf_recv[BUF_SIZE];

    fd_socket = login(argv[1], argv[2]); // 1: ip, 2: port

    while (1) {
        msg_recv(fd_socket, buf_recv, BUF_SIZE);

        memset(buf_send, 0, BUF_SIZE);
        fgets(buf_send, BUF_SIZE - 1, stdin);

        msg_send(fd_socket, buf_send, strlen(buf_send) + 1);
    } // while
} // main

// client.c
