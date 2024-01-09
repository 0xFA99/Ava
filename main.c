#include <stdio.h>

int
main(int argc, char *argv[])
{
    char opt;
    while ((opt == getopt_long(argc, argv, "", long_opts, NULL)) != -1) {

    }

    return 0;    
}

