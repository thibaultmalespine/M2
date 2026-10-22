// UNILIM - FST - L2 - Bases du Langage C - TP2
// Maxime MARIA
#include <stdint.h> // for uint32_t

// Structure to store an image
typedef struct StructImage {
    int width;
    int height;
    // Colors are stored as uint
    uint32_t *pixels;
} Image;

// Create an image with 'width'x'height' white pixels
// Put the result in 'img' 
void createEmptyImage(Image *img, const int width, const int height);

// Load an image from file at path 'imgPath' and store it in 'img'
int loadImage(const char *imgPath, Image *img);

// Write image 'img' into the file at path 'imgPath'
void writeImagePNG(const Image img, const char *imgPath);

// Free pixels buffer 
void deleteImage(const Image img);

// Print information about the image
void printImageInfo(const Image img);

// Return the color of the pixel ('i','j') in 'img'
uint32_t getPixelColor(const Image img, const int i, const int j);

// Set the color of the pixel ('i','j') in 'img' at 'color' 
void setPixelColor(Image *img, const int i, const int j, const uint32_t color);
