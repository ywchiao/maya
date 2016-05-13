
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/select.h>
#include <sys/socket.h>

#include <sys/types.h>

#include "login.h"
#include "message.h"
#include "ui.h"

#include "user.h"

void main_loop(int fd_socket) {
    int in_streams;
    int fd_max;
    char buf_send[BUF_SIZE];
    char buf_recv[BUF_SIZE];

    fd_set fdset;

    while (1) {
        FD_ZERO(&fdset);
        FD_SET(0, &fdset);
        FD_SET(fd_socket, &fdset);

        fd_max = fd_socket;

        in_streams = select(
            fd_max + 1, &fdset,
            (fd_set *)NULL, (fd_set *)NULL, (struct timeval *)NULL
        );

        if (in_streams < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        } // fi

        if (FD_ISSET(0, &fdset)) {
            memset(buf_send, 0, BUF_SIZE);
            fgets(buf_send, BUF_SIZE - 1, stdin);

            msg_send(fd_socket, buf_send, strlen(buf_send) + 1);
        } // fi

        if (FD_ISSET(fd_socket, &fdset)) {
            msg_recv(fd_socket, buf_recv, BUF_SIZE);
        } // fi
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
