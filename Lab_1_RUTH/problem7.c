#include <stdio.h>

#define size 10
//function to print
void printLeds(int redLed, int greenLed, int blueLed)
{
    printf("leds -> r:%d g:%d b:%d\n", redLed, greenLed, blueLed);
}

void doCalc(int a[], int b[], int c[], int op)
{
    //get the operators going
    for (int i = 0; i < size; i++)
    {
        if (op == 1)
        {
            c[i] = a[i] + b[i];
        }
        else if (op == 2)
        {
            c[i] = a[i] - b[i];
        }
        else if (op == 3)
        {
            c[i] = a[i] * b[i];
        }
        else
        {
            c[i] = 0;
        }
    }
}

void printArray(int x[])
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
}

int main(void)
{
    // first 2 arrays
    int arr1[size] = {1,2,3,4,5,6,7,8,9,10};
    int arr2[size] = {10,9,8,7,6,5,4,3,2,1};

    //make third
    int arr3[size] = {0,0,0,0,0,0,0,0,0,0};

    int pressCount = 0;  //button count
    int op = 0;          //changes operand

    int redLed = 0;
    int greenLed = 0;
    int blueLed = 0;

    int choice = 0;

    printf("button 1 = pick operation\n");
    printf("button 2 = run operation on arrays\n");
    printf("type 1 or 2, then enter\n\n");

    while (1)
    {
        scanf("%d", &choice);

        // when button one
        if (choice == 1)
        {
            pressCount = pressCount + 1;

            if (pressCount > 3)
            {
                pressCount = 1;
            }

            op = pressCount;

            //set leds
            redLed = 0;
            greenLed = 0;
            blueLed = 0;

            if (op == 1)
            {
                redLed = 1;   //for adding
                printf("operation: add\n");
            }
            else if (op == 2)
            {
                greenLed = 1; //sub
                printf("operation: sub\n");
            }
            else
            {
                blueLed = 1;  //multi
                printf("operation: mult\n");
            }

            printLeds(redLed, greenLed, blueLed);
        }

        //when button 2
        if (choice == 2)
        {
            if (op == 0)
            {
                printf("pick an operation first (press button 1)\n");
            }
            else
            {
                // when button 2 is pressed
                redLed = 0;
                greenLed = 0;
                blueLed = 0;
                printLeds(redLed, greenLed, blueLed);

                doCalc(arr1, arr2, arr3, op);

                //ending
                redLed = 1;
                greenLed = 1;
                blueLed = 1;
                printLeds(redLed, greenLed, blueLed);

                printf("arr1: ");
                printArray(arr1);
                printf("arr2: ");
                printArray(arr2);
                printf("arr3: ");
                printArray(arr3);
            }
        }
    }

    return 0;
}