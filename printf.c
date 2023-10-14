#include"main.h"
/**
 * _printf - Print formatted output to stdout
 * @format: The format string
 * @...: Variable number of arguments
 *
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
	int char_count = 0, count, c, len, num, j;
	unsigned int uns_num;
	char buffer[12], binary[33];
	const char *str;
	va_list args;

	va_start(args, format);

	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
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
			}
			else if (*format == 's')
			{
				str = va_arg(args, const char *);
				len = 0;
				while (str[len] != '\0')
					len++;
				write(1, str, len);
				char_count += len;
			}
			else if (*format == '%')
			{
				write(1, "%", 1);
				char_count++;
			}
			else if (*format == 'd' || *format == 'i')
			{
				num = va_arg(args, int);
				count = snprintf(buffer, sizeof(buffer), "%d", num);
				write(1, buffer, count);
				char_count += count;
			}
			else if (*format == 'b') {
				uns_num = va_arg(args, unsigned int);
				for (j = 31; j >= 0; j--)
					binary[31 - j] = ((uns_num >> j) & 1) ? '1' : '0';
				binary[32] = '\0';
				for (j = 0; binary[j] != '\0'; j++)
				{
					write(1, &binary[j], 1);
					char_count++;
				}
			}
		}
		format++;
	}

	va_end(args);

	return (char_count);
}
