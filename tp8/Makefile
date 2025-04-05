CC=gcc
CFLAGS= -Wall -Wextra -MMD
LDFLAGS= -lm
LDLIBS=
myprogram = main-Huffman

all: $(myprogram)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(myprogram): $(myprogram).o binary_tree.o list-teacher.o huffman_method-teacher.o image-proba-teacher.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

include $(wildcard *.d)

clean :
	rm -f $(myprogram).o binary_tree.o
	rm -f $(myprogram)
