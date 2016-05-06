
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/select.h>
#include <sys/socket.h>

#include <sys/types.h>

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
    printf("recv <- %s", msg);
} // msg_recv

void msg_send(int comm, char *msg) {
    write(comm, msg, strlen(msg) + 1);
    printf("send -> %s", msg);
} // msg_send

void reception(int fd_listen, int fd_conns[], int len) {
    int fd_socket;
    char *welcome = "Welcome to the land of OrcA.\n";

    fd_socket = accept(fd_listen, (struct sockaddr *)NULL, NULL);

    msg_send(fd_socket, welcome);

    for (int i = 0; i < len; ++ i) {
        if (fd_conns[i] == 0) {
            fd_conns[i] = fd_socket;

            break;
        }
    } // od
} // reception

int main(int argc, char *argv[]) {
    char buffer[BUF_SIZE];
    char *welcome = "Welcome to the land of Orca.\n";

    int fd_comm;
    int in_streams;
    int fd_max;
    int fd_socket;
    int fd_conns[128];
    int res;
    fd_set fdset_ins;

    printf("Orca server started...\n");

//    fd_comm = reception(argv[1]); // 1: port,  waiting for connection
    fd_comm = init(argv[1]); // 1: port,  waiting for connection
    fd_max = fd_comm;

//    msg_send(fd_comm, welcome);

    memset(&fd_conns, 0, sizeof(fd_conns));

    while (1) {
        FD_ZERO(&fdset_ins);
        FD_SET(fd_comm, &fdset_ins);

        for (int i = 0; i < 128; ++ i) {
            fd_socket = fd_conns[i];

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
            reception(fd_comm, fd_conns, 128);
        } // fi

        for (int i = 0; i < 128; ++ i) {
            fd_socket = fd_conns[i];

            if (FD_ISSET(fd_socket, &fdset_ins)) {
               res = recv(fd_socket, buffer, 128, MSG_DONTWAIT); 
               printf("%d bytes read: %s", res, buffer);          } // fi
        } // od
    } // while
} // main()
