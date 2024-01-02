#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

#define INPUT_IMAGE "inputImage.jpg"
#define OUTPUT_IMAGE "vfilterImage.jpg"
#define OUTPUT_IMAGEH "hfilterImage.jpg"
#define OUTPUT_IMAGEBW "bwfilterImage.jpg"

void loadImage( int *width , int *height , int*** matrix ){

    // library content
    int channels;
    unsigned char* img = stbi_load( INPUT_IMAGE , width, height, &channels, 1); // Load image in grayscale (1 channel)

    if (img == NULL) {

        printf("Error: Unable to load image from %s\n", INPUT_IMAGE );
        return;

    }

    // Allocate memory for the matrix
    *matrix = (int**)malloc((*height) * sizeof(int*));

    for (int i = 0; i < *height; ++i) {

        (*matrix)[i] = (int*)malloc((*width) * sizeof(int));

    }

    // Convert image to matrix
    for (int i = 0; i < *height; ++i) {

        for (int j = 0; j < *width; ++j) {

            (*matrix)[i][j] = img[i * (*width) + j];

        }

    }

    // Free stb_image memory
    stbi_image_free(img);

    // library content ended

}

// Function to free the allocated memory for the matrix
void freeMatrix(int*** matrix, int height) {

    for (int i = 0; i < height; ++i) {

        free((*matrix)[i]);

    }

    free(*matrix);
    *matrix = NULL;

}

// Function to print a matrix
void printMatrix(int** matrix, int width, int height) {

    for (int i = 0; i < height; ++i) {

        for (int j = 0; j < width; ++j) {

            printf("%d\t", matrix[i][j]);

        }

        printf("\n");

    }

}

void performConvolution(int filter[][3], int fRow, int fCol, const int** matrix, int** outputMatrix, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int m = -1; m <= 1; ++m) {
                for (int n = -1; n <= 1; ++n) {
                    if (i + m >= 0 && i + m < height && j + n >= 0 && j + n < width) {
                        outputMatrix[i][j] += matrix[i + m][j + n] * filter[1 + m][1 + n];
                    }
                }
            }
        }
    }
}


// Function to convert matrix to image and save it
void saveImage( char outputImage[] , const int** matrix , int width, int height) {

    // Allocate memory for the image data
    unsigned char* image = (unsigned char*)malloc(width * height);

    // Convert matrix to image data
    for (int i = 0; i < height; ++i) {

        for (int j = 0; j < width; ++j) {

            image[i * width + j] = (unsigned char)matrix[i][j];

        }

    }

    // Save image using STB Image Write
    stbi_write_jpg( outputImage , width, height, 1, image, 100); // Assuming grayscale image

    // Free allocated memory
    free(image);

}

int main(){

    int width , height ;
    int** matrix;
    int** outputMatrix;

    //load image and get its dimension
    loadImage(&width , &height , &matrix );

    // Allocate memory for outputMatrix
    outputMatrix = (int**)malloc(height * sizeof(int*));

    for (int i = 0; i < height; ++i) {

        outputMatrix[i] = (int*)malloc(width * sizeof(int));
        
    }

    // introduction and choices option 
    printf("\n");
    printf("Welcome to CNN Tutorial !!\n\n");
    printf("Select choices : \n");
    printf("                    1 --> Vertical Edge Detection \n");
    printf("                    2 --> Horizontal Edge Decdection \n");
    printf("                    3 --> Black and White Image Filtering\n");
    printf("                    4 --> Print the Loaded Image Matrix \n");
    printf("                    5 --> Print the Output Image Matrix \n");
    printf("                    6 --> Exit the Program \n");
    printf("\n");

    // reading the choice
    int choice;
    Choice : 
        {
            printf("Enter your choice : ");
            scanf("%d", &choice);
            printf("\n");
    
        }

    // declaring a horizontal matrix of size 3 x 3 for applying filter 
    
    int hFilter[3][3] = {

        { 1 , 1 , 1 } ,
        { 0 , 0 , 0 } ,
        { -1 , -1 , -1 }

    } ;

    // vertical matrix for applying filter 

    int bwFilter[3][3] = { 

        { 1 , 0 , 0 } ,
        { 0 , 1 , 0 } ,
        { 0 , 0 , 1 } 


    } ;

    int vFilter[3][3] = { 

        { 1 , 0 , -1 } ,
        { 1 , 0 , -1 } ,
        { 1 , 0 , -1 } 

    } ;

    // performing the task as per the choice given
    switch ( choice ){

        case 1 : 
                printf("Performing the Vertical Edge Dedection........\n");
                performConvolution( vFilter , 3 , 3 , (const int**)matrix , outputMatrix , height , width );
                // Save the output matrix as an image
                saveImage( OUTPUT_IMAGE , (const int**)outputMatrix , width, height );
                goto Choice ;
                break;
        
        case 2 : 
                printf("Performing the Horizontal Edge Dedection........\n");
                performConvolution( hFilter , 3 , 3 , (const int**)matrix , outputMatrix , height , width );
                // Save the output matrix as an image
                saveImage( OUTPUT_IMAGEH , (const int**)outputMatrix , width, height );
                goto Choice ;
                break;

        case 3 : 
                printf("Performing the Black and White Image Filtering........\n");
                performConvolution( bwFilter , 3 , 3 , (const int**)matrix , outputMatrix , height , width );
                // Save the output matrix as an image
                saveImage( OUTPUT_IMAGEBW , (const int**)outputMatrix , width, height );
                goto Choice ;
                break;

        case 4 :
                printf("Printing the Input or Loaded Image Mtarix........\n");
                printMatrix(matrix, width, height);
                goto Choice ;
                break;

        case 5 :
                printf("Printing the Output Image Matrix..........\n");
                printMatrix(outputMatrix, width, height);
                goto Choice;
                break;


        case 6 : 
                printf("Exiting the Program..........\n\n");
                break;

        default : 
                printf("Invalid Input !!\n\n");
                goto Choice ;

    }


    // Free the allocated memory for the matrix
    freeMatrix(&matrix, height);
    freeMatrix(&outputMatrix, height);

    return 0;

}
