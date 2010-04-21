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

#include "cdecl.h"	/* for functions requiring __cdecl */

/*
 * version
 */
enum dutil_version {
	DUTIL_VERSION = 1UL
};

/*
 * errors
 */
enum dutil_errors {
	/* getline() */
	GETLINE_NOMEM = -255,
	GETLINE_MAXSIZE = 1,

	/* parsenum() */
	PARSENUM_NOCONV = 0x7f
};

/*
 * macros
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

/* string manipulation */
char*	du_revstr(char *s, size_t len);
char*	du_lowercase(char *str);
char*	du_uppercase(char *str);
char*	du_rtrimstr(char *str, const char *list);
char*	du_ltrimstr(const char *str, const char *list);
char*	du_convbase(char *dest, unsigned long n, int base);
char*	du_formatnum(char *dest, long n, char sep, int group);
long	du_parsenum(const char *src, int *err);

/* I/O */
int		du_getline(char **buf, size_t *sz, size_t maxsz, FILE *fp);

/* binary data */
int		CDECL(du_bitcount(unsigned int x));

/* miscellaneous */
int		du_swap(void *a, void *b, void *tmp, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* DUTILS_H_ */
