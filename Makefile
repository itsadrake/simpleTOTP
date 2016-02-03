CFLAGS := -std=c99 -O2 ${CFLAGS}

all: simpleTOTP.o test

simpleTOTP.o: simpleTOTP.c simpleTOTP.h
	${CC} ${CFLAGS} -c -o $@ $<

test: simpleTOTP.o test.c
	${CC} ${CFLAGS} -lssl -lcrypto -o $@ $+
	./test
