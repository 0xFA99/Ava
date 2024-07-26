
#include "ava.h"

int
main(int argc, char *argv[])
{
    ava_init();
    ava_run(argc, argv);
    ava_cleanup();

    return 0;
}

