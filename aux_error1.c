#include "main.h"

/**
 * concatenateForChangeDirectory - function that concatenates the error message for the cd command
 *
 * @datash: data structure (directory)
 * @message: message to print
 * @errorMessage: output error message
 * @lineCounter: line counter
 * Return: error message
 */
char *concatenateForChangeDirectory(ShellData *datash, char *message, char *errorMessage, char *lineCounter) {
    char *illegalFlag;

    _stringCopy(errorMessage, datash->arguments[0]);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, lineCounter);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, datash->tokens[0]);
    _stringConcatenate(errorMessage, message);
    if (datash->tokens[1][0] == '-') {
        illegalFlag = malloc(3);
        illegalFlag[0] = '-';
        illegalFlag[1] = datash->tokens[1][1];
        illegalFlag[2] = '\0';
        _stringConcatenate(errorMessage, illegalFlag);
        free(illegalFlag);
    } else {
        _stringConcatenate(errorMessage, datash->tokens[1]);
    }

    _stringConcatenate(errorMessage, "\n");
    _stringConcatenate(errorMessage, "\0");
    return errorMessage;
}

/**
 * errorGetDirectory - error message for the cd command in getCd
 * @datash: data structure (directory)
 * Return: Error message
 */
char *errorGetDirectory(ShellData *datash) {
    int length, flagLength;
    char *errorMessage, *lineCounter, *message;

    lineCounter = integerToString(datash->lineCounter);
    if (datash->tokens[1][0] == '-') {
        message = ": Illegal option ";
        flagLength = 2;
    } else {
        message = ": can't cd to ";
        flagLength = _stringLength(datash->tokens[1]);
    }

    length = _stringLength(datash->arguments[0]) + _stringLength(datash->tokens[0]);
    length += _stringLength(lineCounter) + _stringLength(message) + flagLength + 5;
    errorMessage = malloc(sizeof(char) * (length + 1));

    if (errorMessage == NULL) {
        free(lineCounter);
        return NULL;
    }

    errorMessage = concatenateForChangeDirectory(datash, message, errorMessage, lineCounter);

    free(lineCounter);

    return errorMessage;
}

/**
 * errorCommandNotFound - generic error message for "command not found"
 * @datash: data structure (lineCounter, tokens)
 * Return: Error message
 */
char *errorCommandNotFound(ShellData *datash) {
    int length;
    char *errorMessage;
    char *lineCounter;

    lineCounter = integerToString(datash->lineCounter);
    length = _stringLength(datash->arguments[0]) + _stringLength(lineCounter);
    length += _stringLength(datash->tokens[0]) + 16;
    errorMessage = malloc(sizeof(char) * (length + 1));
    if (errorMessage == NULL) {
        free(lineCounter);
        return NULL;
    }
    _stringCopy(errorMessage, datash->arguments[0]);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, lineCounter);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, datash->tokens[0]);
    _stringConcatenate(errorMessage, ": not found\n");
    _stringConcatenate(errorMessage, "\0");
    free(lineCounter);
    return errorMessage;
}

/**
 * errorExitShell - generic error message for "exit" in getExit
 * @datash: data structure (lineCounter, tokens)
 * Return: Error message
 */
char *errorExitShell(ShellData *datash) {
    int length;
    char *errorMessage;
    char *lineCounter;

    lineCounter = integerToString(datash->lineCounter);
    length = _stringLength(datash->arguments[0]) + _stringLength(lineCounter);
    length += _stringLength(datash->tokens[0]) + _stringLength(datash->tokens[1]) + 23;
    errorMessage = malloc(sizeof(char) * (length + 1));
    if (errorMessage == NULL) {
        free(lineCounter);
        return NULL;
    }
    _stringCopy(errorMessage, datash->arguments[0]);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, lineCounter);
    _stringConcatenate(errorMessage, ": ");
    _stringConcatenate(errorMessage, datash->tokens[0]);
    _stringConcatenate(errorMessage, ": Illegal number: ");
    _stringConcatenate(errorMessage, datash->tokens[1]);
    _stringConcatenate(errorMessage, "\n\0");
    free(lineCounter);
    return errorMessage;
}
