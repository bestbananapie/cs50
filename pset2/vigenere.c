/**
 * vigenere.c
 *
 * Simon Lee
 * silee001@gmail.com
 *
 * Applies the Vigenere cipher 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

    // Check right number command line arguments
    if (argc == 1 || argc > 2) 
    {
        printf("Error\n");
        return 1;
    }

    // Iterator for string
    int i = 0;

    string key_word = argv[1];

    // Check the key word only contains letters
    while (key_word[i])
    {
        if ( !( (key_word[i] >= 'A' && key_word[i] <= 'Z') || 
            (key_word[i] >= 'a' && key_word[i] <= 'z') ) ) 
        {
            printf("Error\n");
            return 1;
        }
        i++;
    }

    int key_length = strlen(key_word);

    // Get string from user
    string s = GetString();

    // Iterator for key_word
    int j = 0;

    // Holds key for char
    int key;

    // Reset Iterator
    i = 0;

    // Process string in place
    while (s[i])
    {
        // Calculate key for this char
        key = toupper(key_word[j % key_length]) - 'A';

        // Process cipher depending on case
        if ( s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = cipher(key, s[i], 'A');
            // Only increment keyword index if letter
            j++;
        }
        else if ( s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = cipher(key, s[i], 'a');
            j++;
        }

        i++;
    }

    printf("%s\n", s);

    return 0;
}
