#include "main.h"

/**
 * checkEnvironmentVariables - Checks if the typed variable is an environment variable.
 *
 * @head: Head of linked list
 * @input: Input string
 * @data: Data structure
 * Return: No return
 */
void checkEnvironmentVariables(var_r **head, char *input, ShellData *data)
{
	int row, chr, j, value_length;
	char **environment;

	environment = data->environmentVariables;
	for (row = 0; environment[row]; row++)
	{
		for (j = 1, chr = 0; environment[row][chr]; chr++)
		{
			if (environment[row][chr] == '=')
			{
				value_length = _stringLength(environment[row] + chr + 1);
				addRVarNode(head, j, environment[row] + chr + 1, value_length);
				return;
			}

			if (input[j] == environment[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == '\t' || input[j] == ';' || input[j] == '\n')
			break;
	}

	addRVarNode(head, j, NULL, 0);
}

/**
 * check_special_variables - Checks if the typed variable is $$ or $?
 *
 * @head: Head of the linked list
 * @input: Input string
 * @status: Last status of the Shell
 * @data: Data structure
 * Return: No return
 */
int checkVariables(var_r **head, char *input, char *status, ShellData *data)
{
	int i, last_status_length, pid_length;

	last_status_length = _stringLength(status);
	pid_length = _stringLength(data->processID);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				addRVarNode(head, 2, status, last_status_length), i++;
			else if (input[i + 1] == '$')
				addRVarNode(head, 2, data->processID, pid_length), i++;
			else if (input[i + 1] == '\n' || input[i + 1] == '\0' || input[i + 1] == ' ' ||
				 input[i + 1] == '\t' || input[i + 1] == ';')
				addRVarNode(head, 0, NULL, 0);
			else
				checkEnvironmentVariables(head, input + i, data);
		}
	}

	return (i);
}

/**
 * replace_input_variables - Replaces string into variables.
 *
 * @head: Head of the linked list
 * @input: Input string
 * @new_input: New input string (replaced)
 * @new_length: New length
 * Return: Replaced string
 */
char *replaceInput(var_r **head, char *input, char *new_input, int new_length)
{
	var_r *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < new_length; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->var_len) && !(index->val_len))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (index->var_len && !(index->val_len))
			{
				for (k = 0; k < index->var_len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->val_len; k++)
				{
					new_input[i] = index->value[k];
					i++;
				}
				j += (index->var_len);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * replace_variables - Calls functions to replace string into vars.
 *
 * @input: Input string
 * @datash: Data structure
 * Return: Replaced string
 */
char *replaceVariables(char *input, ShellData *datash)
{
	var_r *head, *index;
	char *status, *new_input;
	int original_length, new_length;

	status = integerToString(datash->status);
	head = NULL;

	original_length = checkVariables(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	new_length = 0;

	while (index != NULL)
	{
		new_length += (index->val_len - index->var_len);
		index = index->next;
	}

	new_length += original_length;

	new_input = malloc(sizeof(char) * (new_length + 1));
	new_input[new_length] = '\0';

	new_input = replaceInput(&head, input, new_input, new_length);

	free(input);
	free(status);
	freeRVarList(&head);

	return (new_input);
}
