/*
// Created by mpressig on 03/11/2021.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "image.h"
#include <math.h>

/*! \fn ImageSquare* createImageSquare(unsigned int length)
* \brief Allocate a square image structure and its fields. Initialize all pixel values to 0.
* \param[in] length the number of rows (and columns) of this image
* \return ImageSquare* the pointer on the new image structure
*/
ImageSquare* createImageSquare(unsigned int length)
{
    ImageSquare* imageSquare = (ImageSquare*) malloc(sizeof(ImageSquare));
    if (imageSquare == NULL) {
        fprintf(stderr,"Error: Could not allocate memory for imageSquare.\n");
        return NULL;
    }
    imageSquare->rows = calloc(length ,sizeof(uint16_t*));
    if (imageSquare->rows == NULL) {
        fprintf(stderr,"Error: Could not allocate memory for imageSquare.rows.\n");
        return NULL;
    }
    for (unsigned int i = 0; i < length; i++) {
        imageSquare->rows[i] = calloc(length ,sizeof(uint16_t));
        if (imageSquare->rows[i] == NULL) {
            fprintf(stderr,"Error: Could not allocate memory for imageSquare.rows.\n");
            for (unsigned int j = 0; j < i; j++) {
                free(imageSquare->rows[j]);
            }
            free(imageSquare->rows);
            free(imageSquare);
            return NULL;
        }
    }
    imageSquare->side_size = length;
    return imageSquare;
}

/*! \fn unsigned int getImageSideSize(const ImageSquare * im)
* \brief Returns the number of rows (or columns) of the square image
* \param[in] im a square image already allocated and filled
* \return unsigned int the length
*/
unsigned int getImageSideSize(const ImageSquare * im)
{
    return im->side_size;
}


/*! \fn uint16_t getPixel(const ImageSquare * im, unsigned int row, unsigned int col)
* \brief Returns the pixel value indexed by a row and column number.
* \param[in] im a square image already allocated and filled
* \param[in] row the row index of the pixel
* \param[in] col the column index of the pixel
* \return uint16_t the pixel value
*/
 uint16_t getPixel(const ImageSquare * im, unsigned int row, unsigned int col)
{
    /* to be completed */
    return im->rows[row][col];
}

/*! \fn void setPixel(ImageSquare * im, unsigned int row, unsigned int col, uint16_t pixval)
* \brief Set the pixel value indexed by a row and column number.
* \param[in,out] im a square image already allocated and filled
* \param[in] row the row index of the pixel
* \param[in] col the column index of the pixel
* \param[in] pixval the newvalue of the pixel
*/
 void setPixel(ImageSquare * im, unsigned int row, unsigned int col, uint16_t pixval)
{
    /* to be completed */
    im->rows[row][col] = pixval;
}

/*! \fn void randomlyBinarize(ImageSquare * im)
* \brief Fill the image with pixel whose value is randomly either 0 either 1.
 * At the first call of randomlyBinarize, the random seed is initialized with the current time.
* \param[in,out] im a square image already allocated
* \return unsigned int the pixel value
*/
void randomlyBinarize(ImageSquare * im)
{
    srand(time(NULL));
    /* to be completed */
    for (unsigned int i = 0; i < im->side_size; i++) {
        for (unsigned int j = 0; j < im->side_size; j++) {
            int randvalue = rand() % 2;
            setPixel(im, i, j, randvalue);
        }
    }
}

/*! \fn void displayImageSquare(const ImageSquare * im)
* \brief Display on standard output as a matrix the image content
* \param[in] im a square image already allocated
*/
void displayImageSquare(const ImageSquare * im)
{
    /* to be completed */
    for (unsigned int i = 0; i < im->side_size; i++) {
        for (unsigned int j = 0; j < im->side_size; j++) {
            printf("%d\t", getPixel(im, i, j));
        }
        printf("\n");
    }
}
/*! \fn unsigned int getImageSideLengthFromFile(const char * filename)
* \brief Estimates the number row (and consequently columns) of the square image stored in a binary file.
 * A pixel is stored on 2 bytes and the file contents all rows consecutively
* \param[in] filename the name of the binary file to be read
* \return unsigned int side length of the square image
*/
unsigned int getImageSideLengthFromFile(const char * filename) {
    /* to be completed */
    FILE* ptr_f = fopen(filename, "rb");
    unsigned int length = 0;
    if (ptr_f == NULL){
        fprintf(stderr,"Error: Could not open file %s\n", filename);
        return 0;
    }
    fseek(ptr_f, 0, SEEK_END);
    length = sqrt(ftell(ptr_f)/2);

    if (fclose(ptr_f)) {
        fprintf(stderr,"Error: Could not close file %s\n", filename);
        return 0;
    }
    return length; //length en octet, on veut numero row en savant que chaque row est de 2 bits
}

/*! \fn ImageSquare * loadImageSquare(const char * filename)
* \brief Create an ImageSquare and fill it from file
* \param[in] filename the name of the binary file to be read
* \return ImageSquare* the pointer on the new filled image structure
*/
ImageSquare * loadImageSquare(const char * filename)
{
    /* to be completed */
    FILE* ptr_f = fopen(filename, "rb");
    unsigned int length = getImageSideLengthFromFile(filename);
    if (ptr_f == NULL) {
        fprintf(stderr,"Error: Could not open file %s\n", filename);
        return NULL;
    }

    ImageSquare* im = createImageSquare(length);

    uint16_t pixel = -1;

    for (unsigned int i = 0; i < im->side_size; i++) {
        for (unsigned int j = 0; j < im->side_size; j++) {
            if (fread(&pixel, sizeof(uint16_t), 1, ptr_f) != 1) {
                fprintf(stderr,"Error: Could not read pixel from file %s\n", filename);
                fclose(ptr_f);
                freeImage(im);
                return NULL;
            }
            setPixel(im, i, j, pixel);
        }
    }
    if (fclose(ptr_f)) {
        fprintf(stderr,"Error: Could not close file %s\n", filename);
        return 0;
    }
    return im;
}

/*! \fn void freeImage(ImageSquare * im)
* \brief deallocate memory of an ImageSquare and its fields
* \param[in] im  a imageSquare already allocated
*/
void freeImage(ImageSquare * im)
{
    for (unsigned int i = 0; i < im->side_size; i++){
        free(im->rows[i]);
        im->rows[i] = NULL; //set these pointers to NULL to avoid dangling
    }
    free(im->rows);
    free(im);
    im = NULL;
}