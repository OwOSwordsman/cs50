def main():
    cardNum = promptCardNum()
    validity = checkNum(cardNum)
    if validity:
        print("INVALID")
        return
    deterCard(cardNum)


""" prompt for card num """
def promptCardNum():
    num = 0
    while num == 0:
        try:    # catch non integer inputs
            num = int(input("Number: "))
        except:
            num = 0
    return num



""" check the validity of the card num """
def checkNum(cardNum):
    # check num length
    if len(str(cardNum)) not in [15, 16, 13]: return False

    # check digit sums
    digitSum = calcDigits(cardNum)
    if digitSum % 10 != 0: return False


"""
get every other digit starting from the second last
double the value and sum their digits
sum the rest of the digits and sum the sums """
def calcDigits(cardNum):
    multipliedSum = 0
    remainingSum = 0

    # loop through every digit
    while (cardNum // 10) != 0:
        # last digit
        remainingSum += cardNum % 10
        cardNum //= 10

        # second to last digit
        multipliedSum += sumDigits(cardNum % 10 * 2)
        cardNum //= 10

    # add remaining digits if num was odd
    if cardNum != 0: remainingSum += cardNum

    return multipliedSum + remainingSum


""" sum digits """
def sumDigits(num):
    sum = 0
    while num != 0: # check to make sure num is not zero
        sum += num % 10
        num //= 10
    return sum


""" determine card type """
def deterCard(cardNum):
    firstTwoDigits = int(str(cardNum)[0] + str(cardNum)[1])
    if str(cardNum)[0] == "4":
        print("VISA")
    elif firstTwoDigits in [34, 37]:
        print("AMEX")
    elif firstTwoDigits in [51, 52, 53, 54, 55]:
        print("MASTERCARD")
    else:
        print("INVALID")


if __name__ == "__main__": main()