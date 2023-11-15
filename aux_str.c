#include "main.h"

/**
 * _stringConcatenate - Concatenate two strings.
 * @destination: Char pointer, the destination of the copied string.
 * @source: Const char pointer, the source of the string.
 * Return: The destination string.
 */
char *_stringConcatenate(char *destination, const char *source)
{
	int i;
	int j;

	for (i = 0; destination[i] != '\0'; i++)
		;

	for (j = 0; source[j] != '\0'; j++)
	{
		destination[i] = source[j];
		i++;
	}

	destination[i] = '\0';
	return (destination);
}

/**
 * _stringCopy - Copies the string pointed to by source.
 * @destination: Type char pointer, the destination of the copied string.
 * @source: Type char pointer, the source of the string.
 * Return: The destination string.
 */
char *_stringCopy(char *destination, char *source)
{

	size_t a;

	for (a = 0; source[a] != '\0'; a++)
	{
		destination[a] = source[a];
	}
	destination[a] = '\0';

	return (destination);
}

/**
 * _stringCompare - Function that compares two strings.
 * @str1: Type string compared.
 * @str2: Type string compared.
 * Return: 0 if strings are equal, positive value if str1 > str2,
 * negative value if str1 < str2.
 */
int _stringCompare(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}

/**
 * custom_strchr - Locates a character in a string.
 * @str: String.
 * @character: Character.
 * Return: The pointer to the first occurrence of the character c,
 * or NULL if the character is not found.
 */
char *custom_strchr(char *str, char character)
{
	unsigned int i = 0;

	for (; *(str + i) != '\0'; i++)
		if (*(str + i) == character)
			return (str + i);

	if (*(str + i) == character)
		return (str + i);

	return (NULL);
}

/**
 * custom_strspn - Gets the length of a prefix substring.
 * @string: Initial segment.
 * @accepted_bytes: Accepted bytes.
 * Return: The number of accepted bytes.
 */
int custom_strspn(char *string, char *accepted_bytes)
{
	int i, j, bool;

	for (i = 0; *(string + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accepted_bytes + j) != '\0'; j++)
		{
			if (*(string + i) == *(accepted_bytes + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
