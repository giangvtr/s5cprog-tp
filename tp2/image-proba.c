/*!
* \file image-proba.c
* \brief File implementing the function to read an image and estimate the probabilities
*/
#include <stdio.h>
#include "image-proba.h"
#include "image.h"

/*! \fn int readProbaFromFile(char* name, float pb[NBVALUES])
* \brief Read the square image made of values between 0 and NBVALUES -1, stored as short int.
* \param[in] name the name of the binary file to be read
* \param[out] pb the probabilities array
* \return int 1 if everything is ok, 0 otherwise
*/
int readProbaFromFile(const char* name, float pb[NBVALUES])
{
    /* to be completed */
    FILE* file = fopen(name, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", name);
        return 0;
    }
    unsigned int length = getImageSideLengthFromFile(name)*getImageSideLengthFromFile(name);
    int n;
    uint16_t pixel = -1;

    //initialize tableau pb
    for (n = 0; n < NBVALUES; n++) {
        pb[n] = 0;
    }

    for (unsigned int i = 0; i < length; i++) {
        if (fread(&pixel, sizeof(uint16_t), 1, file) != 1) {
            fprintf(stderr,"Error: Could not read pixel from file %s\n", name);
            fclose(file);
            return -1;
        }
        pb[pixel]++;
    }
    for (unsigned int i = 0; i < NBVALUES; i++) {
        pb[i] = (float)pb[i]/length;
    }
    return 1;
}

