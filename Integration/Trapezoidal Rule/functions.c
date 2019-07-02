#include <stdio.h>
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
        puts("Enter the number of intervals:");
        *n = get_int();

        if (*low >= *high || *n <= 0)
                ret = 0;
        else
                ret = (*high - *low) / *n;

        return ret;
}

/* calculates f(x) = 1 / (1 + x^2)
 */
double f(double x)
{
        return 1 / (1 + x * x);
}

/* trapezoidal rule */
double trapezoidal(double low, double high, double h, int n)
{
        double answer = 0;

        double x = low + h;
        int i = 1;
        while (i <= n - 1) {
                answer += f(x);
                x += h;
                i++;
        }
        answer *= 2;

        answer += (f(low) + f(high));
        answer *= (h / 2);

        return answer;
}
