/**
 * greedy.c
 *
 * Simon Lee
 * silee001@gmail.com
 *
 * Figures out how many coins of change are due based on input
 * Coins limited to 0.25, 0.1, 0.5, 0.01
 *
 */

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Remaining change to account for
    int change;

    // Denominations of coins, must be descending order
    int coins[4] = {25, 10, 5, 1};

    // Number of coins to issue
    int num_coins = 0;

    // Get input from stdio
    do 
    {
        printf("Change: ");
        change = (int) round( (double) GetFloat() * 100.0);
    }
    while (change <= 0);

    // Loop over coin denominations
    for (int i = 0; i < ( sizeof(coins) / sizeof(coins[0]) ); i++)
    { 
        num_coins += change / coins[i];

        // Calculate how much change still needs to be given
        change = change % coins[i];
    }

    printf("%d\n", num_coins);

    return 0;
}
