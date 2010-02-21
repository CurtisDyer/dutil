/*
 * util.h - general utilities helpful in various programs
 *
 * Copyright (C) 2010  Curtis Dyer
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * The author may be contacted at:  <dyer85@gmail.com>
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string.h>


/*
 * errors
 */
enum util_errors {
	PARSENUM_NOCONV = 0x7f
};

/*
 * macros
 */
/* general whitespace characters */
#define UTIL_SPACE		" \n\r\t\v\f"

/* hex digits */
#define HEX_DIGITS		"0123456789abcdef"

/* get pointer to char before NUL terminator */
#define LAST_CHAR(s)	(strchr((s),'\0') - 1)

/*
 * prototypes
 */
char*	revstr(char *s);
char*	lowercase(char *str);
char*	uppercase(char *str);
char*	rtrim(char *str, const char *list);
char*	ltrim(char *str, const char *list);
char*	convbase(char *dest, unsigned long n, int base);
char*	formatnum(char *dest, long n, char sep, int group);
long	parsenum(const char *src, int *err);

#endif
