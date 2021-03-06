
#include <stdio.h>
#include <string.h>

#include "buffer.h"

static int head = 0;
static int tail = 0;

static char buffer[MAX_MESSAGES][LEN_MESSAGE];

char * next_buffer() {
    char * msg_buffer = NULL;

    head = (head + 1) % MAX_MESSAGES;

    if (head != tail) {
        msg_buffer = buffer[head];
    } // fi

    return msg_buffer;
} // msg_buffer()

char *next_msg() {
    char * msg_buffer = NULL;

    if (head != tail) {
        tail = (tail + 1) % MAX_MESSAGES;

        msg_buffer = buffer[tail];
    }

    return msg_buffer;
} // next_msg()

// buffer.c
