
#include <stdio.h>

#include <string.h>

#include "user.h"

static user_profile members_[128];

user_profile const * user_list(void)
{
    return members_;
} // user_list()

bool user_add(int fd_socket, char const * nick)
{
    bool entered = false;

    for (int i = 0; i < 128; ++ i)
    {
        if (members_[i].fd_socket == 0)
        {
            members_[i].fd_socket = fd_socket;

            strcpy(members_[i].nickname, nick);

            entered = true;

            break;
        } // fi
    } // od

    return entered;
} // user_add()

void user_init(void)
{
    memset(members_, 0, sizeof(user_profile) * 128);
} // user_init()

// user.c
