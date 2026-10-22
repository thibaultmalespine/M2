// UNILIM - FST - L2 - Bases du Langage C - TP2
// Maxime MARIA
#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

void createEmptyImage(Image *img, const int width, const int height)
{
    img->width = width;
    img->height = height;
    const size_t size = img->width * img->height * sizeof(unsigned int);
    img->pixels = (uint32_t *)malloc(size);
    memset(img->pixels, 0xFF, size);
}

int loadImage(const char *imgPath, Image *img)
{
    // Cast to uint32_t for the exercise
    img->pixels = (uint32_t *)stbi_load(imgPath, &(img->width), &(img->height), NULL, 4);
    if (img->pixels == NULL)
    {
        return -1;
    }
    return 0;
}

void writeImagePNG(const Image img, const char *imgPath)
{
    stbi_write_png(imgPath, img.width, img.height, 4, img.pixels, img.width * 4);
}

void deleteImage(const Image img) 
{
    if (img.pixels != NULL)
        free(img.pixels);
}

void printImageInfo(const Image img)
{
    printf("Image:\n");
    printf("- width: %d\n", img.width);
    printf("- height: %d\n", img.height);
}

uint32_t getPixelColor(const Image img, const int i, const int j)
{
    return img.pixels[i + img.width * j];
}

// We assume i and j are valid
void setPixelColor(Image *img, const int i, const int j, const uint32_t color)
{
    img->pixels[i + img->width * j] = color;
}