
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/select.h>
#include <sys/socket.h>

#include <sys/types.h>

#include "buffer.h"
#include "user.h"

#define BUF_SIZE 128

int init(char *port) {
    int fd_socket;
    long port_number = strtol(port, NULL, 0);

    struct sockaddr_in servaddr;

    fd_socket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port_number);

    bind(fd_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(fd_socket, 10);

    return fd_socket;
} // init()

void msg_recv(int comm, char *msg, int size) {
    memset(msg, 0, size);

    read(comm, msg, size);

    msg[strcspn(msg, "\r\n")] = '\0';

    printf("recv <- %s", msg);
} // msg_recv

void msg_send(int comm, char *msg) {
    write(comm, msg, strlen(msg) + 1);

//    fflush(comm);

    printf("send -> %s", msg);
} // msg_send

int reception(int fd_listen) {
    int fd_socket;
    char * welcome = "Welcome to the land of OrcA.\n";

    fd_socket = accept(fd_listen, (struct sockaddr *)NULL, NULL);

    msg_send(fd_socket, welcome);

    return fd_socket;
} // reception

void login_(user_profile * user, char * msg) {
    printf("login_ : %s \n", msg);
    strcpy(user->nickname, msg);

    user->state &= ~(STATE_LOGIN);
} // login_()

int main(int argc, char *argv[]) {
    char buffer[BUF_SIZE];

    char *msg = NULL;
    int fd_comm;
    int in_streams;
    int fd_max;
    int fd_socket;
    int res;
    fd_set fdset_ins;
    user_profile users[128];

    printf("Orca server started...\n");

    fd_comm = init(argv[1]); // 1: port,  waiting for connection
    fd_max = fd_comm;

    memset(&users, 0, sizeof(users));

    while (1) {
        FD_ZERO(&fdset_ins);
        FD_SET(fd_comm, &fdset_ins);

        for (int i = 0; i < 128; ++ i) {
            fd_socket = users[i].fd_socket;

            if (fd_socket != 0) {
                FD_SET(fd_socket, &fdset_ins);

                if (fd_max < fd_socket) {
                    fd_max = fd_socket;
                } // fi
            } // fi
        } // od

        in_streams = select(
            fd_max + 1, &fdset_ins,
            (fd_set *)NULL, (fd_set *)NULL, (struct timeval *)NULL
        );

        if (in_streams < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        } // fi

        if (FD_ISSET(fd_comm, &fdset_ins)) {
            for (int i = 0; i < 128; ++ i) {
                if (users[i].fd_socket == 0) {
                    users[i].fd_socket = reception(fd_comm);
                    users[i].state |= STATE_LOGIN;

                    break;
                } // fi
            } // od
        } // fi
        else {
            for (int i = 0; i < 128; ++ i) {
                fd_socket = users[i].fd_socket;

                if (FD_ISSET(fd_socket, &fdset_ins)) {
                    res = recv(fd_socket, buffer, 128, MSG_DONTWAIT); 
                    // 清掉列尾的換行字元
                    buffer[strcspn(buffer, "\r\n")] = '\0';

                    if (users[i].state & STATE_LOGIN) {
                        login_(&users[i], buffer);
                    } // fi
                    else {
                        printf("%d bytes read: %s", res, msg);

                        msg = next_buffer();
                        sprintf(msg, "%s 說: %s\n", users[i].nickname, buffer);

                        printf("sprintf: %s", msg);
                    } // esle
                } // fi
            } // od
        } // esle

        while ((msg = next_msg())) {
            for (int i = 0; i < 128; ++ i) {
                fd_socket = users[i].fd_socket;

                if (fd_socket != 0) {
                    msg_send(fd_socket, msg);
                } // fi
            } // od
        }
    } // while
} // main()
