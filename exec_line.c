#include "main.h"

/**
 * executeCommandLine - finds built-ins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int executeCommandLine(ShellData *datash)
{
	int (*builtin_function)(ShellData *datash);

	if (datash->arguments[0] == NULL)
		return (1);

	builtin_function = getBuiltinCommand(datash->arguments[0]);

	if (builtin_function != NULL)
		return (builtin_function(datash));

	return (executeCommand(datash));
}
