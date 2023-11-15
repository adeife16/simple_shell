#include "main.h"

/**
 * getNumberLength - Get the length of a number.
 * @num: Type int number.
 * Return: Length of a number.
 */
int getNumberLength(int num)
{
	unsigned int num1;
	int length = 1;

	if (num < 0)
	{
		length++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		length++;
		num1 = num1 / 10;
	}

	return (length);
}

/**
 * intToString - Converts an integer to a string.
 * @num: Type int number.
 * Return: String.
 */
char *integerToString(int num)
{
	unsigned int num1;
	int length = getNumberLength(num);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;
	do {
		*(buffer + length) = (num1 % 10) + '0';
		num1 = num1 / 10;
		length--;
	}
	while (num1 > 0)
		;
	return (buffer);
}

/**
 * stringToInteger - Converts a string to an integer.
 * @s: Input string.
 * Return: Integer.
 */
int stringToInteger(char *s)
{
	unsigned int count = 0, size = 0, result = 0, sign = 1, multiplier = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			sign *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				multiplier *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		result = result + ((*(s + i) - '0') * multiplier);
		multiplier /= 10;
	}
	return (result * sign);
}
