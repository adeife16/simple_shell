#include "main.h"

/**
 * getBuiltinCommand - Finds the builtin command corresponding to the given command.
 *
 * @command: The command for which to retrieve the builtin function.
 * Return: Function pointer to the builtin command, or NULL if not found.
 */
int (*getBuiltinCommand(char *command))(ShellData *)
{
    BuiltinCommand builtins[] = {
        {"env", handleEnvironmentCommand},
        {"exit", exitShell},
        {"setenv", setEnvironment},
        {"unsetenv", unsetEnvironmentVariable},
        {"cd", changeDirectoryCommand},
        {"help", getHelp},
        {NULL, NULL}
    };

    int index;

    for (index = 0; builtins[index].name; index++)
    {
        if (_stringCompare(builtins[index].name, command) == 0)
            break;
    }

    return builtins[index].function;
}
