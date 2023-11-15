#include "main.h"

/**
 * is_colon_directory - checks if ":" is in the current directory.
 * @path: type char pointer representing the path.
 * @index: type int pointer representing the index.
 * Return: 1 if the path is searchable in the current directory, 0 otherwise.
 */
int is_colon_directory(char *path, int *index)
{
	if (path[*index] == ':')
		return 1;

	while (path[*index] != ':' && path[*index])
	{
		*index += 1;
	}

	if (path[*index])
		*index += 1;

	return 0;
}

/**
 * find_executable_path - locates a command in the PATH
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *find_executable_path(char *cmd, char **_environ)
{
	char *path, *path_copy, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getEnvironmentVariable("PATH", _environ);
	if (path)
	{
		path_copy = _stringDuplicate(path);
		len_cmd = _stringLength(cmd);
		token_path = _stringTokenize(path_copy, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_colon_directory(path, &i))
				if (stat(cmd, &st) == 0)
					return cmd;

			len_dir = _stringLength(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_stringCopy(dir, token_path);
			_stringConcatenate(dir, "/");
			_stringConcatenate(dir, cmd);
			_stringConcatenate(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(path_copy);
				return dir;
			}
			free(dir);
			token_path = _stringTokenize(NULL, ":");
		}
		free(path_copy);
		if (stat(cmd, &st) == 0)
			return cmd;
		return NULL;
	}

	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return cmd;

	return NULL;
}

/**
 * is_path_executable - determines if the path is an executable
 *
 * @datash: data structure
 * Return: 0 if it is not an executable, other number if it is
 */
int is_path_executable(ShellData *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->arguments[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return 0;
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return 0;

	if (stat(input + i, &st) == 0)
	{
		return i;
	}

	getErrorMessage(datash, 127);
	return -1;
}

/**
 * check_command_error - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_command_error(char *dir, ShellData *datash)
{
	if (dir == NULL)
	{
		getErrorMessage(datash, 127);
		return 1;
	}

	if (_stringCompare(datash->arguments[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			getErrorMessage(datash, 126);
			free(dir);
			return 1;
		}
		free(dir);
	}
	else
	{
		if (access(datash->arguments[0], X_OK) == -1)
		{
			getErrorMessage(datash, 126);
			return 1;
		}
	}

	return 0;
}

/**
 * execute_command - executes command lines
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 */
int executeCommand(ShellData *datash)
{
	pid_t process_id;
	pid_t wait_process_id;
	int process_state;
	int executable_index;
	char *dir;
	(void) wait_process_id;

	executable_index = is_path_executable(datash);
	if (executable_index == -1)
		return 1;

	if (executable_index == 0)
	{
		dir = find_executable_path(datash->arguments[0], datash->environmentVariables);
		if (check_command_error(dir, datash) == 1)
			return 1;
	}

	process_id = fork();
	if (process_id == 0)
	{
		if (executable_index == 0)
			dir = find_executable_path(datash->arguments[0], datash->environmentVariables);
		else
			dir = datash->arguments[0];

		execve(dir + executable_index, datash->arguments, datash->environmentVariables);
	}
	else if (process_id < 0)
	{
		perror(datash->arguments[0]);
		return 1;
	}
	else
	{
		do {
			wait_process_id = waitpid(process_id, &process_state, WUNTRACED);
		} while (!WIFEXITED(process_state) && !WIFSIGNALED(process_state));
	}

	datash->status = process_state / 256;
	return 1;
}
