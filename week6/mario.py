def main():
    height = 0
    # continue to prompt until appropriate height
    while height < 1 or height > 8:
        try:    # catch non int entries
            height = int(input('Height: '))
        except:
            height = 0
    buildPyramid(height)


""" build pyramid """
def buildPyramid(height):
    # loop through each level
    for i in range(1, height + 1):
        buildLeft(height, i)
        buildRight(i)


""" build left half """
def buildLeft(height, index):
    # fill in empty spaces
    for _ in range(height - index):
        print(' ', end = '')

    # print bricks
    for _ in range(index):
        print('#', end = '')
    print('  ', end = '')


""" build right half """
def buildRight(height):
    # print bricks
    for _ in range(height):
        print('#', end = '')
    print()


if __name__ == '__main__': main()