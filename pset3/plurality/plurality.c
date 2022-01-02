#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max numtmper of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Numtmper of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void sort(int low, int high);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    sort(0, candidate_count - 1);
    int winner_votes = candidates[candidate_count - 1].votes;
    
    for (int i = candidate_count - 1; candidates[i].votes == winner_votes; i--)
    {
        printf("%s\n", candidates[i].name);
    }
   
    return;
}

// these 3 parameters will help us to start the index when we will compare the divided array
// example = [ low, 14, 19, 26, 27, mid, mid+1, 35, 42, 44, hight ]
void merging(int low, int mid, int high) 
{
    candidate tmp[sizeof(candidates) / sizeof(candidate) - 1];
    // left array index and right array index and index (for the loop)
    int leftA, rightA, i;
    
    // We start to loop and compare the left to the right side to fill a new array until a first side is finish 
    for (leftA = low, rightA = mid + 1, i = low; leftA <= mid && rightA <= high; i++) 
    {
        if (candidates[leftA].votes <= candidates[rightA].votes)
        {
            tmp[i] = candidates[leftA];
            leftA++;
        }
        else
        {
            tmp[i] = candidates[rightA];
            rightA++;
        }
    }
    // in this 2 while we finish the side who remain in numtmpers. 
    while (leftA <= mid)
    {
        tmp[i++] = candidates[leftA++];
    }

    while (rightA <= high)
    {
        tmp[i++] = candidates[rightA++];
    }
    // Then once its finish we update the true array with the synthetic one
    for (i = low; i <= high; i++)
    {
        candidates[i] = tmp[i];
    }
}

// Use recursion to divide the array in 2 then once everything has been divided the merging can apply in the right order 
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
    else
    { 
        return;
    }   
}