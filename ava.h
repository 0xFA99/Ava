#include <stdint.h>

typedef struct {
    short   sin_family;
    short   sin_port;
    int     sin_addr;
    double  sin_zero;
} sockaddr_in;

uint16_t hostshort = 8080;
const char *cp = "64.233.164.94";
