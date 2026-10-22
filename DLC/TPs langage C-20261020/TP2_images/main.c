// UNILIM - FST - L2 - Bases du Langage C - TP2
// Maxime MARIA
#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main(int argc, char *argv[])
{
    // Program needs only one parameter: the path to an image
    if (argc != 2)
    {
        printf("[ERROR] Invalid number of parameters\n");
        printf("=> Usage: %s image_path\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *imgPath = argv[1];

    // Loading
    Image img;
    if (loadImage(imgPath, &img) != 0)
    {
        printf("[ERROR] stbi_load failed to load file: %s\n", imgPath);
        return EXIT_FAILURE;
    }

    // Print width and height
    printImageInfo(img);

    // Image to store the copy
    Image imgCopy;
    createEmptyImage(&imgCopy, img.width, img.height);
    
    // Image to store the tinted image
    Image imgInvert;
    createEmptyImage(&imgInvert, img.width, img.height);

    // Image to store the sepia image
    Image imgSepia;
    createEmptyImage(&imgSepia, img.width, img.height);

    // Get the pixel color of 'imgCopy' at (0,0) and print it in hexadecimal
    uint32_t inColor = getPixelColor(imgCopy, 0, 0);
    printf("Should be white: %X\n", inColor);

    // Set the pixel color 'imgCopy' at (0,0) to red and print it in hexadecimal
    setPixelColor(&imgCopy, 0, 0, 0xFF0000FF);
    printf("Should be red: %X\n", getPixelColor(imgCopy, 0, 0));

    // ============================================================
    // CODE HERE
       
    // ============================================================

    // Write PNGs
    printf("Writing images...\n");
    writeImagePNG(imgCopy, "resultCopy.png");
    writeImagePNG(imgInvert, "resultInvert.png");
    writeImagePNG(imgSepia, "resultSepia.png");

    // Free memory :-)
    deleteImage(img);
    deleteImage(imgInvert);
    deleteImage(imgSepia);

    printf("Good bye!\n");

    return EXIT_SUCCESS;
}
