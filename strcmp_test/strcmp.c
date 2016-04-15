
#include <string.h>

#include <stdio.h>

int main(int argc, char *argv[]) {
    char *s1 = "this";
    char *s2 = "this is";
    char *s3 = "this is";

    printf("s1: %s\ns2: %s\ns3: %s\n", s1, s2, s3);

    printf("    strcmp(s1, s2) = %d\n", strcmp(s1, s2));
    printf("    strcmp(s2, s1) = %d\n", strcmp(s2, s1));
    printf("    strcmp(s3, s2) = %d\n", strcmp(s3, s2));
}
