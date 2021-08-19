#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    // LOG: check the prefs array

    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            printf("%d", preferences[i][j]);
        }
        printf("\n");
    }


    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        if (!strcmp(candidates[i], name)) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
int pairsCounter = 0;
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i; j < candidate_count; j++) {
            if (i == j) continue;   // candidate is going against themselves
            int temp1 = preferences[i][j];
            int temp2 = preferences[j][i];
            if (temp1 == temp2) continue; // they tie
            pair tempPair;
            if (temp1 > temp2) {    // pref ij is the winner
                tempPair.winner = i;
                tempPair.loser = j;
            } else {    // pref ji is the winner
                tempPair.winner = j;
                tempPair.loser = i;
            }
            pairs[pairsCounter] = tempPair;
            pairsCounter++;
            printf("%d", pairsCounter);
        }
    }

    // LOG: check pairs array
    /*
    for (int i = 0; i < pairsCounter; i++) {
        printf("winner: %d\n", pairs[i].winner);
        printf("loser: %d\n\n", pairs[i].loser);
    }
    return;
    */
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // LOG: before sort
    /*
    for (int i = 0; i < pairsCounter; i++) {
        printf("%d", preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
    }
    printf("\n");
    */

    bool swap = false;
    int currentPos = 0;
    int maxDiff = 0;
    do {
        swap = false;
        int maxDiffIndex = 0;
        for (int i = currentPos; i < pairsCounter; i++) {
            int index1 = pairs[i].winner;
            int index2 = pairs[i].loser;
            int curDiff = preferences[index1][index2] - preferences[index2][index1];
            if (curDiff > maxDiff) {
                maxDiff = curDiff;
                maxDiffIndex = i;
                swap = true;
            }
        }
        if (swap) {
            pair tempPair = pairs[currentPos];
            pairs[currentPos] = pairs[maxDiffIndex];
            pairs[maxDiffIndex] = tempPair;
        }
    } while (swap);

    // LOG: after sort
    /*
    for (int i = 0; i < pairsCounter; i++) {
        printf("%d", preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
    }
    printf("\n");
    */

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pairsCounter; i++) {    // cycle through all the pairs
        locked[pairs[i].winner][pairs[i].loser] = true;
        int isEdged = 0;
        for (int j = 0; j < pairsCounter; j++) {    // check each column to make sure there is at least one candidate who is not edged
            for (int k = 0; k < pairsCounter; k++) {
                if (locked[k][j] == true) isEdged++;
            }
        }
        // if each candidate is edged then undo last edge
        if (isEdged == candidate_count) locked[pairs[i].winner][pairs[i].loser] = false;
    }

    // LOG: print lock pairs array
    for (int i = 0; i < pairsCounter; i++) {
        for (int j = 0; j < pairsCounter; j++) {
            printf("%d", locked[i][j]);
        }
        printf("\n");
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // cycle through all the columns
    for (int j = 0; j < pairsCounter; j++) {
        bool isEdged = false;
        for (int k = 0; k < pairsCounter; k++) {
            if (locked[k][j] == true) isEdged = true;
        }
        if (!isEdged) {
            string winner = candidates[j];
            printf("%s\n", winner);
        }
    }
    return;
}
