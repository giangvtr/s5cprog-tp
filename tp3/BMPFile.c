/*!
 * \file BMPFile.c
 * \brief definition of functions to handle a BMP file using RGB colour space
 * \author ...
 * \date ...
 */


#include "BMPFile.h"
#include <stdio.h>
#include <string.h>

void writeBMPFile(char * filename, ImageRGB* image, int verbose) {
    FILE *file = NULL;
    FileHeader header;
    DIBHeader dibheader;

    /* padding management */
    int size_row = getWidth(image) * 3;
    int padding = (4-size_row) %4;
    int size_padded_row = size_row + padding;
    int size_image = getHeight(image) * size_padded_row;

    //
    file = fopen(filename, "wb");
    if(file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    header.identity[0] = 'B';
    header.identity[1] = 'M';
    header.file_size = 54 + size_image;
    header.raster_address = 54;

    dibheader.size_DIBHeader = 40;
    dibheader.image_width = getWidth(image);
    dibheader.image_height = getHeight(image); //nb de rows
    dibheader.nbColorPlanes = 1;
    dibheader.nbBitPerPixel = 24;
    dibheader.typeCompression = 0;
    dibheader.size_raw_image = size_image;
    dibheader.hResolution = 2800;
    dibheader.vResolution = 2800;
    dibheader.nbUsedColours = 0;
    dibheader.nbImportantColours = 0;

    if(verbose) {
        displayFileHeader(&header);
        displayDIBHeader(&dibheader);
    }

    if (fwrite(&header, 1, 14, file) != 14) {
        printf("Error writing header to file %s\n", filename);
        fclose(file);
        return;
    }

    if (fwrite(&dibheader, 1, 40, file) != 40) {
        printf("Error writing DIBheader to file %s\n", filename);
        fclose(file);
        return;
    }

    if (fwrite(image->raw_data, 1, size_image, file) != (long unsigned int)size_image) {
      printf("Error writing raw image to file %s\n", filename);
        fclose(file);
        return;
    }

    printf("Done writing image to %s\n", filename);
    fclose(file);
}

void readFileHeader(FILE*fp, FileHeader* eFichier){
  fseek(fp,0,SEEK_SET);
  if(fread(eFichier, 1, 14, fp) != 14){
    printf("Error reading file header of file\n");
    return;
  }
  printf("Done reading file header of file\n");
}

void readDIBHeader(FILE*fp, DIBHeader* eImage){
  if(fseek(fp, 14, SEEK_SET) != 0){
    printf("Error seeking file header of file\n");
    return;
  }

  if(fread(eImage, 1, 40, fp) != 40) {
    printf("Error reading DIBheader of file\n");
    return;
  }
  printf("Done reading DIBheader of file\n");
}

ImageRGB* readRawImage(FILE*fp, unsigned int adress, int l, int h){
    int i;

    // Seek to the start of image data
    if(fseek(fp, adress, SEEK_SET) != 0) {
      printf("Error seeking where raw image starts in file\n");
      return NULL;
    }

    // Calculate row size with padding
    int size_row = l * 3;
    int padding = (4-size_row) % 4;
    int size_padded_row = size_row + padding;

    printf("Calculated sizes: row=%d, padding=%d, padded_row=%d\n",
           size_row, padding, size_padded_row);

    //allocate new image
    ImageRGB *image = allocateImage(h, size_padded_row);

    // Temporary row buffer to handle padding
    unsigned char* row_buffer = malloc(size_padded_row);
    if(row_buffer == NULL) {
      printf("Error allocating memory for image\n");
      free(image);
      return NULL;
    }

    // Read image data bottom-up (BMP format)
    for(i = h-1; i >= 0; i--){
      if(fread(row_buffer, 1, size_padded_row, fp) != (unsigned long) size_padded_row) {
        printf("Error reading raw image of file\n");
        free(image->raw_data);
        free(image);
        free(row_buffer);
        return NULL;
      }
      memcpy(image->raw_data + (h-i-1)*size_padded_row, row_buffer, size_padded_row);
    }
    //Clean up
    free(row_buffer);
    return image;
}

ImageRGB* readBMPFile(char* filename, int verbose)
{
  FILE *fp = fopen(filename, "rb");
  if(fp == NULL) {
    printf("Error opening file %s\n", filename);
    return NULL;
  }
  FileHeader header;
  DIBHeader dibheader;
  ImageRGB* image;

  readFileHeader(fp, &header);
  readDIBHeader(fp, &dibheader);
  image = readRawImage(fp, header.raster_address, dibheader.image_width, dibheader.image_height);
  if(verbose) {
    displayFileHeader(&header);
    displayDIBHeader(&dibheader);
  }
  return image;
}
