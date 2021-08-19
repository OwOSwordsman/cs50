#include <cs50.h>
#include <stdio.h>

void testTriangle(int x, int y, int z);

int main(void) {
    // sides of triangle
    int x = get_int("First side length: ");
    int y = get_int("Second side length: ");
    int z = get_int("Third side length: ");
    testTriangle(x, y, z);
}

void testTriangle(int x, int y, int z) {
    int lengths[] = {x, y, z};
    int longSide = 0;
    int shortSidesTotal = 0;
    // TODO: check to make sure each side is positive and non zero
    for (int i = 0; i < 3; i++) {
        if (lengths[i] > longSide) {
            shortSidesTotal += longSide;
            longSide = lengths[i];
        }
    }
    if (shortSidesTotal > longSide) {
        printf("Triangle is valid!");
    } else {
        printf("Triangle is invalid!");
    }
    return;
}
