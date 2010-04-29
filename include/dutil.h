/*
 * dutil.h - general utilities helpful in various programs
 *
 * Author: Curtis Dyer
 * License: LGPLV v2
 * Version: 0.0.1 Alpha
 *
 * Copyright (C) 2010  Curtis Dyer
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * The author may be contacted at:  <dyer85@gmail.com>
 */

#ifndef DUTILS_H_
#define DUTILS_H_

#include <string.h>

#include "cdecl.h"

/*
 * Version
 */
#define DUTIL_VERSION		1UL

/*
 * Errors
 */
enum dutil_errors {
	GETLINE_NOMEM = -255,
	GETLINE_MAXSIZE = 1,

	PARSENUM_NOCONV = 127
};


/*
 * Macros
 */
/* general whitespace characters */
#define DUTIL_SPACE			" \n\r\t\v\f"

/* hex digits */
#define DUTIL_HEX			"0123456789abcdef"

/* count array elements */
#define ARRAY_COUNT(a)		(sizeof (a) / sizeof (a)[0])

/* Shortcut to trim both ends of a string */
#define TRIMSTR(s,f)		rtrimstr(ltrimstr((s),(f)), (f))

/*
 * prototypes
 */
#ifdef __cplusplus
extern "C" {
#endif

/* String manipulation */
char*	revstr(char *s, size_t len);
char*	lowercase(char *str);
char*	uppercase(char *str);
char*	rtrimstr(char *str, const char *list);
char*	ltrimstr(const char *str, const char *list);
char*	convbase(char *dest, unsigned long n, int base);
char*	formatnum(char *dest, long n, char sep, int group);
long	parsenum(const char *src, int *err);

/* I/O */
int		getline(char **buf, size_t *sz, size_t maxsz, FILE *fp);

/* Bit manipulation */
int		CDECL(bitcount(unsigned int x));

#ifdef __cplusplus
}
#endif

#endif /* DUTILS_H_ */
