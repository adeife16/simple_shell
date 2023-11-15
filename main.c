#include "main.h"

/**
 * free_shell_data - Frees data structure.
 *
 * @datash: ShellData structure.
 * Return: No return.
 */
void free_shell_data(ShellData *datash)
{
    unsigned int i;

    for (i = 0; datash->environmentVariables[i]; i++)
    {
      free(datash->environmentVariables[i]);
    }

    free(datash->environmentVariables);
    free(datash->processID);
}

/**
 * initialize_shell_data - Initializes data structure.
 *
 * @datash: ShellData structure.
 * @av: Argument vector.
 * Return: No return.
 */
void initialize_shell_data(ShellData *datash, char **av)
{
    unsigned int i;


    datash->arguments = av;
    datash->input = NULL;
    datash->tokens = NULL;
    datash->status = 0;
    datash->lineCounter = 1;

    for (i = 0; environ[i]; i++)
      ;

    datash->environmentVariables = malloc(sizeof(char *) * (i + 1));

    for (i = 0; environ[i]; i++)
    {
      datash->environmentVariables[i] = _stringDuplicate(environ[i]);
    }

    datash->environmentVariables[i] = NULL;
    datash->processID = integerToString(getpid());
}

/**
 * main - Entry point.
 *
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
    ShellData datash;
    (void)ac;

    signal(SIGINT, handleSIGINT);
    initialize_shell_data(&datash, av);
    shellLoop(&datash);
    free_shell_data(&datash);
    if (datash.status < 0)
      return (255);
    return (datash.status);
}
