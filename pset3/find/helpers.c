/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 * Linear search implementation. 
 */
bool linearsearch(int value, int values[], int n)
{
    int i = 0;
    while(values[i])
    {
        // only require one match
        if (value == values[i])
        {
            return true;
        }
        i++;
    }
    return false;
}

bool binarysearch(int value, int values[], int lower, int upper)
{
    if (upper - lower > 1)
    {
        int mid = (int) (lower + upper) / 2;

        if (value <= values[mid])
        {
            return binarysearch(value, values, lower, mid);
        }
        else
        {
            return binarysearch(value, values, mid, upper);
        }
    }
    else
    {
        if (value == values[lower] || value == values[upper])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/**
 * Returns true if value is in array of n values, else false.
 * Binary search implementation. 
 *
 */
bool search(int value, int values[], int n)
{
    return binarysearch(value, values, 0, n);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

    for(int i = 0; i < n - 1; i++)
    {
        int min_val_index = i;
        int min_val;
        int j = i + 1;
        while(values[j])
        {
            if (values[j] < values[min_val_index])
            {
                min_val_index = j;
            }
            j++;
        }
        // Swap places
        min_val = values[min_val_index];
        values[min_val_index] = values[i];
        values[i] = min_val;
    }

    
    for(int i = 0; i < n ; i++)
    {
        printf("%i\n", values[i]);
    }
    return;
}
