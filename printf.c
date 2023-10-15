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
        int char_count = 0, count, c, len, num, leading_zero, bit, j, ascii_code, i;
        unsigned int uns_num;
	void *ptr;
        char buffer[1024], c_rot, *rot13, hex[3], *str2;
        const char *str, *str_Rot, *format_str;
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
				format_str = (*format == '0') ? "%0d" : "%d";
                                count = snprintf(buffer, sizeof(buffer), format_str, num);
                                write(1, buffer, count);
                                char_count += count;
			}
			else if (*format == 'b') {
                                uns_num = va_arg(args, unsigned int);
                                leading_zero = 1;
				for (j = 31; j >= 0; j--)
				{
					bit = ((uns_num >> j) & 1);
					if (bit == 1)
						leading_zero = 0;
					if (leading_zero == 0)
					{
						write(1, (bit == 1) ? "1" : "0", 1);
						char_count++;
					}
				}
				if (char_count == 0)
				{
					write(1, "0", 1);
					char_count = 1;
				}
                        }
			else if (*format == 'p')
			{
				ptr = va_arg(args, void *);
				count = snprintf(buffer, sizeof(buffer), "%p", ptr);
				write(1, buffer, count);
				char_count += count;
			}
			else if (*format == 'u')
			{
				num = va_arg(args, unsigned int);
				count = snprintf(buffer, sizeof(buffer), "%u", num);
				write(1, buffer, count);
				char_count += count;
			}
			else if (*format == 'o')
			{
				num = va_arg(args, unsigned int);
				count = snprintf(buffer, sizeof(buffer), "%o", num);
				write(1, buffer, count);
				char_count += count;
			}
			else if (*format == 'x' || *format == 'X')
			{
				num = va_arg(args, unsigned int);
				count = snprintf(buffer, sizeof(buffer), (*format == 'x') ? "%x" : "%X", num);
				write(1, buffer, count);
				char_count += count;
			}
			else if (*format == 'S')
			{
				str = va_arg(args, const char *);
				while (*str)
				{
					if (*str >= 32 && *str < 127)
					{
						write(1, str, 1);
						char_count++;
					}
					else
					{
						write(1, "\\x", 2);
						char_count += 2;
						ascii_code = *str;
						snprintf(hex, sizeof(hex), "%02X", ascii_code);
						write(1, hex, 2);
						char_count += 2;
					}
					str++;
				}
			}
			else if (*format == 'r')
			{
				str = va_arg(args, const char *);
				len = 0;
				str2 = (char *)malloc((len + 1) * sizeof(char));
				while (str[len] != '\0')
					len++;
				if (str2)
				{
					for(j = len - 1, i = 0; j >= 0; j--, i++)
						str2[i] = str[j];
					str2[len] = '\0';
					write(1, str2, len);
					char_count += len;
					free(str2);
				}
                        }
			else if (*format == 'R')
			{
				str_Rot = va_arg(args, const char *);
				len = 0;
				while (str_Rot[len] != '\0')
					len++;
				rot13 = (char *)malloc((len + 1) * sizeof(char));
				if (rot13) {
					for (j = 0; j < len; j++) {
						c_rot = str[j];
						if ((c_rot >= 'a' && c_rot <= 'm')
						|| (c_rot >= 'A' && c_rot <= 'M'))
							rot13[j] = c_rot + 13;
						else if ((c_rot >= 'n' && c_rot <= 'z')
						|| (c_rot >= 'N' && c_rot <= 'Z'))
							rot13[j] = c_rot - 13;
						else
							rot13[j] = c_rot;
					}
					rot13[len] = '\0';
					write(1, rot13, len);
					char_count += len;
					free(rot13);
				}
			}
		}
                format++;
        }

        va_end(args);

        return (char_count);
}
