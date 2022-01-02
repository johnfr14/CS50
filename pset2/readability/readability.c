#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Ask the text to grade
    string text = get_string("Text: ");
    // will make an array in each index will be made as [letter, word, sentence].
    int letter_word_sentence[3] = {0, 0, 0};
    // This loop will check each charactere and increment count wether its a letter, word or sentence
    for (int i = 0; i <= strlen(text); i++)
    {
        // Is it a letter ?
        isalpha(text[i]) ? letter_word_sentence[0] += 1 : ' ';
        // Is it a word ?
        isspace(text[i]) ? letter_word_sentence[1] += 1 : ' ';y
        // are we in the end of a sentence or a word ?
        if (ispunct(text[i]))
        {
            if (text[i] == '\'')
            {
                letter_word_sentence[1] += 1;
            }
            else if (text[i] == ',' || text[i] == ';' || text[i] == '-' || text[i] == '\"') {}
            else
            {
                letter_word_sentence[2] += 1;
            }
        }
        else if (text[i] == '\0')
        {
            letter_word_sentence[1] += 1;
        }
    }
    // calcul the average number of letters per 100 words in the text.
    float average_L = (100 * letter_word_sentence[0]) / (float) letter_word_sentence[1];
    // calcul the average number of sentences per 100 words in the text.
    float average_S = (100 * letter_word_sentence[2]) / (float) letter_word_sentence[1];
    
    int grade = ceil(0.0588 * average_L - 0.296 * average_S - 15.8);
    
    // Print the result grade of text text given
    if (grade < 0)
    {
        printf("Before Grade 1\n");
    } 
    else if (grade <= 16)
    {
        printf("Grade %i\n", grade);
    } 
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
}