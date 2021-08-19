#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string getKey(int argc, string s, char key[]);
string encrypt(string key, string plainTxt, char cipherTxt[]);

int main(int argc, string argv[]) {
    char inputKey[26];
    string key = getKey(argc, argv[1], inputKey);
    if (strlen(key) == 0) return 1; // end program if key is invalid
    string plainTxt = get_string("plaintext: ");
    char inputTxt[strlen(plainTxt) + 1];
    string cipherTxt = encrypt(key, plainTxt, inputTxt);
    printf("ciphertext: %s\n", cipherTxt);
    return 0;
}

/*
check and convert key */
string getKey(int argc, string s, char key[]) {
    // argc must be 2 and s must be 26
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return "";
    } else if (strlen(s) != 26) {
        printf("Key must contain 26 characters\n");
        return "";
    }

    // check for invalid chars
    for (int i = 0, l = strlen(s); i < l; i++) {
        if ((s[i] < 'A') || (s[i] > 'Z' && s[i] < 'a') || (s[i] > 'z')) {   // contains non letters
            printf("Key must contain only letters\n");
            return "";
        }
    }

    // change every character to upper and ct occurrences
    int usedLetter[26];
    for (int i = 0; i < 26; i++) {  // zero all the values
        usedLetter[i] = 0;
    }

    for (int i = 0, l = strlen(s); i < l; i++) {
        char tempChar = toupper(s[i]);
        usedLetter[tempChar - 'A'] += 1;
        for (int j = 0; j < 26; j++) {
            if (usedLetter[j] > 1) {    // repeated letter
                printf("Key must not contain any duplicate characters\n");
                return "";
            }
        }
        key[i] = tempChar;
    }
    return key;
}

/*
encrypt text with key */
string encrypt(string key, string plainTxt, char cipherTxt[]) {
    for (int i = 0, l = strlen(plainTxt); i < l; i++) { // sub 1 to account for the final null char
        // encrypt text based on if char is lower, upper, or other
        bool isLower = islower(plainTxt[i]);
        bool isUpper = isupper(plainTxt[i]);
        if (isLower) {  // lowercase char
            cipherTxt[i] = key[plainTxt[i] - 'A' - 32] + 32; // subtract char so A is 0 and 32 to account for the lowercase
        } else if (isUpper) { // uppercase char
            cipherTxt[i] = key[plainTxt[i] - 'A']; // subtract char so A is 0
        } else { // other
            cipherTxt[i] = plainTxt[i];
        }
        // printf("%c", cipherTxt[i]);  // LOG
    }
    cipherTxt[strlen(plainTxt)] = '\0';
    // printf("\n%s\n", cipherTxt); // LOG
    return cipherTxt;
}