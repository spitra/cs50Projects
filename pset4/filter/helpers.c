#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void swap(RGBTRIPLE *a, RGBTRIPLE *b);
RGBTRIPLE sobel(RGBTRIPLE array[3][3]);
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;

    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width / 2); j++)
        {
            swap(&image[i][width - j - 1], &image[i][j]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //int startR = -1;
            //int startC = -1;
            //int endR = 1;
            //int endC = 1;
            int counter = 0;
            int avgRed = 0;
            int avgBlue = 0;
            int avgGreen = 0;
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    if (i + r < 0 || i + r > (height - 1) || j + c < 0 || j + c > (width - 1))
                    {

                    }
                    else
                    {
                        //blurredPx.rgbtRed
                        avgRed += image[i + r][j + c].rgbtRed;
                        //blurredPx.rgbtBlue
                        avgBlue += image[i + r][j + c].rgbtBlue;
                        //blurredPx.rgbtGreen
                        avgGreen += image[i + r][j + c].rgbtGreen;
                        counter++;
                    }
                }
            }
            //RGBTRIPLE blurredPx;
            //blurredPx.rgbtRed = 0;
            //blurredPx.rgbtGreen = 0;
            // blurredPx.rgbtBlue = 0;
            /*
            if (i == 0 )
            {
                startR = 0;
            }
            if ( i == (height - 1))
            {
                endR = 0;
            }
            if (j == 0)
            {
                startC = 0;
            }
            if (j == (width - 1))
            {
                endC = 0;
            }

            for (; startR <= endR; startR++)
            {
                for(; startC <= endC; startC++)
                {
                    //blurredPx.rgbtRed
                    avgRed += image[i+startR][j+startC].rgbtRed;
                    //blurredPx.rgbtBlue
                    avgBlue += image[i+startR][j+startC].rgbtBlue;
                    //blurredPx.rgbtGreen
                    avgGreen += image[i+startR][j+startC].rgbtGreen;
                    counter++;
                }
            } */
            //blurredPx.rgbtRed
            avgRed = round(avgRed / (float) counter);
            //blurredPx.rgbtBlue
            avgBlue = round(avgBlue / (float) counter);
            //blurredPx.rgbtGreen
            avgGreen = round(avgGreen / (float) counter);
            copy[i][j].rgbtRed = avgRed;
            copy[i][j].rgbtGreen = avgGreen;
            copy[i][j].rgbtBlue = avgBlue;
        }
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j] = copy[i][j];
        }
    }



    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE subMatrix[3][3];
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {


            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    if ((i + r < 0) || (i + r > (height - 1)) || (j + c < 0) || (j + c > (width - 1)))
                    {
                        subMatrix[r + 1][c + 1].rgbtRed = 0;
                        subMatrix[r + 1][c + 1].rgbtGreen = 0;
                        subMatrix[r + 1][c + 1].rgbtBlue = 0;
                    }
                    else
                    {
                        subMatrix[r + 1][c + 1] = image[i + r][j + c];

                    }
                }
            }
            //RGBTRIPLE output = sobel(subMatrix);
            copy[i][j] = sobel(subMatrix);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

void swap(RGBTRIPLE *a, RGBTRIPLE  *b)
{
    RGBTRIPLE temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
}

RGBTRIPLE sobel(RGBTRIPLE array[3][3])
{
    RGBTRIPLE output;
    int gxK[3][3] = 
    {
        { -1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gyK[3][3] = 
    {
        { -1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    int gxR = 0;
    int gyR = 0;
    int gxG = 0;
    int gyG = 0;
    int gxB = 0;
    int gyB = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gxR  += array[i][j].rgbtRed * gxK[i][j];
            gxG  += array[i][j].rgbtGreen * gxK[i][j];
            gxB  += array[i][j].rgbtBlue * gxK[i][j];
            gyR  += array[i][j].rgbtRed * gyK[i][j];
            gyG  += array[i][j].rgbtGreen * gyK[i][j];
            gyB  += array[i][j].rgbtBlue * gyK[i][j];
        }
    }
    
    int red = round(sqrt(pow(gxR, 2) + pow(gyR, 2)));
    //printf("%i\n", red);
    int green = round(sqrt(pow(gxG, 2) + pow(gyG, 2)));
    //printf("%i\n", red);
    int blue = round(sqrt(pow(gxB, 2) + pow(gyB, 2)));
    //printf("%i\n", red);
    
    output.rgbtRed = red;
    output.rgbtGreen = green;
    output.rgbtBlue = blue;
    
    if (red > 255)
    {
        output.rgbtRed = 255;
    }
    if (green > 255)
    {
        output.rgbtGreen = 255;
    }
    if (blue > 255)
    {
        output.rgbtBlue = 255;
    }
    
    
    /*
       output.rgbtRed = round(sqrt( pow(gxR, 2) + pow(gyR, 2)));
        output.rgbtGreen =round(sqrt( pow(gxG, 2) + pow(gyG, 2)));
        output.rgbtBlue = round(sqrt( pow(gxB, 2) + pow(gyB, 2)));

        if (output.rgbtRed > 255)
        {
           output.rgbtRed = 255;
        }
       if (output.rgbtGreen > 255)
        {
          output.rgbtGreen = 255;
        }

        if (output.rgbtBlue > 255)
        {
            output.rgbtBlue = 255;
        }
    */
    return output;
}