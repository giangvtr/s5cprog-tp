/*!
 * \file imageRGB .c
 * \brief definition of fonctions associated to the RGB Image structure
 * \author ...
 * \date ...
 */

#include "imageRGB.h"


/*!
 * Allocate an image as a rectangle whose size is specified.
 * \param[in] w image width
 * \param[in] h image height
 * \return a pointer on the new image
 */
ImageRGB *allocateImage( unsigned int h, unsigned int w)
{
    /* to be completed*/
    ImageRGB *image = NULL;
    image = (ImageRGB *)malloc(sizeof(ImageRGB));
    if (image == NULL){
      fprintf(stderr, "Image allocation failed\n");
      return NULL;
    }
    image -> height = h;
    image -> width = w;
    image -> raw_data = (PixelRGB *)calloc(h*w, sizeof(PixelRGB));
    if (image -> raw_data == NULL){
      fprintf(stderr, "Image allocation failed\n");
      return NULL;
    }
    return image;
}

/*!
 * \fn unsigned int getWidth(ImageRGB *image)
 * Returns the width of teh image
 * \param[in] image the image
 * \return unsigned int the image width
 */

unsigned int getWidth(ImageRGB *image)
{
    /* to be completed*/
    return image->width;
}

/*!
 * \fn unsigned int getHeight(ImageRGB *image)
 * Returns the height of teh image
 * \param[in] image the image
 * \return unsigned int the image height
 */
unsigned int getHeight(ImageRGB *image)
{
    /* to be completed*/
    return image->height;
}

/*!
 *  Free the memore allocated for a structure
 * \param[in] image ImageRGB to be deleted
 */
void  freeImage(ImageRGB * image) {
    free(image->raw_data);
    image->raw_data = NULL;
    image->height = 0;
    image->width = 0;
    free(image);
    image = NULL;
}

/*!
 * \fn void setPixel(ImageRGB *image, unsigned  int r, unsigned  int c , PixelRGB p)
 *  Copy a Pixel at a specified location in the raw data.
 *  c is the column number, r the row number of the Pixel to be set.
 *  Its position in the raw data is given by (c + r*width) since the rows are stored continuously.
 * \param[out] image ImageRGB to be modified
 * \param[in] c The column number of the Pixel to be set
 * \param[in] r The row number of the Pixel to be set
 * \param[in] p Pixel value to set at this location
 */
void setPixel(ImageRGB *image, unsigned int r, unsigned int c , PixelRGB p)
{
    /* to be completed*/
    image->raw_data[r*image->width + c] = p; //acces a le pixel en clomn c et row r
}

/*!
 * \fn PixelRGB getPixel(ImageRGB *image, unsigned int r, unsigned  int c)
 *  Give the pixel value of  specified location in the raw data.
 *  Its position in the raw data is given by (c + r*width) since the rows are stored continuously.
 * \param[in] image ImageRGB to read
 * \param[in] c The column number of the Pixel to read
 * \param[in] r The row number of the Pixel to read
 * \return PixelRGB Pixel value at this location
 */

PixelRGB getPixel(ImageRGB *image, unsigned int r, unsigned int c)
{
    PixelRGB p;
    p = image->raw_data[r*image->width + c];
    return p;
}

/*!
 * \fn ImageRGB* createCross(int length)
 * The resulting image is a red square with a blue cross inside.
 * \param[in] length the square size
 * \return a pointer on the new image
 */

ImageRGB* createCross(long int length)
{
    int i, j, r;
    /* to be completed*/
    ImageRGB *image = allocateImage(length, length);
    if (image == NULL) {
        fprintf(stderr, "Image allocation failed\n");
    }
    /* set blue background */
    PixelRGB blue = {255,0,0};
    for (i = 0; i < length; i++) {
        for (j = 0; j < length; j++) {
            setPixel(image, i, j, blue);
        }
    }

    /* set color of the red cross */
    PixelRGB red = {0,0,255};
    for (r = 0; r < length; r++) { //parcourir chaque ligne
        setPixel(image,r,r,red);
        setPixel(image,r,length - 1 - r, red);
    }
    return image;
}

/*!
 * \fn void modifyImage(ImageRGB * image, PixelRGB pix_initial, PixelRGB pix_final)
 *  Modify an image by replacing every pixel with a given value by another one
 * \param[in,out] image ImageRGB to be modified
 * \param[in] pix_initial initial value in the image to be replaced
 * \param[in] pix_final the new value for those pixels
 */
void modifyImage(ImageRGB * image, PixelRGB pix_initial, PixelRGB pix_final) {
    /* to be completed*/
    unsigned int r,c;
    for (r = 0; r < getHeight(image); r++) {
        for (c = 0; c < getWidth(image); c++) {
            PixelRGB p = getPixel(image, r, c);
            if (p.blue == pix_initial.blue && p.green == pix_initial.green && p.red == pix_initial.red) { //cannot compare pixel to pixel directly since we are in OPP Programming
                setPixel(image, r, c, pix_final);
            }
        }
    }
}


