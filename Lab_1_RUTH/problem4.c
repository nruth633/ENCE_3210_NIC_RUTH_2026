#include <stdio.h>
#include <ctype.h>  

int main(void)
{
    //array
    char arr[] = {'R','x','g','B','r','G','b','R','q','G'};
    int n = sizeof(arr) / sizeof(arr[0]);

    int rCount = 0, gCount = 0, bCount = 0;
    int redLED = 0, greenLED = 0, blueLED = 0;   //0 and 1

    //loops thru array
    for (int i = 0; i < n; i++)
    {
        char c = toupper(arr[i]); //using toupper

        if (c == 'R') {
            rCount++;
            redLED = 1;   //for one r
        }
        else if (c == 'G') {
            gCount++;
            greenLED = 1;
        }
        else if (c == 'B') {
            bCount++;
            blueLED = 1;
        }
    }

    // print leds
    printf("Red LED: %s\n", redLED ? "ON" : "OFF");
    printf("Green LED: %s\n", greenLED ? "ON" : "OFF");
    printf("Blue LED: %s\n\n", blueLED ? "ON" : "OFF");

    //count
    printf("R shows up: %d times\n", rCount);
    printf("G shows up: %d times\n", gCount);
    printf("B shows up: %d times\n", bCount);

    return 0;
}