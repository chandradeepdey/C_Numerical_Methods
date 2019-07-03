#include <stdio.h>
#include <math.h>
#include "inputlib.h"
#include "functions.h"

/* returns 0 if input has no problems, otherwise
 * returns 1
 */
int takeInput(double * low, double * high, double *epsilon)
{
        puts("Enter the lower limit:");
        *low = get_double();
        puts("Enter the upper limit:");
        *high = get_double();
        puts("Enter the desired tolerance:");
        *epsilon = get_double();

        if (*epsilon >= 1 || *epsilon <= 0) {
                fputs("Invalid tolerance, using 0.0001\n", stderr);
                *epsilon = 0.0001;
        }

        if (*low > *high)
                return 1;
        else
                return 0;
}

/* calculates f(x) = x^3 - x^2 + 2
 */
double f(double x)
{
        return x * x * x - x * x + 2;
}

/* bisection method - returns root if found within suitable tolerance
 * and within 20 iterations. otherwise returns nan
 */
double bisection(double low, double high, double epsilon)
{
        int numIter = 20, i = 1;
        double flow = f(low), fmid;
        double mid;
        while (i <= numIter) {
                mid = low + (high - low) / 2; // same as (low + high) / 2 but
                                              // avoids overflow
                fmid = f(mid);
                /* we check for appreciable amount
                 * that is added to mid on every iteration
                 * so (high - low) / 2 is checked against epsilon
                 */
                if (fmid == 0 || (high - low) / 2 < epsilon)
                        return mid;
                else if (flow * fmid > 0) {
                        low = mid;
                        flow = fmid;
                } else
                        high = mid;
                i++;
        }
        // number of iterations exceeded
        return NAN;
}
