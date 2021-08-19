#include "helpers.h"
#include <math.h>

void addAvgColors(int* avgRed, int* avgGreen, int* avgBlue, int* surroundingPxCt, int height, int width, int row, int col, RGBTRIPLE ogImage[height][width]);
int calcMagnitude(int color[]);
int calcGx(int color[]);
int calcGy(int color[]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int avgShade = 0;
            avgShade += image[row][col].rgbtBlue;
            avgShade += image[row][col].rgbtGreen;
            avgShade += image[row][col].rgbtRed;
            avgShade = avgShade / 3.0 + 0.5;
            image[row][col].rgbtBlue = avgShade;
            image[row][col].rgbtGreen = avgShade;
            image[row][col].rgbtRed = avgShade;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++) {
        for (int col = 0, half = width / 2; col < half; col++) {
            RGBTRIPLE tmpPixel = image[row][col];
            RGBTRIPLE* swapPixel = &image[row][width - col - 1];
            image[row][col] = *swapPixel;
            (*swapPixel) = tmpPixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ogImage[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ogImage[i][j] = image[i][j];
        }
    }

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < height; col++) {
            int avgRed = 0;
            int avgGreen = 0;
            int avgBlue = 0;
            int surroundingPxCt = 0;
            if ((row - 1) >= 0 && (col - 1) >= 0) { // top left
                addAvgColors(&avgRed, &avgGreen, &avgBlue, &surroundingPxCt, height, width, row - 1, col - 1, ogImage);
            }
            if ((row - 1) >= 0) {   // top center
                addAvgColors(&avgRed, &avgGreen, &avgBlue, &surroundingPxCt, height, width, row - 1, col, ogImage);
            }
            if ((row - 1) >= 0 && (col + 1) < width) {  // top right
                addAvgColors(&avgRed, &avgGreen, &avgBlue, &surroundingPxCt, height, width, row - 1, col + 1, ogImage);
            }
            if (col - 1 >= 0) { // middle left
                addAvgColors(&avgRed, &avgGreen, &avgBlue, &surroundingPxCt, height, width, row, col - 1, ogImage);
            }
            // middle center
                addAvgColors(&avgRed, &avgGreen, &avgBlue, &surroundingPxCt, height, width, row, col, ogImage);

            if (col + 1 < width) {  // middle right
                addAvgColors(&avgRed, &avgGreen, &avgBlue, &surroundingPxCt, height, width, row, col + 1, ogImage);
            }
            if ((row + 1) < height && (col - 1) >= 0) { // bottom left
                addAvgColors(&avgRed, &avgGreen, &avgBlue, &surroundingPxCt, height, width, row + 1, col - 1, ogImage);
            }
            if ((row + 1) < height) {   // bottem center
                addAvgColors(&avgRed, &avgGreen, &avgBlue, &surroundingPxCt, height, width, row + 1, col, ogImage);
            }
            if ((row + 1) < height && (col + 1) < width) {  // bottom right
                addAvgColors(&avgRed, &avgGreen, &avgBlue, &surroundingPxCt, height, width, row + 1, col + 1, ogImage);
            }

            avgRed = avgRed / (double) surroundingPxCt + 0.5;
            avgGreen = avgGreen / (double) surroundingPxCt + 0.5;
            avgBlue = avgBlue / (double) surroundingPxCt + 0.5;
            image[row][col].rgbtRed = avgRed;
            image[row][col].rgbtGreen = avgGreen;
            image[row][col].rgbtBlue = avgBlue;
        }
    }
    return;
}

