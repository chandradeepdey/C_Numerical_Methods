/* evaluate integral from 0 to 1 of dx/(1 + x^2)
 * using trapezoidal rule. Take 6 intervals.
 */

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[])
{
        puts("This program evaluates integral dx/(1 + x^2)");
        puts("in a given interval using the trapezoidal rule");

        double low, high, h;
        int n;

        while (!feof(stdin) && !(h = interval(&low, &high, &n)))
                puts("Invalid input, please try again.");

        if (!feof(stdin))
                printf("The answer is %f\n", trapezoidal(low, high, h, n));

        else
                fputs("EOF reached before matching all inputs.\n", stderr);

        return EXIT_SUCCESS;
}
