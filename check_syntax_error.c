#include "main.h"

/**
 * count_repeated_chars - counts the repetitions of a char
 *
 * @input: input string
 * @index: index
 * Return: repetitions
 */
int count_repeated_chars(char *input, int index)
{
    if (*(input - 1) == *input)
        return count_repeated_chars(input - 1, index + 1);

    return index;
}

/**
 * find_syntax_errors - finds syntax errors
 *
 * @input: input string
 * @index: index
 * @last_char: last char read
 * Return: index of error. 0 when there are no errors
 */
int find_syntax_errors(char *input, int index, char last_char)
{
    int repetitions;

    repetitions = 0;
    if (*input == '\0')
        return 0;

    if (*input == ' ' || *input == '\t')
        return find_syntax_errors(input + 1, index + 1, last_char);

    if (*input == ';')
        if (last_char == '|' || last_char == '&' || last_char == ';')
            return index;

    if (*input == '|')
    {
        if (last_char == ';' || last_char == '&')
            return index;

        if (last_char == '|')
        {
            repetitions = count_repeated_chars(input, 0);
            if (repetitions == 0 || repetitions > 1)
                return index;
        }
    }

    if (*input == '&')
    {
        if (last_char == ';' || last_char == '|')
            return index;

        if (last_char == '&')
        {
            repetitions = count_repeated_chars(input, 0);
            if (repetitions == 0 || repetitions > 1)
                return index;
        }
    }

    return find_syntax_errors(input + 1, index + 1, *input);
}

/**
 * find_first_char_index - finds index of the first char
 *
 * @input: input string
 * @index: index
 * Return: 1 if there is an error. 0 in other case.
 */
int find_first_char_index(char *input, int *index)
{
    for (*index = 0; input[*index]; *index += 1)
    {
        if (input[*index] == ' ' || input[*index] == '\t')
            continue;

        if (input[*index] == ';' || input[*index] == '|' || input[*index] == '&')
            return -1;

        break;
    }

    return 0;
}

/**
 * print_syntax_error_message - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @index: index of the error
 * @is_bool: to control msg error
 * Return: no return
 */
void print_syntax_error_message(ShellData *datash, char *input, int index, int is_bool)
{
    char *error_char, *msg_start, *msg_middle, *msg_end, *error_message, *counter;
    int message_length;

    if (input[index] == ';')
    {
        if (is_bool == 0)
            error_char = (input[index + 1] == ';' ? ";;" : ";");
        else
            error_char = (input[index - 1] == ';' ? ";;" : ";");
    }

    if (input[index] == '|')
        error_char = (input[index + 1] == '|' ? "||" : "|");

    if (input[index] == '&')
        error_char = (input[index + 1] == '&' ? "&&" : "&");

    msg_start = ": Syntax error: \"";
    msg_middle = "\" unexpected\n";
    counter = integerToString(datash->lineCounter);
    message_length = _stringLength(datash->arguments[0]) + _stringLength(counter);
    message_length += _stringLength(error_char) + _stringLength(msg_start) + _stringLength(msg_middle) + 2;

    error_message = malloc(sizeof(char) * (message_length + 1));
    if (error_message == 0)
    {
        free(counter);
        return;
    }
    _stringCopy(error_message, datash->arguments[0]);
    _stringConcatenate(error_message, counter);
    _stringConcatenate(error_message, ": ");
    _stringConcatenate(error_message, msg_start);
    _stringConcatenate(error_message, error_char);
    _stringConcatenate(error_message, msg_middle);
    _stringConcatenate(error_message, "\0");

    write(STDERR_FILENO, error_message, message_length);
    free(error_message);
    free(counter);
}

/**
 * hasSyntaxError - intermediate function to find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int hasSyntaxError(ShellData *datash, char *input)
{
    int begin_index = 0;
    int first_char_error = 0;
    int syntax_error_index = 0;

    first_char_error = find_first_char_index(input, &begin_index);
    if (first_char_error == -1)
    {
        print_syntax_error_message(datash, input, begin_index, 0);
        return 1;
    }

    syntax_error_index = find_syntax_errors(input + begin_index, 0, *(input + begin_index));
    if (syntax_error_index != 0)
    {
        print_syntax_error_message(datash, input, begin_index + syntax_error_index, 1);
        return 1;
    }

    return 0;
}
