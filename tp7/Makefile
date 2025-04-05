CC=gcc
CFLAGS= -Wall -Wextra -MMD
LDFLAGS= -lm
LDLIBS=
myprogram = main

all: $(myprogram)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(myprogram): $(myprogram).o myDoubleTree.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

include $(wildcard *.d)

clean :
	rm -f $(myprogram).o myDoubleTree.o
	rm -f $(myprogram)
