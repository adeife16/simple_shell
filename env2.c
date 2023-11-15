#include "main.h"

/**
 * copyInformation - copies information to create
 * a new environment variable or alias
 * @name: name (environment variable or alias)
 * @value: value (environment variable or alias)
 *
 * Return: new environment variable or alias.
 */
char *copyInformation(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _stringLength(name);
	len_value = _stringLength(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_stringCopy(new, name);
	_stringConcatenate(new, "=");
	_stringConcatenate(new, value);
	_stringConcatenate(new, "\0");

	return (new);
}

/**
 * setEnvironmentVariable - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void setEnvironmentVariable(char *name, char *value, ShellData *datash)
{
	int i;
	char *current_environment, *current_name;

	for (i = 0; datash->environmentVariables[i]; i++)
	{
		current_environment = _stringDuplicate(datash->environmentVariables[i]);
		current_name = _stringTokenize(current_environment, "=");
		if (_stringCompare(current_name, name) == 0)
		{
			free(datash->environmentVariables[i]);
			datash->environmentVariables[i] = copyInformation(current_name, value);
			free(current_environment);
			return;
		}
		free(current_environment);
	}

	datash->environmentVariables = _reallocateDoublePointer(datash->environmentVariables, i, sizeof(char *) * (i + 2));
	datash->environmentVariables[i] = copyInformation(name, value);
	datash->environmentVariables[i + 1] = NULL;
}

/**
 * setEnvironment - handles the setenv command
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int setEnvironment(ShellData *datash)
{

	if (datash->arguments[1] == NULL || datash->arguments[2] == NULL)
	{
		getErrorMessage(datash, -1);
		return (1);
	}

	setEnvironmentVariable(datash->arguments[1], datash->arguments[2], datash);

	return (1);
}

/**
 * unsetEnvironmentVariable - deletes an environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int unsetEnvironmentVariable(ShellData *datash)
{
	char **realloc_environ;
	char *current_environment, *current_name;
	int i, j, index_to_remove;

	if (datash->arguments[1] == NULL)
	{
		getErrorMessage(datash, -1);
		return (1);
	}

	index_to_remove = -1;
	for (i = 0; datash->environmentVariables[i]; i++)
	{
		current_environment = _stringDuplicate(datash->environmentVariables[i]);
		current_name = _stringTokenize(current_environment, "=");
		if (_stringCompare(current_name, datash->arguments[1]) == 0)
		{
			index_to_remove = i;
		}
		free(current_environment);
	}

	if (index_to_remove == -1)
	{
		getErrorMessage(datash, -1);
		return (1);
	}

	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->environmentVariables[i]; i++)
	{
		if (i != index_to_remove)
		{
			realloc_environ[j] = datash->environmentVariables[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->environmentVariables[index_to_remove]);
	free(datash->environmentVariables);
	datash->environmentVariables = realloc_environ;
	return (1);
}
