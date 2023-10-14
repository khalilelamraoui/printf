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
	int char_count = 0, c, len;
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
		}
		format++;
	}

	va_end(args);
	return (char_count);
}
