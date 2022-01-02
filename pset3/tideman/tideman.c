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
bool back_tracking(int origin_pair, int locker);

void print_pairs();
void print_locked();
void print_preference();

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
        int ranks[] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // check for each candidat if the one chosen by voter exist if yes put the candidat in his rank
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // check if the candidate has already been chosen by voter in his ranks
            for (int j = 0; j < candidate_count; j++)
            {
                if (ranks[j] == i)
                {
                    printf("Candidat already chose\n");
                    return false;
                }
            }

            ranks[rank] = i;
            return true;
        }
    }
    printf("Candidat don't exist\n");
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

void merging(int low, int mid, int high);
void sort(int low, int high);
// Sort pairs in decreasing order by strength of victory
// Use recursion to divide the array in 2 then once everything has been divided the merging can apply in the right order
void sort_pairs()
{
    sort(0, pair_count - 1);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // check for all the pairs
    for (int i = 0; i < pair_count; i++)
    {
        // if a candidat is already locked we will find out the preference difference to not make a loop
        for (int j = 0; j < candidate_count; j++)
        {
            // if the winner is already locked by somenone
            if (locked[j][pairs[i].winner] && i != j)
            {
                if (back_tracking(i, j))
                {
                    i++;
                    j = -1;
                }
            }
        }
        if (i < pair_count)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                j = 0;
                i++;
            }
        }
        if (i < candidate_count)
        {
            printf("the winner is %s\n", candidates[i]);
        }
        else
        {
            printf("ERROR");
            return;
        }
    }
    return;
}

// these 3 parameters will help us to start the index when we will compare the divided array
// example = [ low, 14, 19, 26, 27, mid, mid+1, 35, 42, 44, hight ]
void merging(int low, int mid, int high)
{
    pair tmp[sizeof(pairs) / sizeof(pair) - 1];
    // left array index and right array index and index (for the loop)
    int leftA, rightA, i;

    // We start to loop and compare the left to the right side to fill a new array until a first side is finish
    for (leftA = low, rightA = mid + 1, i = low; leftA <= mid && rightA <= high; i++)
    {
        if (preferences[pairs[leftA].winner][pairs[leftA].loser] >= preferences[pairs[rightA].winner][pairs[rightA].loser])
        {
            tmp[i] = pairs[leftA];
            leftA++;
        }
        else
        {
            tmp[i] = pairs[rightA];
            rightA++;
        }
    }
    // in this 2 while we finish the side who remain in numtmpers.
    while (leftA <= mid)
    {
        tmp[i++] = pairs[leftA++];
    }

    while (rightA <= high)
    {
        tmp[i++] = pairs[rightA++];
    }
    // Then once its finish we update the true array with the synthetic one
    for (i = low; i <= high; i++)
    {
        pairs[i] = tmp[i];
    }
}

void sort(int low, int high)
{
    int mid;
    // if low is equal that means that the index is same so we can't divide anymore
    if (low < high)
    {
        mid = (low + high) / 2;
        // divide left side again
        sort(low, mid);
        // divide right side again
        sort(mid + 1, high);
        // sort everything depending of the index given (low, mid, hight)
        merging(low, mid, high);
    }
    return;
}
// will track if there is no cycle in the winners/losers pairs
bool back_tracking(int origin_pair, int locker)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][locker] && i != locker)
        {
            if (pairs[origin_pair].loser == pairs[i].winner)
            {
                return true;
            }
            else
            {
                return back_tracking(origin_pair, i);
            }
        }
    }
    return false;
}
