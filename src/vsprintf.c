/*
 * vsprintf.c
 */

#include <stdio.h>
#include <stdint.h>
#ifndef NO_UNISTD_H
#include <unistd.h>
#endif

int vsprintf(char *buffer, const char *format, va_list ap)
{
	return vsnprintf(buffer, PTRDIFF_MAX, format, ap);
}
