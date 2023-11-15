#include "main.h"

/**
 * swapCharacters - Replaces | and & with non-printed characters.
 *
 * @input: Input string
 * @replace: Type of replacement
 * Return: Modified string
 */
char *swapCharacters(char *input, int replace)
{
	int i;

	if (replace == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return input;
}

/**
 * addNodes - Adds separators and command lines in the lists.
 *
 * @separator_list: Head of separator list
 * @list_line: Head of command lines list
 * @input: Input string
 * Return: No return
 */
void addNodes(list_sep **separator_list, list_line **list_line, char *input)
{
	int i;
	char *line;

	input = swapCharacters(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			addSeparatorNodeEnd(separator_list, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			addSeparatorNodeEnd(separator_list, input[i]);
			i++;
		}
	}

	line = _stringTokenize(input, ";|&");
	do
	{
		line = swapCharacters(line, 1);
		addCommandLineNodeEnd(list_line, line);
		line = _stringTokenize(NULL, ";|&");
	} while (line != NULL);
}

/**
 * moveNext - Moves to the next command line stored.
 *
 * @separator_list: Separator list
 * @list_line: Command line list
 * @datash: Data structure
 * Return: No return
 */
void moveNext(list_sep **separator_list, list_line **line_list, ShellData *datash)
{
	int loop_separator;
	list_sep *current_separator;
	list_line *current_line;

	loop_separator = 1;
	current_separator = *separator_list;
	current_line = *line_list;

	while (current_separator != NULL && loop_separator)
	{
		if (datash->status == 0)
		{
			if (current_separator->separator == '&' || current_separator->separator == ';')
				loop_separator = 0;
			if (current_separator->separator == '|')
				current_line = current_line->next, current_separator = current_separator->next;
		}
		else
		{
			if (current_separator->separator == '|' || current_separator->separator == ';')
				loop_separator = 0;
			if (current_separator->separator == '&')
				current_line = current_line->next, current_separator = current_separator->next;
		}
		if (current_separator != NULL && !loop_separator)
			current_separator = current_separator->next;
	}

	*separator_list = current_separator;
	*line_list = current_line;
}

/**
 * splitCommands - Splits command lines according to
 * the separators ;, | and &, and executes them.
 *
 * @datash: Data structure
 * @input: Input string
 * Return: 0 to exit, 1 to continue
 */
int splitCommands(ShellData *datash, char *input)
{

	list_sep *separator_head, *separator_list;
	list_line *line_head, *list_line;
	int loop;

	separator_head = NULL;
	line_head = NULL;

	addNodes(&separator_head, &line_head, input);

	separator_list = separator_head;
	list_line = line_head;

	while (list_line != NULL)
	{
		datash->input = list_line->line;
		datash->arguments = splitCommandLine(datash->input);
		loop = executeCommandLine(datash);
		free(datash->arguments);

		if (loop == 0)
			break;

		moveNext(&separator_list, &list_line, datash);

		if (list_line != NULL)
			list_line = list_line->next;
	}

	freeSeparatorList(&separator_head);
	freeSeparatorList(&line_head);

	if (loop == 0)
		return 0;
	return 1;
}

/**
 * splitCommandLine - Tokenizes the input string.
 *
 * @input: Input string.
 * Return: String splitted.
 */
char **splitCommandLine(char *input)
{
	size_t bufsize;
	size_t i;
	char **tokens;
	char *token;

	bufsize = TOKEN_BUFFER_SIZE;
	tokens = malloc(sizeof(char *) * (bufsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _stringTokenize(input, TOKEN_DELIMITERS);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bufsize)
		{
			bufsize += TOKEN_BUFFER_SIZE;
			tokens = _reallocateDoublePointer(tokens, i, sizeof(char *) * bufsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _stringTokenize(NULL, TOKEN_DELIMITERS);
		tokens[i] = token;
	}

	return tokens;
}
