#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getLetterCt(string text);
int getWordCt(string text);
int getSentenceCt(string text);
int calcIndex(int letters, int words, int sentences);
double valuePer100(int x, int y);
void displayGradeLv(int index);

int main(void)
{
    string text = get_string("Text: ");
    int letterCt = getLetterCt(text);
    int wordCt = getWordCt(text);
    int sentenceCt = getSentenceCt(text);
    int index = calcIndex(letterCt, wordCt, sentenceCt);
    displayGradeLv(index);
}

/*
get letter count */
int getLetterCt(string text)
{
    // loop through every character in the string
    int letterCt = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        int tempChar = toupper(text[i]) - 65; // sub 65 so A starts at 0
        if (tempChar >= 0 && tempChar <= 26)
        {
            letterCt++; // add to var when tempChar is within range
        }
    }
    return letterCt;
}

/*
get word count */
int getWordCt(string text)
{
    // loop through every character in the string
    int wordCt = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (text[i] == 32)
        {
            wordCt++; // add to word var for every blank space
        }
    }
    return wordCt + 1; // add 1 to count for the first word
}

/*
get sentence count */
int getSentenceCt(string text)
{
    // loop through every character in the string
    int sentenceCt = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentenceCt++;
        }
    }
    return sentenceCt;
}

/*
calc index of text */
int calcIndex(int letters, int words, int sentences) {
    double L = valuePer100(letters, words);
    double S = valuePer100(sentences, words);
    int index = (int)((0.0588 * L - 0.296 * S - 15.8) + 0.5); // add 0.5 to round
    return index;
}

/*
calc letters per words
x per 100y */
double valuePer100(int x, int y)
{
    // divide twice to calc x per 100 y
    double divisor = y / 100.0;
    return x / (double)divisor;
}

/*
display grade level */
void displayGradeLv(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %d", index);
    }
    printf("\n");
}