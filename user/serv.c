
#include <netdb.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#define BUF_SIZE 128

int reception() {
    int fd_socket;
    int fd_comm;

    struct sockaddr_in servaddr;

    fd_socket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(4004);

    bind(fd_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(fd_socket, 10);

    fd_comm = accept(fd_socket, (struct sockaddr *)NULL, NULL);

    return fd_comm;
} // reception

void msg_recv(int comm, char *msg, int size) {
    memset(msg, 0, size);

    read(comm, msg, size);
    printf("recv <- %s", msg);
} // msg_recv

void msg_send(int comm, char *msg) {
    write(comm, msg, strlen(msg) + 1);
    printf("send -> %s", msg);
} // msg_send

int main() {
    char buffer[BUF_SIZE];
    char *welcome = "Welcome to the land of Orca.\n";

    int fd_comm;

    printf("Orca server started...\n");

    fd_comm = reception(); // waiting for connection

    msg_send(fd_comm, welcome);

    while (1) {
        msg_recv(fd_comm, buffer, BUF_SIZE);
        
        msg_send(fd_comm, buffer);
    } // while
} // main()
