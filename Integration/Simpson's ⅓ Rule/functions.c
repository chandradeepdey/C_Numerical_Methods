#include <stdio.h>
#include <math.h>
#include "inputlib.h"
#include "functions.h"

/* asks the user for integration interval, number of
 * subintervals to divide the interval into, and calculates
 * h from that information
 *
 * returns 0 if the input has problems, otherwise returns the value of h
 */
double interval(double * low, double * high, int * n)
{
        double ret;

        puts("Enter the lower limit:");
        *low = get_double();
        puts("Enter the upper limit:");
        *high = get_double();
        puts("Enter the number of intervals (even):");
        *n = get_int();

        if (*low >= *high || *n <= 0 || *n % 2 != 0)
                ret = 0;
        else
                ret = (*high - *low) / *n;

        return ret;
}

/* calculates f(x) = 1 / sqrt(1 + x^2)
 */
double f(double x)
{
        return 1 / sqrt(1 + x * x);
}

/* simpson's 1/3rd rule */
double simpson(double low, double high, double h, int n)
{
        double part1, part2, answer;
        answer = part2 = part1 = 0;

        answer = f(low) + f(high);

        int i = 1;
        double x = low + h;
        while (i <= n - 1) {
                if (i % 2 == 1)
                        part1 += f(x);
                else
                        part2 += f(x);
                x += h;
                i++;
        }
        part1 *= 4;
        part2 *= 2;
        answer += part1 + part2;
        answer *= (h / 3);

        return answer;
}
