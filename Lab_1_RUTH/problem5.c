#include <stdio.h>

//count in array
int countPattern(int data[], int dataSize, int pattern[])
{
    int count = 0;

    for (int i = 0; i <= dataSize - 3; i++)
    {
        int match = 1;

        if (data[i] != pattern[0])
        {
            match = 0;
        }
        if (data[i + 1] != pattern[1])
        {
            match = 0;
        }
        if (data[i + 2] != pattern[2])
        {
            match = 0;
        }

        if (match == 1)
        {
            count = count + 1;
        }
    }

    return count;
}

//sets what led its on
void setLedState(int patternCount, int *greenLed, int *redLed)
{
    if (patternCount > 0)
    {
        *greenLed = 1;
        *redLed = 0;
    }
    else
    {
        *greenLed = 0;
        *redLed = 1;
    }
}

int main(void)
{
    //for main array
    int data[] = {1, 2, 3, 5, 1, 2, 3, 9, 1, 2, 3};
    int dataSize = (int)(sizeof(data) / sizeof(data[0]));

    //p array
    int pattern[3] = {1, 2, 3};

    //for var
    int patternCount = 0;

    //for led
    int greenLed = 0;
    int redLed = 0;

    //counting
    patternCount = countPattern(data, dataSize, pattern);

//i.c.
    setLedState(patternCount, &greenLed, &redLed);


    if (greenLed == 1)
    {
        printf("green led: on\n");
    }
    else
    {
        printf("green led: off\n");
    }

    if (redLed == 1)
    {
        printf("red led: on\n");
    }
    else
    {
        printf("red led: off\n");
    }

    //count
    printf("pattern count: %d\n", patternCount);

    return 0;
}