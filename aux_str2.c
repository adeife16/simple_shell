#include "main.h"

/**
 * custom_stringDuplicate - Duplicates a string in the heap memory.
 * @s: Type char pointer representing the string.
 * Return: Duplicated string.
 */
char *_stringDuplicate( char *s)
{
	char *new;
	size_t len;

	len = _stringLength(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memoryCopy(new, s, len + 1);
	return (new);
}

/**
 * _stringLength - Returns the length of a string.
 * @s: Type char pointer representing the string.
 * Return: Length of the string.
 */
int _stringLength(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * custom_cmp_chars - Compare characters of strings.
 * @str: Input string.
 * @delim: Delimiter.
 *
 * Return: 1 if characters are equal, 0 if not.
 */
int custom_cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _stringTokenize - Splits a string by some delimiter.
 * @str: Input string.
 * @delim: Delimiter.
 *
 * Return: String split by the delimiter.
 */
char *_stringTokenize(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (custom_cmp_chars(str, delim))
			return (NULL);
		splitted = str; /* Store first address */
		i = _stringLength(str);
		str_end = &str[i]; /* Store last address */
	}
	str_start = splitted;
	if (str_start == str_end) /* Reaching the end */
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/* Breaking loop finding the next token */
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/* Replacing delimiter for null char */
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /* Str != Delim */
			bool = 1;
	}
	if (bool == 0) /* Str == Delim */
		return (NULL);
	return (str_start);
}

/**
 * isDigit - Defines if the string passed is a number.
 *
 * @s: Input string.
 * Return: 1 if the string is a number, 0 otherwise.
 */
int isDigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
