#include "main.h"

/**
 * exitShell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exitShell(ShellData *datash)
{
	unsigned int exit_status;
	int is_valid_digit;
	int arg_length;
	int exceeds_int_max;

	if (datash->arguments[1] != NULL)
	{
		exit_status = stringToInteger(datash->arguments[1]);
		is_valid_digit = isDigit(datash->arguments[1]);
		arg_length = _stringLength(datash->arguments[1]);
		exceeds_int_max = exit_status > (unsigned int)INT_MAX;

		if (!is_valid_digit || arg_length > 10 || exceeds_int_max)
		{
			getErrorMessage(datash, 2);
			datash->status = 2;
			return (1);
		}

		datash->status = (exit_status % 256);
	}

	return (0);
}
