#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[], char* arge[])
{
	int i;
    int pflag = 0;
    long sum = 0;
    long product = 1;
    int c;

    while ((c = getopt (argc, argv, "p")) != -1)
    switch (c)
      {
      case 'p':
        pflag = 1;
        break;
      case '?':
        if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
        return 1;
      default:
        abort ();
      }
    if (argc <= optind) {
        fprintf(stderr, "No arguments provided.\n");
        return 1;
    }

    for (i = optind; i < argc; ++i) {
		char * endstring; //le pointeur vers ou il pose le probleme de parse
        int nb = strtoll(argv[i],&endstring,10);
        if(pflag == 1) product *= nb;
        else sum += nb;
    }
    if(pflag == 1) printf("Result = %ld\n", product);
    else printf("Result = %ld\n", sum);
	return 0;
}
