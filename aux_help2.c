#include "main.h"

/**
 * showHelp - Display help information for the `help` built-in
 * Return: No return
 */
void showHelp(void)
{
	char *description = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, description, _stringLength(description));
	description = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, description, _stringLength(description));
	description = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, description, _stringLength(description));
}

/**
 * showAliasHelp - Display help information for the `alias` built-in
 * Return: No return
 */
void showAliasHelp(void)
{
	char *description = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, description, _stringLength(description));
	description = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, description, _stringLength(description));
}

/**
 * showChangeDirectoryHelp - Display help information for the `cd` built-in
 * Return: No return
 */
void showChangeDirectoryHelp(void)
{
	char *description = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, description, _stringLength(description));
	description = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, description, _stringLength(description));
}
