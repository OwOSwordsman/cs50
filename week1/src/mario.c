#include <cs50.h>
#include <stdio.h>

// prototypes
void printGap(int height, int i);
void printSide(int height, int i);

int main(void) {
    // prompt for pyramid height
    int height;
    do {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    // print pyramid
    for (int i = 0; i < height; i++) {  // layer by layer
        printGap(height, i);
        printSide(height, i);
        printf("  ");
        printSide(height, i);
        printf("\n");
    }
}

/*
prints the gap on the left side */
void printGap(int height, int i) {
    for (int j = 0; j < height - i - 1; j++) {
        printf(" ");
    }
}

/*
prints the side of the pyramid */
void printSide(int height, int i) {
    for (int j = 0; j < i + 1; j++) {  // right side
        printf("#");
    }
}