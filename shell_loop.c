#include "main.h"

/**
 * removeComment - Deletes comments from the input.
 *
 * @input: Input string
 * Return: Input without comments
 */
char *removeComment(char *input)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return NULL;
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		input = _reallocate(input, i, up_to + 1);
		input[up_to] = '\0';
	}

	return input;
}

/**
 * shell_loop - Main loop of the shell.
 *
 * @datash: Data relevant (arguments, input, args)
 * Return: No return
 */
void shellLoop(ShellData *datash)
{
	int should_continue, input_eof;
	char *input;

	should_continue = 1;
	while (should_continue == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = readCommandLine(&input_eof);

		if (input_eof != -1)
		{
			input = removeComment(input);
			if (input == NULL)
				continue;

			if (hasSyntaxError(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = replaceVariables(input, datash);
			should_continue = splitCommands(datash, input);
			datash->lineCounter += 1;
			free(input);
		}
		else
		{
			should_continue = 0;
			free(input);
		}
	}
}
