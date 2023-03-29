include config.mk

SRC = answer.c ava.c utils.c
OBJ = ${SRC:.c=.o}

VALGRIND = valrind --leak-check=full --show-leak-kinds=all
VALGRIND_OPTS = -v

all: options ava

options:
	@echo ava build options:
	@echo "CFLAGS	= ${CFLAGS}"
	@echo "LDFLAGS	= ${LDFLAGS}"
	@echo "CC	= ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

ava: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -rf ava ${OBJ} ava-${VERSION}.tar.gz

dist: clean
	mkdir -p ava-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		ava.1 answer.h utils.h ${SRC} ava-${VERSION}
	tar -cf ava-${VERSION}.tar ava-${VERSION}
	gzip ava-${VERSION}.tar
	rm -rf ava-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ava ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/ava
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < ava.1 > ${DESTDIR}${MANPREFIX}/man1/ava.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/ava.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/ava\
		${DESTDIR}${MANPREFIX}/man1/ava.1

valgrind: ${OBJ}
	${VALGRIND} ${VALGRIND_OPTS} ${CC} -o $@ ${OBJ} ${LDFLAGS}

.PHONY: all options clean dist install uninstall
