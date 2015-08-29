/**
 * initials.c
 *
 * Simon Lee
 * silee001@gmail.com
 *
 * Prints initials in caps given a full name
 *
 */

#include <stdio.h>
#include <ctype.h>

#include <cs50.h>

int main(void)
{
    // Iterator
    int i=0;

    // Get name from user
    string name = GetString();

    // Iterate over every char in string
    while (name[i])
    {
        // Second condition possible as will never be tested if i == 0
        if ( i == 0 || name[i - 1] == ' ' )
        {
            // Print capitalised letter to stdio
            printf("%c",toupper(name[i]));
        }
        i++;
    }

    printf("\n");


    return 0;
}
