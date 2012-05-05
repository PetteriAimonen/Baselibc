/*
 * vfprintf.c
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

// This amount of memory is always taken from stack.
// If it is not enough, the function tries to malloc().
#define BUFFER_SIZE	40

int vfprintf(FILE * file, const char *format, va_list ap)
{
	int rv;
	char buffer[BUFFER_SIZE];

	va_list ap_copy;
	va_copy(ap_copy, ap);
	rv = vsnprintf(buffer, BUFFER_SIZE, format, ap);
	va_end(ap_copy);

	if (rv < 0)
		return rv;

	if (rv > BUFFER_SIZE - 1)
	{
		char *buf2 = malloc(rv + 1);
		if (buf2 == NULL)
		{
			// Couldn't malloc, output what fits on stack.
			rv = BUFFER_SIZE - 1;
		} else {
			rv = vsnprintf(buf2, rv + 1, format, ap);
			rv = fwrite(buffer, rv, 1, file);
			free(buf2);
			return rv;
		}
	}

	return fwrite(buffer, 1, rv, file);
}
