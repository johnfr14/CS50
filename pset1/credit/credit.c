#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    // Ask for the card numbers
    long card_numbers;
    card_numbers = get_long("Number: ");
    
    // We extract the cheksum and the total of all the even numbers in the card
    long checksum = 0;
    long total_even_numbers = 0;
    for (long i = card_numbers; i > 0; i = i / 100)
    {
        total_even_numbers += i % 10;
        
        long digit = ((i / 10) % 10) * 2;
        if (digit > 9)
        {
            while (digit > 0)
            {
                checksum += digit % 10;
                digit /= 10;
            }
        }
        else
        {
            checksum += digit;
        }
    }
    
    // calcul the length of the card
    int card_length = 0;
    for (long i = card_numbers; i >= 1; i = i / 10)
    {
        card_length++;
    }
    
   
    // check all the conditions if its wether a "VISA/MASTERCARD/AMERICAN EXPRESS" or an INVALID card
    // first check if this a valid card with the checksum
    if ((checksum + total_even_numbers) % 10 != 0)
    {
        printf("INVALID\n");
    }
    // then defining the length and how start the numbers we find the type or if its a valid card
    else
    {
        long start = 0;
        switch (card_length)
        {
            case 13:
                start = card_numbers / (1e12);
                start == 4 ? printf("VISA\n") : printf("INVALID\n");
                break;
            case 15:
                start = card_numbers / (1e13);
                if (start == 34 || start == 37)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 16:
                start = card_numbers / (1e14);
                if (start / 10 == 4)
                {
                    printf("VISA\n");
                }
                else if (start >= 51 && start <= 55)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            default:
                printf("INVALID\n");
        }
    }
}