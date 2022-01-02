#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

bool isGoodKey(string key);
string cypher(string key, string text);

int main(int argc, string argv[])
{
    string key = argv[1];
    
    // check if commande line is all good
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return (1);
    }
    else if (!isGoodKey(key))
    {
        return (1);
    }
    
    // Ask the user for a text to cypher
    string plaintext = get_string("plaintext: ");
    // encrypte the message
    string cypherText = cypher(key, plaintext);
    printf("ciphertext: %s\n", cypherText);
    return (0);
}

bool onlyAlpha(string key);
bool isGoodLength(string key);
bool onlyUniqueChar(string key);

// check if the key is made of 26 unique alphabetic charactere. 
bool isGoodKey(string key)
{
    if (!isGoodLength(key)) 
    { 
        return (false);
    }
    if (!onlyAlpha(key)) 
    { 
        return (false);
    }
    if (!onlyUniqueChar(key)) 
    { 
        return (false);
    }
    
    return (true);
}


// check if the key is only made of alphabetic charactere
bool onlyAlpha(string key)
{
    for (int i = 0; key[i]; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must be filled only wich charactere.\n");
            printf("Usage: ./substitution key\n");
            return (false);
        }
    }
    return (true);
}

// check if the length of the key is good 
bool isGoodLength(string key)
{
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        printf("Usage: ./substitution key\n");
        return (false);
    }
    return (true);
}

// check if the key is not made of double same charactere
bool onlyUniqueChar(string key)
{
    // make an array of 26 integers and then clean each slot 
    int alphabet_array[strlen(key)];
    for (int i = 0; i < (sizeof(alphabet_array) / sizeof(alphabet_array[0])); i++) 
    {
        alphabet_array[i] = 0;
    }
    
    // check if there's no double letters in the key
    for (int i = 0; key[i]; i++)
    {
        if (key[i] < 97)
        {
            alphabet_array[key[i] - 65] += 1;
            if (alphabet_array[key[i] - 65] > 1)
            {
                printf("Key must be filled only wich UNIQUE characteres!\n");
                printf("charactere printed twice %c\n", key[i]);
                return (false); 
            }
        }
        else 
        {
            alphabet_array[key[i] - 97] += 1;
            if (alphabet_array[key[i] - 97] > 1)
            {
                printf("Key must be filled only wich UNIQUE characteres!\n");
                printf("charactere printed twice %c\n", key[i]);
                return (false); 
            }
        }
    }
    return (true);
}

string cypher(string key, string text)
{
    for (int i = 0; text[i]; i++)
    {
        if (isalpha(text[i]))
        {
            if (text[i] < 97)
            {
                char letter = key[(int) text[i] - 65];
                text[i] = islower(letter) ? letter - 32 : letter;
            }
            else
            {
                char letter = key[(int) text[i] - 97];
                text[i] = isupper(letter) ? letter + 32 : letter;
            }
            
        }
    }

    return (text);
}