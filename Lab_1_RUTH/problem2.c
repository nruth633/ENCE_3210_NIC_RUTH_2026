#include <stdio.h>
#include <math.h>

#define DEG_MAX 360
#define PI 3.14

void fill_cos_array(double arr[], int max_deg) //tried to use array tool instead of pointer
{
    for (int deg = 0; deg <= max_deg; deg++) {
        double rad = deg * (PI / 180.0); //dg to rads
        arr[deg] = cos(rad);
    }
}

int main(void)// prints out tests from 90 deg
{
    double cos_vals[DEG_MAX + 1];
    fill_cos_array(cos_vals, DEG_MAX);

    printf("cos(60) = %.6f\n", cos_vals[90]);
    printf("cos(60) = %.6f\n", cos_vals[180]);
    printf("cos(60) = %.6f\n", cos_vals[270]);
    printf("cos(60) = %.6f\n", cos_vals[360]);

    return 0;
}