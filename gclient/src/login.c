
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include "login.h"

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

// login.c
