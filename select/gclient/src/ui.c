
#include <string.h>
#include <stdio.h>

#include "ui.h"

void usage(void) {
    char *msgs[] = {
        "Maya Client ver 0.0.0",
        "    Usage: user [options]"
    }; // msgs[]

    for (unsigned i = 0; i < sizeof(msgs) / sizeof(char *); ++ i) {
        printf("%s\n", msgs[i]);
    } // od
} // usage()

int getCommPort(int argc, char *argv[], struct CommPort *comm_port) {
    int ok = 0;

    for (int i = 0; i < argc; ++ i) {
        if (strcmp("-a", argv[i]) == 0) {
            // ip address
            comm_port->ip_addr = argv[i + 1];
        }

        if (strcmp("-p", argv[i]) == 0) {
            // port number
            comm_port->port_number = argv[i + 1];
        } // esle

        if (strcmp("-h", argv[i]) == 0) {
            // help
//            print_help();
        }
    } // for

    return ok;
} // getCommPort()

// ui.c
