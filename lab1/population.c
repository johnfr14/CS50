#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user for a starting population size
    int start_size = get_int("How much is the starting size of the population ?: ");
    
    // Ask again if the answer is under 9.
    while (start_size < 9)
    {
        start_size = get_int("The population must start by at least 9 or more: ");
    }

    // Ask the user for a ending population size
    int end_size = get_int("How much is the end size of the population ?: ");
    
    // Ask again if the answer is under or equal than the starting population.
    while (end_size < start_size)
    {
        end_size = get_int("The end population must be above the starting population: ");
    }
    
    // initialisation of the born & death rate + the population & the years required
    float born_rate = 3;
    float death_rate = 4;
    float population = start_size;
    int n = 0;
 
    if (population >= end_size)
    {
        printf("Years: %i", n);
        return (0);
    } 
    else 
    {
        // As long as we did not get the ending numbers of the populations we continue the loop 
        while (population < end_size) 
        {
            population += population / born_rate - population / death_rate;
            population >= end_size ? ' ' : n++;
        };
 
        // Print the result
        printf("Years: %i", n);
    }
}