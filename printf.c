#include"main.h"
/**
 * int_to_binary - Convert an unsigned integer to a binary string
 * @buffer: The buffer to store the binary string
 * @num: The unsigned integer
 *
 * Return: The number of characters written to the buffer, or -1 on error
 */
int int_to_binary(char *buffer, unsigned int num)
{
	int count = 0, i = 0, j;
	char temp;

	if (buffer == NULL)
		return (-1);
	if (num == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return (1);
	}
	while (num > 0)
	{
		buffer[i] = (num % 2) + '0';
		num /= 2;
		i++;
	}
	for (j = 0; j < i / 2; j++)
	{
		temp = buffer[j];
		buffer[j] = buffer[i - j - 1];
		buffer[i - j - 1] = temp;
	}
	buffer[i] = '\0';
	count = i;
	return (count);
}
/**
 * _printf - Print formatted output to stdout
 * @format: The format string
 * @...: Variable number of arguments
 *
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
	int char_count = 0, count, c, len, num;
	char buffer[12];
	const char *str;
	va_list args;

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			char_count++;
		}
		else
		{
			format++;
			if (*format == 'c')
			{
				c = va_arg(args, int);
				write(1, &c, 1);
				char_count++;
