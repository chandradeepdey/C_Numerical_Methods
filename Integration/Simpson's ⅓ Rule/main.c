/* evaluate integral from 1 to 2 of dx/sqrt(1 + x^2)
 * using simpson's 1/3rd rule. Take 18 intervals.
 */

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[])
{
        puts("This program evaluates the integral dx/sqrt(1 + x^2)");
        puts("in a given interval using Simpson's 1/3rd rule");

        double low, high, h;
        int n;

        while (!feof(stdin) && !(h = interval(&low, &high, &n)))
                puts("Invalid input, please try again.");

        if (!feof(stdin))
                printf("The answer is %f\n", simpson(low, high, h, n));

        else
                fputs("EOF reached before matching all inputs.\n", stderr);

        return EXIT_SUCCESS;
}
