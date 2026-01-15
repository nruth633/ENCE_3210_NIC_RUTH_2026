#include <stdio.h>
#include <limits.h>

#define N 50

//found how to make global array, seems to be the wrong way to do it
int gArr[N + 1] = {
    //asked gpt for 50 random numbers
    3, 7, 2, 7, 1, 9, 4, 9, 0, 5,
    6, 8, 8, 2, 1, 3, 4, 5, 6, 7,
    10, 10, 9, 34, 4, 6, 8, 1, 0, -2,
    11, 11, 3, 5, 7, 50, 2, 4, 6, 8,
    12, 12, 1, 2, 3, 4, 5, 6, 7, 8
};
//static bc it will reset once it finds it
static int second_max_of_first_50(const int a[])
{
    int max1 = INT_MIN;
    int max2 = INT_MIN;
//initilize the two things we want to compare
    for (int i = 0; i < N; i++) {
        int x = a[i];

        if (x > max1) {
            max2 = max1;
            max1 = x;
        } else if (x < max1 && x > max2) {
            // second maximum different than the first
            max2 = x;
        }
    }

    // if there isnt a second we just use the first
    return (max2 == INT_MIN) ? max1 : max2;
}

int main(void)
{
    gArr[N] = second_max_of_first_50(gArr);
//print results
    printf("Second maximum = %d\n", gArr[N]);
    return 0;
}