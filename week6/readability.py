def main():
    text = input("Text: ")
    letterCt = getLetterCt(text)
    wordCt = getWordCt(text)
    sentenceCt = getSentenceCt(text)
    index = calcIndex(letterCt, wordCt, sentenceCt)
    displayGradeLv(index)


""" get letter count """


def getLetterCt(text):
    letterCt = 0
    # loop through every char and check for letters
    for char in text:
        if char.isalpha():
            letterCt += 1
    return letterCt


""" get word count """


def getWordCt(text):
    wordCt = 1  # start at 1 to account for first word
    # loop through every char and check for spaces
    for char in text:
        if char.isspace():
            wordCt += 1
    return wordCt


""" get sentence count """


def getSentenceCt(text):
    sentenceCt = 0
    # loop through every char and check for .!?
    for char in text:
        if char in [".", "!", "?"]:
            sentenceCt += 1
    return sentenceCt


""" calc readability index """


def calcIndex(letters, words, sentences):
    L = valPer100(letters, words)   # letters per 100 words
    S = valPer100(sentences, words) # sentences per 100 words
    index = int(((0.0588 * L - 0.296 * S - 15.8) + 0.5))  # add 0.5 to round
    return index


""" calc x per 100y """


def valPer100(x, y):
    # divide twice to calc x per 100 y
    divisor = y / 100
    return x / divisor


""" display grade level """


def displayGradeLv(index):
    if index < 1:   # before grade 1
        print("Before Grade 1")
    elif index >= 16:   # grades 16+
        print("Grade 16+")
    else:   # grades 1 to 15
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
