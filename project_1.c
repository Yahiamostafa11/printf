#include "main.h"

void flush_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: Format string.
 * Return: Number of printed characters.
 */
int _printf(const char *format, ...)
{
	int i, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list args;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				flush_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			flush_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			++i;
			printed_chars += handle_print(format, &i, args, buffer,
				flags, width, precision, size);
		}
	}

	flush_buffer(buffer, &buff_ind);

	va_end(args);

	return (printed_chars);
}

/**
 * flush_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars.
 * @buff_ind: Index at which to add the next char, represents the length.
 */
void flush_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

