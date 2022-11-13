#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float grayscale_pixel = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = (int) round(grayscale_pixel); // Storing new grayscale value of blue channel
            image[i][j].rgbtGreen = (int) round(grayscale_pixel); // Storing new grayscale value of green channel
            image[i][j].rgbtRed = (int) round(grayscale_pixel); // Storing new grayscale value of red channel
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp[1][1]; // Temp array for swapping
            // Swapping the blue color in pixel
            temp[0][0].rgbtBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp[0][0].rgbtBlue;

            // Swapping the green color in pixel
            temp[0][0].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp[0][0].rgbtGreen;
            // Swapping the red color in pixel
            temp[0][0].rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp[0][0].rgbtRed;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a copy of all the pixels to a new 2d array copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    // Iterating through all the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Blurring top left corner
            if (i - 1 < 0 && j - 1 < 0)
            {
                image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i +
                                                    1][j].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i +
                                                     1][j].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i +
                                                   1][j].rgbtRed) / 4.0);
            }
            // Blurring bottom right corner
            else if (i + 1 == height && j + 1 == width)
            {
                image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i -
                                                    1][j].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i -
                                                     1][j].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i -
                                                   1][j].rgbtRed) / 4.0);
            }
            // Blurring top right corner
            else if (i - 1 < 0 && j + 1 == width)
            {
                image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j -
                                                    1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j -
                                                     1].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j -
                                                   1].rgbtRed) / 4.0);
            }
            // Blurring bottom left corner
            else if (i + 1 == height && j - 1 < 0)
            {
                image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j +
                                                    1].rgbtBlue) / 4.0);
                image[i][j].rgbtGreen = (int)round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j +
                                                    1].rgbtGreen) / 4.0);
                image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j +
                                                   1].rgbtRed) / 4.0);
            }

            // Blurring top edge pixels
            else if (i - 1 < 0)
            {
                image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j +
                                                    1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j
                                                     +

                                                     1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j +
                                                   1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed) / 6.0);
            }
            // Blurring left edge pixels
            else if (j - 1 < 0)
            {
                image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j +
                                                    1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j +
                                                     1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j +
                                                   1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 6.0);
            }
            // Blurring right edge pixels
            else if (j + 1 == width)
            {
                image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j -
                                                    1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j -
                                                     1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j -
                                                   1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 6.0);
            }
            // Blurring bottom edge pixels
            else if (i + 1 == height)
            {
                image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j +
                                                    1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue) / 6.0);
                image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j +
                                                     1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen) / 6.0);
                image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j +
                                                   1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed) / 6.0);
            }
            // Blurring middle pixels
            else
            {
                image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j +
                                                    1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i +
                                                            1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 9.0);
                image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j +
                                                     1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                                                     copy[i + 1][j - 1].rgbtGreen) / 9.0);
                image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j +
                                                   1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i +
                                                           1][j - 1].rgbtRed) / 9.0);
            }

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a copy of all the pixels in image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue; // Blue channel of all pixels
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen; // Green channel of all pixels
            copy[i][j].rgbtRed = image[i][j].rgbtRed;    // Red channel of all pixels
        }
    }
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}; // Defining gx convolution matrix for horizontal edges
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}; // Defining gy convolution matrix for vertical edges
    int tempx = 0, tempy = 0; // Two temp variables for storing the value obtained bw product of pixel channel and gx / gy
    float temp; // Temp float to store the decimal value of new value after doing sobel algorithm
    // Itererating through all the pixels of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner
            if (i - 1 < 0 && j - 1 < 0)
            {
                tempx = copy[i][j].rgbtBlue * gx[1][1] + copy[i][j + 1].rgbtBlue * gx[1][2] + copy[i + 1][j].rgbtBlue * gx[2][1] + copy[i + 1][j +
                        1].rgbtBlue * gx[2][2];
                tempy = copy[i][j].rgbtBlue * gy[1][1] + copy[i][j + 1].rgbtBlue * gy[1][2] + copy[i + 1][j].rgbtBlue * gy[2][1] + copy[i + 1][j +
                        1].rgbtBlue * gy[2][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtBlue = (int) round(temp);

                tempx = copy[i][j].rgbtGreen * gx[1][1] + copy[i][j + 1].rgbtGreen * gx[1][2] + copy[i + 1][j].rgbtGreen * gx[2][1] + copy[i + 1][j
                        + 1].rgbtGreen * gx[2][2];
                tempy = copy[i][j].rgbtGreen * gy[1][1] + copy[i][j + 1].rgbtGreen * gy[1][2] + copy[i + 1][j].rgbtGreen * gy[2][1] + copy[i + 1][j
                        + 1].rgbtGreen * gy[2][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtGreen = (int) round(temp);

                tempx = copy[i][j].rgbtRed * gx[1][1] + copy[i][j + 1].rgbtRed * gx[1][2] + copy[i + 1][j].rgbtRed * gx[2][1] + copy[i + 1][j +
                        1].rgbtRed * gx[2][2];
                tempy = copy[i][j].rgbtRed * gy[1][1] + copy[i][j + 1].rgbtRed * gy[1][2] + copy[i + 1][j].rgbtRed * gy[2][1] + copy[i + 1][j +
                        1].rgbtRed * gy[2][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtRed = (int) round(temp);
            }

            // Bottom right corner
            else if (i + 1 == height && j + 1 == width)
            {
                tempx = copy[i][j].rgbtBlue * gx[1][1] + copy[i][j - 1].rgbtBlue * gx[1][0] + copy[i - 1][j - 1].rgbtBlue * gx[0][0] + copy[i -
                        1][j].rgbtBlue * gx[0][1];
                tempy = copy[i][j].rgbtBlue * gy[1][1] + copy[i][j - 1].rgbtBlue * gy[1][0] + copy[i - 1][j - 1].rgbtBlue * gy[0][0] + copy[i -
                        1][j].rgbtBlue * gy[0][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtBlue = (int) round(temp);

                tempx = copy[i][j].rgbtGreen * gx[1][1] + copy[i][j - 1].rgbtGreen * gx[1][0] + copy[i - 1][j - 1].rgbtGreen * gx[0][0] + copy[i -
                        1][j].rgbtGreen * gx[0][1];
                tempy = copy[i][j].rgbtGreen * gy[1][1] + copy[i][j - 1].rgbtGreen * gy[1][0] + copy[i - 1][j - 1].rgbtGreen * gy[0][0] + copy[i -
                        1][j].rgbtGreen * gy[0][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtGreen = (int) round(temp);

                tempx = copy[i][j].rgbtRed * gx[1][1] + copy[i][j - 1].rgbtRed * gx[1][0] + copy[i - 1][j - 1].rgbtRed * gx[0][0] + copy[i -
                        1][j].rgbtRed * gx[0][1];
                tempy = copy[i][j].rgbtRed * gy[1][1] + copy[i][j - 1].rgbtRed * gy[1][0] + copy[i - 1][j - 1].rgbtRed * gy[0][0] + copy[i -
                        1][j].rgbtRed * gy[0][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtRed = (int) round(temp);


            }

            // Top right corner
            else if (i - 1 < 0 && j + 1 == width)
            {
                tempx = copy[i][j].rgbtBlue * gx[1][1] + copy[i][j - 1].rgbtBlue * gx[1][0] + copy[i + 1][j - 1].rgbtBlue * gx[2][0] + copy[i +
                        1][j].rgbtBlue * gx[2][1];
                tempy = copy[i][j].rgbtBlue * gy[1][1] + copy[i][j - 1].rgbtBlue * gy[1][0] + copy[i + 1][j - 1].rgbtBlue * gy[2][0] + copy[i +
                        1][j].rgbtBlue * gy[2][1];
                image[i][j].rgbtBlue = (int) round(sqrt(pow(tempx, 2) + pow(tempy, 2)));
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtBlue = (int) round(temp);

                tempx = copy[i][j].rgbtGreen * gx[1][1] + copy[i][j - 1].rgbtGreen * gx[1][0] + copy[i + 1][j - 1].rgbtGreen * gx[2][0] + copy[i +
                        1][j].rgbtGreen * gx[2][1];
                tempy = copy[i][j].rgbtGreen * gy[1][1] + copy[i][j - 1].rgbtGreen * gy[1][0] + copy[i + 1][j - 1].rgbtGreen * gy[2][0] + copy[i +
                        1][j].rgbtGreen * gy[2][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtGreen = (int) round(temp);

                tempx = copy[i][j].rgbtRed * gx[1][1] + copy[i][j - 1].rgbtRed * gx[1][0] + copy[i + 1][j - 1].rgbtRed * gx[2][0] + copy[i +
                        1][j].rgbtRed * gx[2][1];
                tempy = copy[i][j].rgbtRed * gy[1][1] + copy[i][j - 1].rgbtRed * gy[1][0] + copy[i + 1][j - 1].rgbtRed * gy[2][0] + copy[i +
                        1][j].rgbtRed * gy[2][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtRed = (int) round(temp);

            }
            // Bottom left corner
            else if (i + 1 == height && j - 1 < 0)
            {
                tempx = copy[i][j].rgbtBlue * gx[1][1] + copy[i - 1][j].rgbtBlue * gx[0][1] + copy[i - 1][j + 1].rgbtBlue * gx[0][2] + copy[i][j +
                        1].rgbtBlue * gx[1][2];
                tempy = copy[i][j].rgbtBlue * gy[1][1] + copy[i - 1][j].rgbtBlue * gy[0][1] + copy[i - 1][j + 1].rgbtBlue * gy[0][2] + copy[i][j +
                        1].rgbtBlue * gy[1][2];
                image[i][j].rgbtBlue = (int) round(sqrt(pow(tempx, 2) + pow(tempy, 2)));
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtBlue = (int) round(temp);

                tempx = copy[i][j].rgbtGreen * gx[1][1] + copy[i - 1][j].rgbtGreen * gx[0][1] + copy[i - 1][j + 1].rgbtGreen * gx[0][2] + copy[i][j
                        + 1].rgbtGreen * gx[1][2];
                tempy = copy[i][j].rgbtGreen * gy[1][1] + copy[i - 1][j].rgbtGreen * gy[0][1] + copy[i - 1][j + 1].rgbtGreen * gy[0][2] + copy[i][j
                        + 1].rgbtGreen * gy[1][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtGreen = (int) round(temp);

                tempx = copy[i][j].rgbtRed * gx[1][1] + copy[i - 1][j].rgbtRed * gx[0][1] + copy[i - 1][j + 1].rgbtRed * gx[0][2] + copy[i][j +
                        1].rgbtRed * gx[1][2];
                tempy = copy[i][j].rgbtRed * gy[1][1] + copy[i - 1][j].rgbtRed * gy[0][1] + copy[i - 1][j + 1].rgbtRed * gy[0][2] + copy[i][j +
                        1].rgbtRed * gy[1][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtRed = (int) round(temp);
            }
            // Top edge pixels
            else if (i - 1 < 0)
            {
                tempx = copy[i][j].rgbtBlue * gx[1][1] + copy[i][j + 1].rgbtBlue * gx[1][2] + copy[i + 1][j + 1].rgbtBlue * gx[2][2] + copy[i +
                        1][j].rgbtBlue * gx[2][1] + copy[i + 1][j - 1].rgbtBlue * gx[2][0] + copy[i][j - 1].rgbtBlue * gx[1][0];
                tempy = copy[i][j].rgbtBlue * gy[1][1] + copy[i][j + 1].rgbtBlue * gy[1][2] + copy[i + 1][j + 1].rgbtBlue * gy[2][2] + copy[i +
                        1][j].rgbtBlue * gy[2][1] + copy[i + 1][j - 1].rgbtBlue * gy[2][0] + copy[i][j - 1].rgbtBlue * gy[1][0];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtBlue = (int) round(temp);


                tempx = copy[i][j].rgbtGreen * gx[1][1] + copy[i][j + 1].rgbtGreen * gx[1][2] + copy[i + 1][j + 1].rgbtGreen * gx[2][2] + copy[i +
                        1][j].rgbtGreen * gx[2][1] + copy[i + 1][j - 1].rgbtGreen * gx[2][0] + copy[i][j - 1].rgbtGreen * gx[1][0];
                tempy = copy[i][j].rgbtGreen * gy[1][1] + copy[i][j + 1].rgbtGreen * gy[1][2] + copy[i + 1][j + 1].rgbtGreen * gy[2][2] + copy[i +
                        1][j].rgbtGreen * gy[2][1] + copy[i + 1][j - 1].rgbtGreen * gy[2][0] + copy[i][j - 1].rgbtGreen * gy[1][0];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtGreen = (int) round(temp);


                tempx = copy[i][j].rgbtRed * gx[1][1] + copy[i][j + 1].rgbtRed * gx[1][2] + copy[i + 1][j + 1].rgbtRed * gx[2][2] + copy[i +
                        1][j].rgbtRed * gx[2][1] + copy[i + 1][j - 1].rgbtRed * gx[2][0] + copy[i][j - 1].rgbtRed * gx[1][0];
                tempy = copy[i][j].rgbtRed * gy[1][1] + copy[i][j + 1].rgbtRed * gy[1][2] + copy[i + 1][j + 1].rgbtRed * gy[2][2] + copy[i +
                        1][j].rgbtRed * gy[2][1] + copy[i + 1][j - 1].rgbtRed * gy[2][0] + copy[i][j - 1].rgbtRed * gy[1][0];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtRed = (int) round(temp);

            }
            // Left edge pixels
            else if (j - 1 < 0)
            {
                tempx = copy[i][j].rgbtBlue * gx[1][1] + copy[i - 1][j].rgbtBlue * gx[0][1] + copy[i - 1][j + 1].rgbtBlue * gx[0][2] + copy[i][j +
                        1].rgbtBlue * gx[1][2] + copy[i + 1][j + 1].rgbtBlue * gx[2][2] + copy[i + 1][j].rgbtBlue * gx[2][1];
                tempy = copy[i][j].rgbtBlue * gy[1][1] + copy[i - 1][j].rgbtBlue * gy[0][1] + copy[i - 1][j + 1].rgbtBlue * gy[0][2] + copy[i][j +
                        1].rgbtBlue * gy[1][2] + copy[i + 1][j + 1].rgbtBlue * gy[2][2] + copy[i + 1][j].rgbtBlue * gy[2][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtBlue = (int) round(temp);


                tempx = copy[i][j].rgbtGreen * gx[1][1] + copy[i - 1][j].rgbtGreen * gx[0][1] + copy[i - 1][j + 1].rgbtGreen * gx[0][2] + copy[i][j
                        + 1].rgbtGreen * gx[1][2] + copy[i + 1][j + 1].rgbtGreen * gx[2][2] + copy[i + 1][j].rgbtGreen * gx[2][1];
                tempy = copy[i][j].rgbtGreen * gy[1][1] + copy[i - 1][j].rgbtGreen * gy[0][1] + copy[i - 1][j + 1].rgbtGreen * gy[0][2] + copy[i][j
                        + 1].rgbtGreen * gy[1][2] + copy[i + 1][j + 1].rgbtGreen * gy[2][2] + copy[i + 1][j].rgbtGreen * gy[2][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtGreen = (int) round(temp);


                tempx = copy[i][j].rgbtRed * gx[1][1] + copy[i - 1][j].rgbtRed * gx[0][1] + copy[i - 1][j + 1].rgbtRed * gx[0][2] + copy[i][j +
                        1].rgbtRed * gx[1][2] + copy[i + 1][j + 1].rgbtRed * gx[2][2] + copy[i + 1][j].rgbtRed * gx[2][1];
                tempy = copy[i][j].rgbtRed * gy[1][1] + copy[i - 1][j].rgbtRed * gy[0][1] + copy[i - 1][j + 1].rgbtRed * gy[0][2] + copy[i][j +
                        1].rgbtRed * gy[1][2] + copy[i + 1][j + 1].rgbtRed * gy[2][2] + copy[i + 1][j].rgbtRed * gy[2][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtRed = (int) round(temp);

            }

            // Right edge pixels
            else if (j + 1 == width)
            {
                tempx = copy[i][j].rgbtBlue * gx[1][1] + copy[i + 1][j].rgbtBlue * gx[2][1] + copy[i + 1][j - 1].rgbtBlue * gx[2][0] + copy[i][j -
                        1].rgbtBlue * gx[1][0] + copy[i - 1][j - 1].rgbtBlue * gx[0][0] + copy[i - 1][j].rgbtBlue * gx[0][1];
                tempy = copy[i][j].rgbtBlue * gy[1][1] + copy[i + 1][j].rgbtBlue * gy[2][1] + copy[i + 1][j - 1].rgbtBlue * gy[2][0] + copy[i][j -
                        1].rgbtBlue * gy[1][0] + copy[i - 1][j - 1].rgbtBlue * gy[0][0] + copy[i - 1][j].rgbtBlue * gy[0][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtBlue = (int) round(temp);

                tempx = copy[i][j].rgbtGreen * gx[1][1] + copy[i + 1][j].rgbtGreen * gx[2][1] + copy[i + 1][j - 1].rgbtGreen * gx[2][0] + copy[i][j
                        - 1].rgbtGreen * gx[1][0] + copy[i - 1][j - 1].rgbtGreen * gx[0][0] + copy[i - 1][j].rgbtGreen * gx[0][1];
                tempy = copy[i][j].rgbtGreen * gy[1][1] + copy[i + 1][j].rgbtGreen * gy[2][1] + copy[i + 1][j - 1].rgbtGreen * gy[2][0] + copy[i][j
                        - 1].rgbtGreen * gy[1][0] + copy[i - 1][j - 1].rgbtGreen * gy[0][0] + copy[i - 1][j].rgbtGreen * gy[0][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtGreen = (int) round(temp);


                tempx = copy[i][j].rgbtRed * gx[1][1] + copy[i + 1][j].rgbtRed * gx[2][1] + copy[i + 1][j - 1].rgbtRed * gx[2][0] + copy[i][j -
                        1].rgbtRed * gx[1][0] + copy[i - 1][j - 1].rgbtRed * gx[0][0] + copy[i - 1][j].rgbtRed * gx[0][1];
                tempy = copy[i][j].rgbtRed * gy[1][1] + copy[i + 1][j].rgbtRed * gy[2][1] + copy[i + 1][j - 1].rgbtRed * gy[2][0] + copy[i][j -
                        1].rgbtRed * gy[1][0] + copy[i - 1][j - 1].rgbtRed * gy[0][0] + copy[i - 1][j].rgbtRed * gy[0][1];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtRed = (int) round(temp);

            }
            // Bottom edge pixels
            else if (i + 1 == height)
            {
                tempx = copy[i][j].rgbtBlue * gx[1][1] + copy[i][j - 1].rgbtBlue * gx[1][0] + copy[i - 1][j - 1].rgbtBlue * gx[0][0] + copy[i -
                        1][j].rgbtBlue * gx[0][1] + copy[i - 1][j + 1].rgbtBlue * gx[0][2] + copy[i][j + 1].rgbtBlue * gx[1][2];
                tempy = copy[i][j].rgbtBlue * gy[1][1] + copy[i][j - 1].rgbtBlue * gy[1][0] + copy[i - 1][j - 1].rgbtBlue * gy[0][0] + copy[i -
                        1][j].rgbtBlue * gy[0][1] + copy[i - 1][j + 1].rgbtBlue * gy[0][2] + copy[i][j + 1].rgbtBlue * gy[1][2];

                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtBlue = (int) round(temp);


                tempx = copy[i][j].rgbtGreen * gx[1][1] + copy[i][j - 1].rgbtGreen * gx[1][0] + copy[i - 1][j - 1].rgbtGreen * gx[0][0] + copy[i -
                        1][j].rgbtGreen * gx[0][1] + copy[i - 1][j + 1].rgbtGreen * gx[0][2] + copy[i][j + 1].rgbtGreen * gx[1][2];
                tempy = copy[i][j].rgbtGreen * gy[1][1] + copy[i][j - 1].rgbtGreen * gy[1][0] + copy[i - 1][j - 1].rgbtGreen * gy[0][0] + copy[i -
                        1][j].rgbtGreen * gy[0][1] + copy[i - 1][j + 1].rgbtGreen * gy[0][2] + copy[i][j + 1].rgbtGreen * gy[1][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtGreen = (int) round(temp);


                tempx = copy[i][j].rgbtRed * gx[1][1] + copy[i][j - 1].rgbtRed * gx[1][0] + copy[i - 1][j - 1].rgbtRed * gx[0][0] + copy[i -
                        1][j].rgbtRed * gx[0][1] + copy[i - 1][j + 1].rgbtRed * gx[0][2] + copy[i][j + 1].rgbtRed * gx[1][2];
                tempy = copy[i][j].rgbtRed * gy[1][1] + copy[i][j - 1].rgbtRed * gy[1][0] + copy[i - 1][j - 1].rgbtRed * gy[0][0] + copy[i -
                        1][j].rgbtRed * gy[0][1] + copy[i - 1][j + 1].rgbtRed * gy[0][2] + copy[i][j + 1].rgbtRed * gy[1][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtRed = (int) round(temp);


            }
            // All middle pixels which form 3 * 3 grid
            else
            {
                tempx = copy[i][j].rgbtBlue * gx[1][1]  + copy[i + 1][j].rgbtBlue * gx[2][1] + copy[i + 1][j - 1].rgbtBlue * gx[2][0] + copy[i][j -
                        1].rgbtBlue * gx[1][0] + copy[i - 1][j - 1].rgbtBlue * gx[0][0] + copy[i - 1][j].rgbtBlue * gx[0][1] + copy[i - 1][j + 1].rgbtBlue *
                        gx[0][2] + copy[i][j + 1].rgbtBlue * gx[1][2] + copy[i + 1][j + 1].rgbtBlue * gx[2][2];
                tempy = copy[i][j].rgbtBlue * gy[1][1]  + copy[i + 1][j].rgbtBlue * gy[2][1] + copy[i + 1][j - 1].rgbtBlue * gy[2][0] + copy[i][j -
                        1].rgbtBlue * gy[1][0] + copy[i - 1][j - 1].rgbtBlue * gy[0][0] + copy[i - 1][j].rgbtBlue * gy[0][1] + copy[i - 1][j + 1].rgbtBlue *
                        gy[0][2] + copy[i][j + 1].rgbtBlue * gy[1][2] + copy[i + 1][j + 1].rgbtBlue * gy[2][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtBlue = (int) round(temp);


                tempx = copy[i][j].rgbtGreen * gx[1][1]  + copy[i + 1][j].rgbtGreen * gx[2][1] + copy[i + 1][j - 1].rgbtGreen * gx[2][0] + copy[i][j
                        - 1].rgbtGreen * gx[1][0] + copy[i - 1][j - 1].rgbtGreen * gx[0][0] + copy[i - 1][j].rgbtGreen * gx[0][1] + copy[i - 1][j +
                                1].rgbtGreen * gx[0][2] + copy[i][j + 1].rgbtGreen * gx[1][2] + copy[i + 1][j + 1].rgbtGreen * gx[2][2];
                tempy = copy[i][j].rgbtGreen * gy[1][1]  + copy[i + 1][j].rgbtGreen * gy[2][1] + copy[i + 1][j - 1].rgbtGreen * gy[2][0] + copy[i][j
                        - 1].rgbtGreen * gy[1][0] + copy[i - 1][j - 1].rgbtGreen * gy[0][0] + copy[i - 1][j].rgbtGreen * gy[0][1] + copy[i - 1][j +
                                1].rgbtGreen * gy[0][2] + copy[i][j + 1].rgbtGreen * gy[1][2] + copy[i + 1][j + 1].rgbtGreen * gy[2][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtGreen = (int) round(temp);


                tempx = copy[i][j].rgbtRed * gx[1][1]  + copy[i + 1][j].rgbtRed * gx[2][1] + copy[i + 1][j - 1].rgbtRed * gx[2][0] + copy[i][j -
                        1].rgbtRed * gx[1][0] + copy[i - 1][j - 1].rgbtRed * gx[0][0] + copy[i - 1][j].rgbtRed * gx[0][1] + copy[i - 1][j + 1].rgbtRed *
                        gx[0][2] + copy[i][j + 1].rgbtRed * gx[1][2] + copy[i + 1][j + 1].rgbtRed * gx[2][2];
                tempy = copy[i][j].rgbtRed * gy[1][1]  + copy[i + 1][j].rgbtRed * gy[2][1] + copy[i + 1][j - 1].rgbtRed * gy[2][0] + copy[i][j -
                        1].rgbtRed * gy[1][0] + copy[i - 1][j - 1].rgbtRed * gy[0][0] + copy[i - 1][j].rgbtRed * gy[0][1] + copy[i - 1][j + 1].rgbtRed *
                        gy[0][2] + copy[i][j + 1].rgbtRed * gy[1][2] + copy[i + 1][j + 1].rgbtRed * gy[2][2];
                temp =  sqrt(pow(tempx, 2) + pow(tempy, 2));
                if (temp > 255) // Encapsulating the value to 255 in case sobel algorithm gives a value greater than 255
                {
                    temp = 255;
                }
                image[i][j].rgbtRed = (int) round(temp);




            }



        }
    }


    return;
}
