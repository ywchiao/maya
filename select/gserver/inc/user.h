
#include <stdbool.h>

#define STATE_LOGIN 1

typedef struct user_profile
{
    char nickname[32];
    int fd_socket;
    int state;
} user_profile;

bool user_add(int, char const *);
user_profile const * user_list(void);
void user_init(void);

// user.h