void addAvgColors(int* avgRed, int* avgGreen, int* avgBlue, int* surroundingPxCt, int height, int width, int row, int col, RGBTRIPLE ogImage[height][width]) {
    *avgRed += ogImage[row][col].rgbtRed;
    *avgGreen += ogImage[row][col].rgbtGreen;
    *avgBlue += ogImage[row][col].rgbtBlue;
    *surroundingPxCt += 1;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ogImage[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ogImage[i][j] = image[i][j];
        }
    }

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int red[9];
            int green[9];
            int blue[9];
            int curRow;
            int curCol;
            int curIndex;

            curIndex = 0;
            if ((row - 1) >= 0 && (col - 1) >= 0) { // top left
                curRow = row - 1;
                curCol = col - 1;
                red[curIndex]= ogImage[curRow][curCol].rgbtRed;
                green[curIndex] = ogImage[curRow][curCol].rgbtGreen;
                blue[curIndex] = ogImage[curRow][curCol].rgbtBlue;
            } else {
                red[curIndex] = 0;
                green[curIndex] = 0;
                blue[curIndex] = 0;
            }
            curIndex = 1;
            if ((row - 1) >= 0) {   // top center
                curRow = row - 1;
                curCol = col;
                red[curIndex]= ogImage[curRow][curCol].rgbtRed;
                green[curIndex] = ogImage[curRow][curCol].rgbtGreen;
                blue[curIndex] = ogImage[curRow][curCol].rgbtBlue;
            } else {
                red[curIndex] = 0;
                green[curIndex] = 0;
                blue[curIndex] = 0;
            }
            curIndex = 2;
            if ((row - 1) >= 0 && (col + 1) < width) {  // top right
                curRow = row - 1;
                curCol = col + 1;
                red[curIndex]= ogImage[curRow][curCol].rgbtRed;
                green[curIndex] = ogImage[curRow][curCol].rgbtGreen;
                blue[curIndex] = ogImage[curRow][curCol].rgbtBlue;
            } else {
                red[curIndex] = 0;
                green[curIndex] = 0;
                blue[curIndex] = 0;
            }
            curIndex = 3;
            if (col - 1 >= 0) { // middle left
                curRow = row;
                curCol = col - 1;
                red[curIndex]= ogImage[curRow][curCol].rgbtRed;
                green[curIndex] = ogImage[curRow][curCol].rgbtGreen;
                blue[curIndex] = ogImage[curRow][curCol].rgbtBlue;
            } else {
                red[curIndex] = 0;
                green[curIndex] = 0;
                blue[curIndex] = 0;
            }

            curIndex = 4;
            // middle center
                curRow = row;
                curCol = col;
                red[curIndex]= ogImage[curRow][curCol].rgbtRed;
                green[curIndex] = ogImage[curRow][curCol].rgbtGreen;
                blue[curIndex] = ogImage[curRow][curCol].rgbtBlue;

            curIndex = 5;
            if (col + 1 < width) {  // middle right
                curRow = row;
                curCol = col + 1;
                red[curIndex]= ogImage[curRow][curCol].rgbtRed;
                green[curIndex] = ogImage[curRow][curCol].rgbtGreen;
                blue[curIndex] = ogImage[curRow][curCol].rgbtBlue;
            } else {
                red[curIndex] = 0;
                green[curIndex] = 0;
                blue[curIndex] = 0;
            }
            curIndex = 6;
            if ((row + 1) < height && (col - 1) >= 0) { // bottom left
                curRow = row + 1;
                curCol = col - 1;
                red[curIndex]= ogImage[curRow][curCol].rgbtRed;
                green[curIndex] = ogImage[curRow][curCol].rgbtGreen;
                blue[curIndex] = ogImage[curRow][curCol].rgbtBlue;
            } else {
                red[curIndex] = 0;
                green[curIndex] = 0;
                blue[curIndex] = 0;
            }
            curIndex = 7;
            if ((row + 1) < height) {   // bottem center
                curRow = row + 1;
                curCol = col;
                red[curIndex]= ogImage[curRow][curCol].rgbtRed;
                green[curIndex] = ogImage[curRow][curCol].rgbtGreen;
                blue[curIndex] = ogImage[curRow][curCol].rgbtBlue;
            } else {
                red[curIndex] = 0;
                green[curIndex] = 0;
                blue[curIndex] = 0;
            }
            curIndex = 8;
            if ((row + 1) < height && (col + 1) < width) {  // bottom right
                curRow = row + 1;
                curCol = col + 1;
                red[curIndex]= ogImage[curRow][curCol].rgbtRed;
                green[curIndex] = ogImage[curRow][curCol].rgbtGreen;
                blue[curIndex] = ogImage[curRow][curCol].rgbtBlue;
            } else {
                red[curIndex] = 0;
                green[curIndex] = 0;
                blue[curIndex] = 0;
            }
            int edgeRed = calcMagnitude(red);
            int edgeGreen = calcMagnitude(green);
            int edgeBlue = calcMagnitude(blue);
            image[row][col].rgbtRed = edgeRed;
            image[row][col].rgbtGreen = edgeGreen;
            image[row][col].rgbtBlue = edgeBlue;
        }
    }
    return;
}

int calcMagnitude(int color[]) {
    int gx = calcGx(color);
    int gy = calcGy(color);
    int magnitude = sqrt(pow(gx, 2) + pow(gy, 2)) + 0.5;
    if (magnitude > 255) magnitude = 255;
    return magnitude;
}

int calcGx(int color[]) {
    int gx = 0;
    gx += color[0] * -1;
    gx += color[2] * 1;
    gx += color[3] * -2;
    gx += color[5] * 2;
    gx += color[6] * -1;
    gx += color[8] * 1;
    return gx;
}

int calcGy(int color[]) {
    int gy = 0;
    gy += color[0] * -1;
    gy += color[1] * -2;
    gy += color[2] * -1;
    gy += color[6] * 1;
    gy += color[7] * 2;
    gy += color[8] * 1;
    return gy;
}