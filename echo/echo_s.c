
#include <netdb.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#define BUF_SIZE 128

int main() {
    char buffer[BUF_SIZE];

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

    while (1) {
        memset(buffer, 0, BUF_SIZE);

        read(fd_comm, buffer, BUF_SIZE);

        printf("Echoing back - %s", buffer);

        write(fd_comm, buffer, strlen(buffer)+1);
    } // while
} // main()
