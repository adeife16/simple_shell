#include "main.h"

/**
 * errorEnvironment - error message for the "env" command in getEnv.
 * @datash: data structure (lineCounter, tokens)
 * Return: error message.
 */
char *errorEnvironment(ShellData *datash)
{
    int length;
    char *errorMessage;
    char *lineCounter;
    char *message;

    lineCounter = integerToString(datash->lineCounter);
    message = ": Unable to add/remove from environment\n";
    length = _stringLength(datash->arguments[0]) + _stringLength(lineCounter);
    length += _stringLength(datash->tokens[0]) + _stringLength(message) + 4;
    errorMessage = malloc(sizeof(char) * (length + 1));
    if (errorMessage == 0)
    {
      free(errorMessage);
      free(lineCounter);
      return (NULL);
    }

    _stringCopy(errorMessage, datash->arguments[0]);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, lineCounter);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, datash->tokens[0]);
    _stringConcatenate(errorMessage, message);
    _stringConcatenate(errorMessage, "\0");
    free(lineCounter);

    return (errorMessage);
}

/**
 * errorPath126 - error message for "path" and permission denied.
 * @datash: data structure (lineCounter, tokens).
 *
 * Return: The error string.
 */
char *errorPath126(ShellData *datash)
{
    int length;
    char *lineCounter;
    char *errorMessage;

    lineCounter = integerToString(datash->lineCounter);
    length = _stringLength(datash->arguments[0]) + _stringLength(lineCounter);
    length += _stringLength(datash->tokens[0]) + 24;
    errorMessage = malloc(sizeof(char) * (length + 1));
    if (errorMessage == 0)
    {
      free(errorMessage);
      free(lineCounter);
      return (NULL);
    }
    _stringCopy(errorMessage, datash->arguments[0]);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, lineCounter);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, datash->tokens[0]);
    _stringConcatenate(errorMessage, ": Permission denied\n");
    _stringConcatenate(errorMessage, "\0");
    free(lineCounter);
    return (errorMessage);
}
