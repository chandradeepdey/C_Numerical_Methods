/* C_inputlib version 7.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include "inputlib.h"

/* gets a string upto the next newline from a given stream
 *
 * Parameters
 * 1) stream is the stream from which input is taken. if stream
 * is NULL, stdin is used.
 *
 * Return
 * a pointer to the new string. In case there are errors allocating
 * memory, NULL pointer is returned.
 * If the return value is not NULL, it should be freed using free()
 * before exiting the program.
 */
char* get_dynstring(FILE *stream)
{
        if (stream == NULL)
                stream = stdin;

        char *ret, *temp = NULL;
        size_t size = 1;
        ret = malloc(size);

        if (ret != NULL) {
                int ch;
                size_t i = 0;
                while ((ch = getc(stream)), ch != '\n' && ch != EOF) {
                        if (i == size - 1) {
                                if (size <= SIZE_MAX / 2)
                                        temp = realloc(ret, size * 2);
                                if (temp != NULL) {
                                        size *= 2;
                                        ret = temp;
                                        temp = NULL;
                                } else {
                                        free(ret);
                                        ret = NULL;
                                }
                        }
                        if (ret == NULL)
                                break;
                        ret[i] = ch;
                        i++;
                }
                if (ret != NULL)
                        ret[i] = '\0';
        }

        return ret;
}

/* gets an unsigned long long int from a stream by persistently
 * nagging the user to enter the right thing
 *
 * Input
 * 1) stream is the stream from which input is to be taken.
 * stdin is used if stream is NULL
 *
 * Return
 * Returns an unsigned long long int. 0 is returned in case of a read error
 * or EOF
 *
 * Any input after the unsigned int until the next newline character
 * is consumed by this function
 */
unsigned long long int get_unsigned_long_long(FILE *stream)
{
        if (stream == NULL)
                stream = stdin;

        unsigned long long int ret = 0;
        char *input;
        char *endptr;

        char *checksign;

        int valid = 0;
        while (valid == 0 && feof(stream) == 0 && ferror(stream) == 0) {
                if ((input = get_dynstring(stream)) != NULL) {
                        checksign = strchr(input, '-');
                        errno = 0;
                        ret = strtoull(input, &endptr, 0);
                        if (input == endptr
                                        || (checksign != NULL
                                                        && checksign < endptr))
                                fputs("Invalid input\n", stderr);
                        else if (errno == ERANGE)
                                fprintf(stderr, "%s\n", strerror(ERANGE));
                        else
                                valid = 1;
                        free(input);
                }
        }

        return ret;
}

/* gets a double from a stream by persistently
 * nagging the user to enter the right thing
 *
 * Input
 * 1) stream is the stream from which input is to be taken.
 * stdin is used if stream is NULL
 *
 * Return
 * Returns a double. 0 is returned in case of a read error
 * or EOF
 *
 * Any input after the double until the next newline character
 * is consumed by this function
 */
double get_double(FILE *stream)
{
        if (stream == NULL)
                stream = stdin;

        double ret = 0;
        char *input;
        char *endptr;

        int valid = 0;
        while (valid == 0 && feof(stream) == 0 && ferror(stream) == 0) {
                if ((input = get_dynstring(stream)) != NULL) {
                        errno = 0;
                        ret = strtod(input, &endptr);
                        if (input == endptr)
                                fputs("Invalid input\n", stderr);
                        else if (errno == ERANGE)
                                fprintf(stderr, "%s\n", strerror(errno));
                        else
                                valid = 1;
                        free(input);
                }
        }

        return ret;
}
