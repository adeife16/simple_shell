#include "main.h"

/**
 * assign_line_buffer - Assigns the line buffer for get_line function.
 *
 * @lineptr: Pointer to the buffer that stores the input string.
 * @n: Size of the lineptr buffer.
 * @buffer: String that is being assigned to line.
 * @buffer_size: Size of the buffer.
 */
void assign_line_buffer(char **lineptr, size_t *n, char *buffer, size_t buffer_size)
{
	if (*lineptr == NULL)
	{
		if (buffer_size > BUFSIZ)
			*n = buffer_size;
		else
			*n = BUFSIZ;

		*lineptr = buffer;
	}
	else if (*n < buffer_size)
	{
		if (buffer_size > BUFSIZ)
			*n = buffer_size;
		else
			*n = BUFSIZ;

		*lineptr = buffer;
	}
	else
	{
		_stringCopy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * custom_getline - Reads input from a stream.
 *
 * @lineptr: Pointer to the buffer that stores the input.
 * @n: Size of lineptr.
 * @stream: Stream to read from.
 * Return: The number of bytes read.
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	int read_result;
	static ssize_t input_size;
	ssize_t retval;
	char *buffer;
	char current_char = 'z';

	if (input_size == 0)
		fflush(stream);
	else
		return (-1);

	input_size = 0;

	buffer = malloc(sizeof(char) * BUFSIZ);
	if (buffer == 0)
		return (-1);

	while (current_char != '\n')
	{
		read_result = read(STDIN_FILENO, &current_char, 1);

		if (read_result == -1 || (read_result == 0 && input_size == 0))
		{
			free(buffer);
			return (-1);
		}

		if (read_result == 0 && input_size != 0)
		{
			input_size++;
			break;
		}

		if (input_size >= BUFSIZ)
			buffer = _reallocate(buffer, input_size, input_size + 1);

		buffer[input_size] = current_char;
		input_size++;
	}

	buffer[input_size] = '\0';
	assign_line_buffer(lineptr, n, buffer, input_size);
	retval = input_size;

	if (read_result != 0)
		input_size = 0;

	return (retval);
}
