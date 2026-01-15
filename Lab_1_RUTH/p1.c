#include <stdio.h>

#define maximum 100 //limits the number being squared for storage

//makes function
long twice_square(int x) //long bc squaring
{
    return 2L * x * x;
}

int main(void)
{
    
    long results[maximum + 1];

    for (int i = 0; i <= maximum; i++)
    {
        results[i] = twice_square(i);
    }
    
    // tests some in console
    printf("results[0]   = %ld\n", results[0]);
    printf("results[10]  = %ld\n", results[10]);
    printf("results[511] = %ld\n", results[100]);

    return 0;
}