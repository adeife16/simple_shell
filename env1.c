#include "main.h"

/**
 * compare_env_variable_name - compares environment variable names
 * with the name passed.
 * @env_var: environment variable name
 * @name: name to compare
 *
 * Return: 0 if they are not equal, otherwise the length of the matched part.
 */
int compare_env_variable_name(const char *env_var, const char *name)
{
	int i;

	for (i = 0; env_var[i] != '='; i++)
	{
		if (env_var[i] != name[i])
		{
		  return (0);
		}
	}

	return (i + 1);
}

/**
 * get_environment_variable - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if found, otherwise NULL.
 */
char *_getEnvironmentVariable(char *name, char **_environ)
{
	char *env_var_ptr;
	int i, move;

	env_var_ptr = NULL;
	move = 0;

	for (i = 0; _environ[i]; i++)
	{
		move = compare_env_variable_name(_environ[i], name);

		if (move)
		{
			env_var_ptr = _environ[i];
			break;
		}
	}

	return (env_var_ptr + move);
}

/**
 * print_environment_variables - prints the environment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int handleEnvironmentCommand(ShellData *datash)
{
	int i, j;

	for (i = 0; datash->environmentVariables[i]; i++)
	{
		for (j = 0; datash->environmentVariables[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->environmentVariables[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}

	datash->status = 0;

	return (1);
}
