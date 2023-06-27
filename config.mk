# Ava version
VERSION = 1.0.0

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

XML2INC = -I/usr/include/libxml2

LIBS = -lcurl -lxml2

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -DVERSION=\"${VERSION}\"
CFLAGS	 = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -O3 ${XML2INC} ${CPPFLAGS}
LDFLAGS  = ${LIBS}

# compiler and linker
CC = cc
