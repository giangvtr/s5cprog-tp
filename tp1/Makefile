CC=gcc
CFLAGS= -Wall -Wextra -MMD
LDFLAGS=
LDLIBS=

all: main-exprString

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

main-exprString: test.o stack.o main-exprString.o evaluation.o evaluationString.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

include $(wildcard *.d)

clean :
	rm *.d *.o
	rm main-exprString
