#include "main.h"

/**
 * showEnvironmentHelp - Display help information for the `env` built-in
 * Return: No return
 */
void showEnvironmentHelp(void)
{
	char *description = "env: env [option] [name=value] [command [args]]\n\t";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, description, _stringLength(description));
}

/**
 * showSetenvHelp - Display help information for the `setenv` built-in
 * Return: No return
 */
void showSetenvHelp(void)
{
	char *description = "setenv: setenv (const char *name, const char *value, int replace)\n\t";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = "Add a new definition to the environment.\n";
	write(STDOUT_FILENO, description, _stringLength(description));
}

/**
 * showUnsetenvHelp - Display help information for the `unsetenv` built-in
 * Return: No return
 */
void showUnsetenvHelp(void)
{
	char *description = "unsetenv: unsetenv (const char *name)\n\t";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = "Remove an entry completely from the environment.\n";
	write(STDOUT_FILENO, description, _stringLength(description));
}

/**
 * showGeneralHelp - Display general help information for the shell
 * Return: No return
 */
void showGeneralHelp(void)
{
	char *description = "^-^ bash, version 1.0(1)-release\n";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = "These commands are defined internally. Type 'help' to see the list.\n";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = "exit: exit [n]\n env: env [option] [name=value] [command [args]]\n";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = "setenv: setenv [variable] [value]\n unsetenv: unsetenv [variable]\n";
	write(STDOUT_FILENO, description, _stringLength(description));
}

/**
 * showExitHelp - Display help information for the `exit` built-in
 * Return: No return
 */
void showExitHelp(void)
{
	char *description = "exit: exit [n]\n Exit shell.\n";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = "Exits the shell with a status of N. If N is omitted, the exit ";
	write(STDOUT_FILENO, description, _stringLength(description));

	description = "status is that of the last command executed.\n";
	write(STDOUT_FILENO, description, _stringLength(description));
}
