/**
 * caesar.c
 *
 * Simon Lee
 * silee001@gmail.com
 *
 * Applies the Caesar cipher 
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <cs50.h>

/**
 * Applies the Caesar cipher on character c, with shift key.
 * Identifier is either A or a depending on case.
 */
char cipher(int key, char c, char identifier)
{
    return ( ( c - identifier + key) % 26 ) + identifier;
}

int main(int argc, string argv[])
{

    // Check right number and type of arguments
    if (argc == 1 || argc > 2) 
    {
        printf("Error\n");
        return 1;
    }

    int k = atoi(argv[1]);

    // Check atoi was successful
    if (k == 0)
    {
        printf("Error\n");
        return 1;
    }

    // Get string from user
    string s = GetString();

    // Iterator variable
    int i = 0;

    // Process string in place
    while (s[i])
    {
        // Process cipher depending on case
        if ( s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = cipher(k, s[i], 'A');
        }
        else if ( s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = cipher(k, s[i], 'a');
        }

        i++;
    }

    printf("%s\n", s);

    return 0;
}
