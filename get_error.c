#include "main.h"

/**
 * getErrorMessage - Handles different error cases and prints error messages.
 *
 * @datash: Data structure containing arguments and status.
 * @error_code: Error code to determine the type of error.
 * Return: The error code.
 */
int getErrorMessage(ShellData *datash, int error_code)
{
	char *error_message;

	switch (error_code)
	{
	case -1:
		error_message = errorEnvironment(datash);
		break;
    case 2:
		if (_stringCompare("exit", datash->arguments[0]) == 0)
			error_message = errorExitShell(datash);
		else if (_stringCompare("cd", datash->arguments[0]) == 0)
			error_message = errorGetDirectory(datash);
		break;
    case 127:
		error_message = errorCommandNotFound(datash);
		break;
	case 126:
		error_message = errorPath126(datash);
		break;
	default:
		error_message = NULL;
	}

	if (error_message)
	{
		write(STDERR_FILENO, error_message, _stringLength(error_message));
		free(error_message);
	}

	datash->status = error_code;
	return (error_code);
}
