/*
 * vsprintf.c
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int vsprintf(char *buffer, const char *format, va_list ap)
{
	return vsnprintf(buffer, PTRDIFF_MAX, format, ap);
}
