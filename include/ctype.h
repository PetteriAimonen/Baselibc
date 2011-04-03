/*
 * ctype.h
 *
 * This assumes ISO 8859-1, being a reasonable superset of ASCII.
 */

#ifndef _CTYPE_H
#define _CTYPE_H

#include <klibc/extern.h>
#include <klibc/inline.h>

/*
 * This relies on the following definitions:
 *
 * cntrl = !print
 * alpha = upper|lower
 * graph = punct|alpha|digit
 * blank = '\t' || ' ' (per POSIX requirement)
 */
enum {
	__ctype_upper = (1 << 0),
	__ctype_lower = (1 << 1),
	__ctype_digit = (1 << 2),
	__ctype_xdigit = (1 << 3),
	__ctype_space = (1 << 4),
	__ctype_print = (1 << 5),
	__ctype_punct = (1 << 6),
	__ctype_cntrl = (1 << 7),
};

extern const unsigned char __ctypes[];

__extern_inline int isalnum(int __c)
{
	return __ctypes[__c + 1] &
	    (__ctype_upper | __ctype_lower | __ctype_digit);
}

__extern_inline int isalpha(int __c)
{
	return __ctypes[__c + 1] & (__ctype_upper | __ctype_lower);
}

__extern_inline int isascii(int __c)
{
	return !(__c & ~0x7f);
}

__extern_inline int isblank(int __c)
{
	return (__c == '\t') || (__c == ' ');
}

__extern_inline int iscntrl(int __c)
{
	return __ctypes[__c + 1] & __ctype_cntrl;
}

__extern_inline int isdigit(int __c)
{
	return ((unsigned)__c - '0') <= 9;
}

__extern_inline int isgraph(int __c)
{
	return __ctypes[__c + 1] &
	    (__ctype_upper | __ctype_lower | __ctype_digit | __ctype_punct);
}

__extern_inline int islower(int __c)
{
	return __ctypes[__c + 1] & __ctype_lower;
}

__extern_inline int isprint(int __c)
{
	return __ctypes[__c + 1] & __ctype_print;
}

__extern_inline int ispunct(int __c)
{
	return __ctypes[__c + 1] & __ctype_punct;
}

__extern_inline int isspace(int __c)
{
	return __ctypes[__c + 1] & __ctype_space;
}

__extern_inline int isupper(int __c)
{
	return __ctypes[__c + 1] & __ctype_upper;
}

__extern_inline int isxdigit(int __c)
{
	return __ctypes[__c + 1] & __ctype_xdigit;
}

__extern_inline int toupper(int __c)
{
	return islower(__c) ? (__c & ~32) : __c;
}

__extern_inline int tolower(int __c)
{
	return isupper(__c) ? (__c | 32) : __c;
}

#endif				/* _CTYPE_H */
