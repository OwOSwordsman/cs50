#include <cs50.h>
#include <stdio.h>

void meow(int num);

int main(void) {
    meow(3);
}

void meow(int num) {
    for (int i = 0; i < num; i++) {
        printf("meow\n");
    }
}