#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "BMPFile.h"
#include "imageRGB.h"
#include "test.h"

/*!\def MY_FILENAME_MAX
* Taille maximum du nom d'un fichier
*/
#define MY_FILENAME_MAX 24

int main(int argc, char *argv[])
{
    char *lengthvalue = NULL;
    char*endstring;
    int c;
    long int length = 0;

    char filename[MY_FILENAME_MAX];
    ImageRGB* cross = NULL;
    ImageRGB* crossopt = NULL;
    ImageRGB* f = NULL;
    PixelRGB pixel_background = {4,4,4};
    PixelRGB pixel_white = {255,255,255};


    while ((c=getopt(argc,argv,"l:"))!= -1) {
        switch (c){
            case 'l':
                lengthvalue = optarg;
                break;
            case '?':
                if (optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown option character `\\x%x'.\n",
                             optopt);
                return 1;
            default:
                abort();
        }
    }

    if (lengthvalue != NULL) {
        length = strtol(lengthvalue, &endstring, 10);
        if (*endstring != '\0') { // Vérifie si la conversion s'est bien passée
            fprintf(stderr, "Invalid length value: %s\n", lengthvalue);
            return 1;
        }
    }
    /*Uncomment after allocateImage/getWidth/getHeight/getPixel/setPixel implementation*/

    f = allocateImage(200,100);
    display_test_uint("Test allocateImage (getWidth)", 100, getWidth(f));
    display_test_uint("Test allocateImage (getHeight)", 200, getHeight(f));
    display_test_uint("Test allocateImage (getPixel)", 0, getPixel(f, 3, 3).red);
    setPixel(f,3,3,pixel_white);
    display_test_int("Test setPixel", 255, getPixel(f, 3, 3).blue);
    display_test_int("Test setPixel", 255, getPixel(f, 3, 3).green);
    display_test_int("Test setPixel", 255, getPixel(f, 3, 3).red);

    /*Uncomment for question 2*/

    sprintf(filename,"test_allocate.bmp");
    writeBMPFile(filename, f, 1);
    freeImage(f);

    sprintf(filename,"mask.bmp");
    f = readBMPFile(filename,1);
    modifyImage(f,pixel_background,pixel_white);
    sprintf(filename,"result.bmp");
    writeBMPFile(filename,f,1);
    freeImage(f);


    /*Uncomment after createCross implementation*/

    cross = createCross(151);
    sprintf(filename,"cross.bmp");
    writeBMPFile(filename, cross, 1);
    f = readBMPFile(filename,0);
    sprintf(filename,"cross2.bmp");
    writeBMPFile(filename, f, 1);
    freeImage(f);

    crossopt = createCross(length);
    sprintf(filename,"crossopt.bmp");
    writeBMPFile(filename, crossopt, 1);
    freeImage(f);
    //test this by typing ./main -l 200 in the terminal after building by make

    return 0;
}
