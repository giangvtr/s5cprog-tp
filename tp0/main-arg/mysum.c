#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[], char* arge[])
{
	int i;
    long sum = 0;
	for (i=1 ; i<argc ; ++i){
		char * endstring; //le pointeur vers ou il pose le probleme de parse
        int nb = strtoll(argv[i],&endstring,10);
        sum += nb;
    }
    printf("Sum = %ld\n", sum);
	return 0;
}
