#include <stdio.h>
#include <cs50.h>

int collatzCalc(int n);

int main(void) {
    int number = get_int("Enter a positive number: ");
    int collatz = collatzCalc(number);
    printf("Iterations: %d\n", collatz);
}

int collatzCalc(int n) {
    if (n == 1) return 0;
    if (n % 2 == 0) {
        return 1 + collatzCalc(n / 2);
    } else {
        return 1 + collatzCalc(3 * n + 1);
    }
}