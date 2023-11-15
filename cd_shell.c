#include "main.h"

/**
 * change_directory - changes the current directory based on input arguments
 *
 * @datash: Data structure containing relevant information
 * Return: 1 on success
 */
int changeDirectoryCommand(ShellData *datash)
{
	char *target_directory;
	int is_home, is_home_short, is_double_dash;

	target_directory = datash->arguments[1];

	if (target_directory != NULL)
	{
		is_home = _stringCompare("$HOME", target_directory);
		is_home_short = _stringCompare("~", target_directory);
		is_double_dash = _stringCompare("--", target_directory);
	}

	if (target_directory == NULL || !is_home || !is_home_short || !is_double_dash)
	{
		changeDirectoryToHome(datash);
		return (1);
	}

	if (_stringCompare("-", target_directory) == 0)
	{
		changeDirectoryToPrevious(datash);
		return (1);
	}

	if (_stringCompare(".", target_directory) == 0 || _stringCompare("..", target_directory) == 0)
	{
		changeDirectoryToDot(datash);
		return (1);
	}

	changeDirectory(datash);

	return (1);
}
