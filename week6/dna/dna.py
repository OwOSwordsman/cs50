from sys import argv
from sys import exit
from csv import DictReader


def main():
    checkArgs()
    database = readDatabase()
    sequence = readSequence()
    STRs = getSTRLengths(sequence, database)
    matchDatabase(STRs, database)


""" check for two arguments """


def checkArgs():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)


""" read database into a dictionary list """


def readDatabase():
    with open(argv[1]) as f:  # open database file
        csvData = DictReader(f)
        database = []
        for entry in csvData:  # loop through all the csv entries and add to dictionary
            database.append(entry)
        return database


""" read input sequence """


def readSequence():
    with open(argv[2]) as f:  # open sequence file
        return f.read()


""" get maximum STR sequence lengths """


def getSTRLengths(sequence, database):
    # get list of all targets
    targets = []
    for i in database[1]:
        targets.append(i)
    targets.pop(0)

    # get STR for target and store in dict
    STRDict = {}
    for target in targets:
        STRDict[target] = getSTR(sequence, target)

    return STRDict


""" get STR length for specified target """


def getSTR(sequence, target):
    maxRepeats = 0
    searchThreshold = (
        len(sequence) - len(target) + 1
    )  # ensure enough chars to search for target

    for i in range(
        searchThreshold
    ):  # loop through sequence while ensuring enough chars for target

        sequencesFound = 0  # tmp var to track STRs
        while i < searchThreshold:
            if (
                sequence[i : i + len(target)] == target
            ):  # split string to size of target

                # target was found, look for more
                i += len(target)
                sequencesFound += 1
            else:  # not found
                break

        if sequencesFound > maxRepeats:  # update max repeats if tmp var is greater
            maxRepeats = sequencesFound
    return maxRepeats


""" check for matching person in database """


def matchDatabase(STRs, database):
    # check for matching STR values and remove people from database that don't match
    updatedDatabase = database
    for STR in STRs:
        # update database
        database = updatedDatabase
        updatedDatabase = []

        # loop through every person and check if they have matching STR
        for person in database:
            if int(person[STR]) == STRs[STR]:
                updatedDatabase.append(person)

    # print matched person
    if len(updatedDatabase) == 0:  # person not found
        print("No match")
    else:  # person found
        for i in updatedDatabase:
            print(i["name"])


if __name__ == "__main__":
    main()
