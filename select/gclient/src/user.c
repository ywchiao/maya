
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "login.h"
#include "message.h"
#include "ui.h"

#include "user.h"

void main_loop(int socket) {
    char buf_send[BUF_SIZE];
    char buf_recv[BUF_SIZE];

    while (1) {
        msg_recv(socket, buf_recv, BUF_SIZE);

        memset(buf_send, 0, BUF_SIZE);
        fgets(buf_send, BUF_SIZE - 1, stdin);

        msg_send(socket, buf_send, strlen(buf_send) + 1);
    } // od
} // main_loop()

int main(int argc, char *argv[]) {
    int fd_socket;

    struct CommPort comm_port = {
        "127.0.0.1",
        "4004"
    }; // struct CommPort

    if (getCommPort(argc, argv, &comm_port)) {
        printf("something wrong!");
        exit(-1);
    }; // fi

    fd_socket = login(comm_port.ip_addr, comm_port.port_number);

    main_loop(fd_socket);
} // main

// client.c
