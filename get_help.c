#include "main.h"

/**
 * getHelp - function that retrieves help messages according builtin
 * @datash: data structure (args and input)
 * Return: Return 0
*/
int getHelp(ShellData *datash)
{

	if (datash->arguments[1] == 0)
		showGeneralHelp();
	else if (_stringCompare(datash->arguments[1], "setenv") == 0)
		showSetenvHelp();
	else if (_stringCompare(datash->arguments[1], "env") == 0)
		showEnvironmentHelp();
	else if (_stringCompare(datash->arguments[1], "unsetenv") == 0)
		showUnsetenvHelp();
	else if (_stringCompare(datash->arguments[1], "help") == 0)
		showHelp();
	else if (_stringCompare(datash->arguments[1], "exit") == 0)
		showExitHelp();
	else if (_stringCompare(datash->arguments[1], "cd") == 0)
		showChangeDirectoryHelp();
	else if (_stringCompare(datash->arguments[1], "alias") == 0)
		showAliasHelp();
	else
		write(STDERR_FILENO, datash->arguments[0],
		      _stringLength(datash->arguments[0]));

	datash->status = 0;
	return (1);
}
