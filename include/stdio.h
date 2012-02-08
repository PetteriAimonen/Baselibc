/*
 * stdio.h
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <klibc/extern.h>
#include <klibc/inline.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

/* This structure doesn't necessarily exist, but it gives us something
   to define FILE * with */
struct File;
typedef struct File FILE;

#ifndef EOF
# define EOF (-1)
#endif

/*
 * Convert between a FILE * and a file descriptor.  We don't actually
 * have any in-memory data, so we just abuse the pointer itself to
 * hold the data.  Note, however, that for file descriptors, -1 is
 * error and 0 is a valid value; for FILE *, NULL (0) is error and
 * non-NULL are valid.
 */
static inline int fileno(FILE * __f)
{
	/* This should really be intptr_t, but size_t should be the same size */
	return (int)(size_t) __f - 1;
}

/* This is a macro so it can be used as initializer */
#define __create_file(__fd) ((FILE *)(size_t)((__fd) + 1))

/* Standard file descriptors - feel free to invent more for your own purposes
   as long as they don't clash with valid FILE * pointers. */
#define stdin  __create_file(0)
#define stdout __create_file(1)
#define stderr __create_file(2)

/* These are implemented in glue */
__extern size_t _fread(void *, size_t, FILE *);
__extern size_t _fwrite(const void *, size_t, FILE *);

/* Wrappers around _fread and _fwrite */
__extern_inline size_t fread(void *buf, size_t size, size_t nmemb, FILE *stream)
{
	return _fread(buf, size*nmemb, stream) / size;
}

__extern_inline size_t fwrite(const void *buf, size_t size, size_t nmemb, FILE *stream)
{
	return _fwrite(buf, size*nmemb, stream) / size;
}

__extern_inline int fputs(const char *s, FILE *f)
{
	return fwrite(s, 1, strlen(s), f);
}

__extern_inline int puts(const char *s)
{
	return fwrite(s, 1, strlen(s), stdout) + fwrite("\n", 1, 1, stdout);
}

__extern_inline int fputc(int c, FILE *f)
{
	unsigned char ch = c;
	return fwrite(&ch, 1, 1, f) == 1 ? ch : EOF;
}

__extern char *fgets(char *, int, FILE *);
__extern_inline int fgetc(FILE *f)
{
	unsigned char ch;
	return fread(&ch, 1, 1, f) == 1 ? ch : EOF;
}

#define putc(c,f)  fputc((c),(f))
#define putchar(c) fputc((c),stdout)
#define getc(f) fgetc(f)
#define getchar() fgetc(stdin)

__extern int printf(const char *, ...);
__extern int vprintf(const char *, va_list);
__extern int fprintf(FILE *, const char *, ...);
__extern int vfprintf(FILE *, const char *, va_list);
__extern int sprintf(char *, const char *, ...);
__extern int vsprintf(char *, const char *, va_list);
__extern int snprintf(char *, size_t n, const char *, ...);
__extern int vsnprintf(char *, size_t n, const char *, va_list);
__extern int asprintf(char **, const char *, ...);
__extern int vasprintf(char **, const char *, va_list);

__extern int sscanf(const char *, const char *, ...);
__extern int vsscanf(const char *, const char *, va_list);

#endif				/* _STDIO_H */
