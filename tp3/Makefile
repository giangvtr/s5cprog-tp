CC=gcc
CFLAGS= -Wall -Wextra -MMD
LDFLAGS= -lm
LDLIBS=
myprogram = main

all: $(myprogram)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(myprogram): test.o $(myprogram).o imageRGB.o BMPFile.o BMPFile_teacher.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

include $(wildcard *.d)

clean :
	rm -f test.o $(myprogram).o imageRGB.o BMPFile.o
	rm -f $(myprogram)
