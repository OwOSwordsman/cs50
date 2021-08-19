#include <cs50.h>
#include <stdio.h>

bool checkCardNum(long cardNum, int length);
int sumEveryOtherDigit(long cardNum);
int sumDigits(int num);
int getNumLength(long cardNum);
int getBeginningCardNumber(long cardNum, int length);
long getPower10(int length);
void determineCard(int beginingDigits, int length);

int main(void)
{
    // prompt credit card number
    long cardNum = get_long("Number: ");
    int cardNumLength = getNumLength(cardNum);
    bool isValid = checkCardNum(cardNum, cardNumLength);
    // printf("%i\n", isValid); // LOG
    if (!isValid)
    {
        // print invalid if card is not valid and end program
        printf("INVALID\n");
        return 0;
    }

    // printf("%li\n", cardNumLength);    // LOG
    int beginingDigits = getBeginningCardNumber(cardNum, cardNumLength);
    // printf("%i\n", beginingDigits); // LOG
    determineCard(beginingDigits, cardNumLength);
}

/*
determine if card is legit */
bool checkCardNum(long cardNum, int length)
{
    // check if cardnumber length is valid
    if (length != 15 && length != 16 && length != 13)
    {
        return false;
    }

    // sums digits and make sure it is a multiple of 10
    int digitSum = sumEveryOtherDigit(cardNum);
    // printf("%i\n", digitSum); // LOG
    if (!(digitSum % 10 == 0 && getNumLength(cardNum)))
    {
        return false;
    }
    return true;
}

/*
get every other number starting from second to last
multiply each by two and sum all the digits
sum the previous sum and the other digits */
int sumEveryOtherDigit(long cardNum)
{
    int multipliedSum = 0;
    int remainingSum = 0;
    while (cardNum / 10 != 0)
    {
        // check make sure there are at least 2 digits left
        int tempNum = cardNum % 10;
        // printf("%i\n", tempNum); // LOG
        remainingSum += tempNum;
        cardNum /= 10;
        tempNum = cardNum % 10 * 2;
        multipliedSum += sumDigits(tempNum);
        cardNum /= 10;
    }
    // add the remaining digit if cardNum was odd
    if (cardNum != 0)
    {
        remainingSum += cardNum;
    }
    return multipliedSum + remainingSum;
}

/*
sum digits */
int sumDigits(int num)
{
    int sum = 0;
    while (num != 0)
    {
        // check to make sure num is not zero
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

/*
determine validity of number length */
int getNumLength(long num)
{
    int length = 0;
    while (num > 0)
    {
        num /= 10;
        length++;
    }
    return length;
}

/*
get first two digits of card number */
int getBeginningCardNumber(long cardNum, int length)
{
    // printf("%li\n", getPower10(length)); // LOG
    int beginNums = cardNum / getPower10(length);
    return beginNums;
}

/*
get power 10 */
long getPower10(int length)
{
    long power10 = 1;
    for (int i = 0; i < length; i++)
    {
        power10 *= 10;
    }
    return power10 / 100;
}

/*
determines the card type */
void determineCard(int beginingDigits, int length)
{
    // printf("%i/n", beginingDigits); // LOG
    if ((beginingDigits == 34 || beginingDigits == 37) && length == 15)
    {
        printf("AMEX\n");
    }
    else if (((beginingDigits >= 51 && beginingDigits <= 55) || beginingDigits == 22) && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((beginingDigits / 10 == 4) && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}