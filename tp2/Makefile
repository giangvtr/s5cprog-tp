CC=gcc
CFLAGS= -Wall -Wextra -MMD
LDFLAGS=
LDLIBS= -lm

all: main

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

main: test.o main.o image.o image-proba.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

include $(wildcard *.d)

clean :
	rm *.d *.o
	rm main
