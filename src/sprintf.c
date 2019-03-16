/*
 * sprintf.c
 */

#include <stdio.h>
#include <stdint.h>
#ifndef NO_UNISTD_H
#include <unistd.h>
#endif

int sprintf(char *buffer, const char *format, ...)
{
	va_list ap;
	int rv;

	va_start(ap, format);
	rv = vsnprintf(buffer, PTRDIFF_MAX, format, ap);
	va_end(ap);

	return rv;
}
