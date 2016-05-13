
#include <stdio.h>
#include <string.h>

#include <unistd.h>

void msg_recv(int comm, char *msg, int size) {
    memset(msg, 0, size);

    read(comm, msg, size);
    printf("recv <- %s", msg);
} // msg_recv

void msg_send(int comm, char *msg, int size) {
    write(comm, msg, strlen(msg) + 1);
    printf("send -> %s\n", msg);
} // msg_send()

// message.c
