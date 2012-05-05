#ifndef _TINYPRINTF_H_
#define _TINYPRINTF_H_

#include <stdarg.h>
#include <stdlib.h>

typedef void (*putcf) (void *, char);

void tfp_format(void *putp, putcf putf, const char *fmt, va_list va);

#endif
