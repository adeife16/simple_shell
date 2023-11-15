#include "main.h"

/**
 * changeDirectoryToDot - changes to the parent directory
 *
 * @datash: Data structure containing relevant information (environ)
 *
 * Return: No return
 */
void changeDirectoryToDot(ShellData *datash)
{
	char current_path[PATH_MAX];
	char *copied_pwd, *directory, *copied_stringTokenize_pwd;

	getcwd(current_path, sizeof(current_path));
	copied_pwd = _stringDuplicate(current_path);
	setEnvironmentVariable("OLDPWD", copied_pwd, datash);
	directory = datash->arguments[1];

	if (_stringCompare(".", directory) == 0)
	{
		setEnvironmentVariable("PWD", copied_pwd, datash);
		free(copied_pwd);
		return;
	}

	if (_stringCompare("/", copied_pwd) == 0)
	{
		free(copied_pwd);
		return;
	}

	copied_stringTokenize_pwd = copied_pwd;
	reverseString(copied_stringTokenize_pwd);
	copied_stringTokenize_pwd = _stringTokenize(copied_stringTokenize_pwd, "/");

	if (copied_stringTokenize_pwd != NULL)
	{
		copied_stringTokenize_pwd = _stringTokenize(NULL, "\0");

		if (copied_stringTokenize_pwd != NULL)
			reverseString(copied_stringTokenize_pwd);
	}

	if (copied_stringTokenize_pwd != NULL)
	{
		chdir(copied_stringTokenize_pwd);
		setEnvironmentVariable("PWD", copied_stringTokenize_pwd, datash);
	}
	else
	{
		chdir("/");
		setEnvironmentVariable("PWD", "/", datash);
	}

	datash->status = 0;
	free(copied_pwd);
}

/**
 * changeDirectory - changes to a directory given by the user
 *
 * @datash: Data structure containing relevant information (directories)
 * Return: No return
 */
void changeDirectory(ShellData *datash)
{
	char current_path[PATH_MAX];
	char *directory, *copied_pwd, *copied_dir;

	getcwd(current_path, sizeof(current_path));
	directory = datash->arguments[1];

	if (chdir(directory) == -1)
	{
		getErrorMessage(datash, 2);
		return;
	}

	copied_pwd = _stringDuplicate(current_path);
	setEnvironmentVariable("OLDPWD", copied_pwd, datash);

	copied_dir = _stringDuplicate(directory);
	setEnvironmentVariable("PWD", copied_dir, datash);

	free(copied_pwd);
	free(copied_dir);

	datash->status = 0;

	chdir(directory);
}

/**
 * changeDirectoryToPrevious - changes to the previous directory
 *
 * @datash: Data structure containing relevant information (environ)
 * Return: No return
 */
void changeDirectoryToPrevious(ShellData *datash)
{
	char current_path[PATH_MAX];
	char *previous_pwd, *previous_oldpwd, *copied_pwd, *copied_oldpwd;

	getcwd(current_path, sizeof(current_path));
	copied_pwd = _stringDuplicate(current_path);

	previous_oldpwd = _getEnvironmentVariable("OLDPWD", datash->environmentVariables);

	if (previous_oldpwd == NULL)
		copied_oldpwd = copied_pwd;
	else
		copied_oldpwd = _stringDuplicate(previous_oldpwd);

	setEnvironmentVariable("OLDPWD", copied_pwd, datash);

	if (chdir(copied_oldpwd) == -1)
		setEnvironmentVariable("PWD", copied_pwd, datash);
	else
		setEnvironmentVariable("PWD", copied_oldpwd, datash);

	previous_pwd = _getEnvironmentVariable("PWD", datash->environmentVariables);

	write(STDOUT_FILENO, previous_pwd, _stringLength(previous_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(copied_pwd);
	if (previous_oldpwd)
		free(copied_oldpwd);

	datash->status = 0;

	chdir(previous_pwd);
}

/**
 * changeDirectoryToHome - changes to home directory
 *
 * @datash: Data structure containing relevant information (environ)
 * Return: No return
 */
void changeDirectoryToHome(ShellData *datash)
{
	char *previous_pwd, *home_directory;
	char current_path[PATH_MAX];

	getcwd(current_path, sizeof(current_path));
	previous_pwd = _stringDuplicate(current_path);

	home_directory = _getEnvironmentVariable("HOME", datash->environmentVariables);

	if (home_directory == NULL)
	{
		setEnvironmentVariable("OLDPWD", previous_pwd, datash);
		free(previous_pwd);
		return;
	}

	if (chdir(home_directory) == -1)
	{
		getErrorMessage(datash, 2);
		free(previous_pwd);
		return;
	}

	setEnvironmentVariable("OLDPWD", previous_pwd, datash);
	setEnvironmentVariable("PWD", home_directory, datash);
	free(previous_pwd);
	datash->status = 0;
}
