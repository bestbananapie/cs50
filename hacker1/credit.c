/**
 * credit.c
 *
 * Simon Lee
 * silee001@gmail.com
 *
 * Validates an inputed credit number and tries to identify issuer
 *
 */

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Uses the Luhn Algorithm to validate CC against checksum.
 * Returns 1 if CC is valid number.
 * Algoritm works by summing all the individal digits of the number with these
 * rules:
 *  > Every 2nd number (starting from the right) is multiplied by two
 *    and having the individual digits added to the checksum
 *  > Last digit of sum to match last digit of card number
 */
int cc_valid(long long int cc_num)
{
    // Boolean toggle to determine if number should be multiplied by 2
    int multiplier = 0;

    // Digits of CC.
    int digit = 0;

    int check_sum = 0;

    while(cc_num)
    {
        // Use modulus to extract last digit
        digit = (int) (cc_num % 10);

        // Divide by 10 to 'pop' last digit out. Remember: Not a float
        cc_num /= 10;

        // Multiple digit by two if appropriate.
        digit *= multiplier ? 2 : 1;

        // Add Individual digits to checksum
        while(digit)
        {
            check_sum += digit % 10;
            digit /= 10;
        }

        // Toggle multiplier boolean.
        multiplier = !multiplier;
    }
    
    return ( (check_sum % 10) - (int) (cc_num % 10) ) == 0;
}

/**
 * Uses the first 2 digits of the cc to try and identify issuer
 * and is return in passed char array
 */
void cc_issuer(long long int cc_num, char* issuer)
{   
    // Represents first and digit of CC
    int first_digit = 0;
    int second_digit = 0;

    /* Shift through all numbers right to left. At end of routine  */
    /* first and second numbers will be stored */
    while (cc_num)
    {
        second_digit = first_digit;
        first_digit = (int) (cc_num % 10);
        cc_num /= 10;
    }

    // Identity Issuer
    if (first_digit == 3 && ( second_digit == 4 || second_digit == 7 ))
    {
        sprintf(issuer, "AMEX");
    } 
    else if (first_digit == 4)
    {
        sprintf(issuer, "VISA");
    } 
    else if (first_digit == 5 && second_digit >= 1 && second_digit <= 5)
    {
        sprintf(issuer, "MASTERCARD");
    }
    else
    {
        sprintf(issuer, "INVALID");
    }
}

int main(void)
{
    // Variable for CC number
    long long int cc_num = 0;

    // String for CC issuer
    char issuer[255];

    // Get input from stdio
    do 
    {
        printf("Number: ");
        cc_num = GetLongLong();
    }
    while (cc_num < 0);

    // If number is valid, check for issuer. Else print error
    if (cc_valid(cc_num))
    {
        cc_issuer(cc_num, issuer);
        printf("%s\n", issuer);
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
