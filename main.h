#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 128
#define TOKEN_DELIMITERS " \t\r\n\a"

extern char **environ;

typedef struct ShellData
{
    char **arguments;
    char *input;
    char **tokens;
    int status;
    int lineCounter;
    char **environmentVariables;
    char *processID;
} ShellData;

typedef struct list_sep
{
    char separator;
    struct list_sep *next;
} list_sep;

typedef struct list_line
{
    char *line;
    struct list_line *next;
} list_line;

typedef struct var_r
{
    int var_len;
    char *value;
    int val_len;
    struct var_r *next;
} var_r;

typedef struct BuiltinCommand
{
    char *name;
    int (*function)(ShellData *data);
} BuiltinCommand;

list_sep *addSeparatorNodeEnd(list_sep **head, char sep);
void freeSeparatorList(list_sep **head);
list_line *addCommandLineNodeEnd(list_line **head, char *line);
void freeLineList(list_line **head);

var_r *addRVarNode(var_r **head, int variableLength, char *variable, int valueLength);
void freeRVarList(var_r **head);

char *_stringConcatenate(char *destination, const char *source);
char *_stringCopy(char *destination, char *source);
int _stringCompare(char *str1, char *str2);
char *_stringFindCharacter(char *str, char character);
int _stringSpan(char *str, char *accept);

void _memoryCopy(void *newPointer, const void *pointer, unsigned int size);
void *_reallocate(void *pointer, unsigned int oldSize, unsigned int newSize);
char **_reallocateDoublePointer(char **pointer, unsigned int oldSize, unsigned int newSize);

char *_stringDuplicate(char *str);
int _stringLength(const char *str);
int compareCharacters(char str[], const char *delimiters);
char *_stringTokenize(char str[], const char *delimiters);
int isDigit(const char *str);

void reverseString(char *str);

int hasRepeatedCharacter(char *input, int index);
int hasSyntaxErrorInSeparator(char *input, int index, char lastSeparator);
int findFirstCharacter(char *input, int *index);
void printSyntaxError(ShellData *data, char *input, int index, int isError);
int hasSyntaxError(ShellData *data, char *input);

char *removeComment(char *input);
void shellLoop(ShellData *data);

char *readCommandLine(int *isEndOfFile);

char *swapCharacters(char *input, int shouldSwap);
void addNodes(list_sep **list_sep, list_line **list_line, char *input);
void moveNext(list_sep **list_sep, list_line **list_line, ShellData *data);
int splitCommands(ShellData *data, char *input);
char **splitCommandLine(char *input);

void checkEnvironmentVariables(var_r **head, char *input, ShellData *data);
int checkVariables(var_r **head, char *input, char *substring, ShellData *data);
char *replaceInput(var_r **head, char *input, char *newInput, int newLength);
char *replaceVariables(char *input, ShellData *data);

void readCommandLineFromFile(char **linePointer, size_t *size, char *buffer, size_t bufferSize);
ssize_t getCommandLine(char **linePointer, size_t *size, FILE *stream);

int executeCommandLine(ShellData *data);

int isCurrentDirectory(const char *path, int *index);
char *findExecutableCommand(char *command, char **environmentVariables);
int isExecutable(ShellData *data);
int checkCommandError(const char *directory, ShellData *data);
int executeCommand(ShellData *data);

char *_getEnvironmentVariable(char *name, char **environmentVariables);
int handleEnvironmentCommand(ShellData *data);

char *copyInformation(char *name, char *value);
void setEnvironmentVariable(char *name, char *value, ShellData *data);
int setEnvironment(ShellData *data);
int unsetEnvironmentVariable(ShellData *data);

void changeDirectoryToDot(ShellData *data);
void changeDirectory(ShellData *data);
void changeDirectoryToPrevious(ShellData *data);
void changeDirectoryToHome(ShellData *data);

int changeDirectoryCommand(ShellData *data);

int (*getBuiltinCommand(char *command))(ShellData *data);

int exitShell(ShellData *data);

int getLength(int number);
char *integerToString(int number);
int stringToInteger(char *str);

char *concatenateForChangeDirectory(ShellData *data, char *directory, char *message1, char *message2);
char *errorGetDirectory(ShellData *data);
char *errorCommandNotFound(ShellData *data);
char *errorExitShell(ShellData *data);

char *errorGetAlias(char **arguments);
char *errorEnvironment(ShellData *data);
char *errorSyntax(char **arguments);
char *errorPermission(char **arguments);
char *errorPath126(ShellData *data);

int getErrorMessage(ShellData *data, int evaluation);

void handleSIGINT(int signal);

void showEnvironmentHelp(void);
void showSetenvHelp(void);
void showUnsetenvHelp(void);
void showGeneralHelp(void);
void showExitHelp(void);

void showHelp(void);
void showAliasHelp(void);
void showChangeDirectoryHelp(void);

int getHelp(ShellData *data);

#endif
