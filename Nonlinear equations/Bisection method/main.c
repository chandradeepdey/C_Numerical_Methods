/* find a real root of x^3 - x^2 + 2 between
 * -200 and 300, use tolerance = 0.01
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

int main(int argc, char *argv[])
{
        fputs("This program finds a real root of the equation ", stdout);
        puts("x^3 - x^2 + 2");
        puts("in a given interval using the method of bisection");

        double low, high, epsilon;
        double root;

        while (!feof(stdin) && takeInput(&low, &high, &epsilon))
                puts("Invalid input, please try again.");

        if (!feof(stdin)) {
                root = bisection(low, high, epsilon);
                if (isnan(root)) {
                        fputs("Could not find a root.\n", stderr);
                        exit(EXIT_FAILURE);
                } else
                        printf("The root lies at %f\n", root);
        } else {
                fputs("EOF reached before matching all inputs.\n", stderr);
                exit(EXIT_FAILURE);
        }

        return EXIT_SUCCESS;
}
