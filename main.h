#ifndef MAIN_H
#define MAIN_H

#include<stdarg.h>
#include<unistd.h>
#include<stdio.h>

/**
 * struct format_specifiers - Struct for format specifiers
 * @spec: The format specifier character
 * @func: The corresponding function for the format specifier
 */
typedef struct format_specifiers
{
	char spec;
	int (*func)(va_list);
} format_t;

int _printf(const char *format, ...);

#endif /* MAIN_H */
