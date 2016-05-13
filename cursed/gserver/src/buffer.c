
#include <string.h>

#include "buffer.h"

static int head = 0;
static int tail = 0;

static char buffer[MAX_MESSAGES][LEN_MESSAGE];

char *next_buffer() {
    head = (head + 1) % MAX_MESSAGES;

    return buffer[head];
} // msg_buffer()

char *next_msg() {
    if (head == tail) {
        return NULL;
    } // fi
    else {
        tail = (tail + 1) % MAX_MESSAGES;

        return buffer[tail];
    }
} // next_msg()

// buffer.c
