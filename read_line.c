#include "main.h"

/**
 * read_line - Reads the input string.
 *
 * @getline_result: Return value of the getline function.
 * Return: Input string.
 */
char *readCommandLine(int *getline_result)
{
    char *input = NULL;
    size_t buffer_size = 0;

    *getline_result = getline(&input, &buffer_size, stdin);

    return (input);
}
