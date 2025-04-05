CC=gcc
CFLAGS= -Wall -Wextra -MMD
LDFLAGS= -lm
LDLIBS=
myprogram = main_testlist

all: $(myprogram)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(myprogram): $(myprogram).o memoryList.o test.o myFunctions.o myAlloc.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

include $(wildcard *.d)

clean :
	rm -f $(myprogram).o memoryList.o test.o myFunctions.o myAlloc.o
	rm -f $(myprogram)
