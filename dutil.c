/*
 * dutil.c - general utilities helpful in various programs
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
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * The author may be contacted at:  <dyer85@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

#include "dutil.h"


/*
 * revstr - reverse characters in a string pointed to by `s'. The
 * caller must ensure the pointer points to a writable C string.
 */
char* revstr(char *s)
{
	char t;
	size_t i, j;

	for (i = 0, j = strlen(s)+1; s != NULL && i < j; ++i, --j)
		t = s[i], s[i] = s[j], s[j] = t;
	return s;
}

/*
 * lowercase - make characters in string pointed to by `str'
 * lowercase.
 *
 * `str' must point to a mutable C string.
 */
char* lowercase(char *str)
{
	char *r = str;
	while (tolower((unsigned char)*str) != '\0')
		str++;
	return r;
}

/*
 * uppercase - the same as `lowercase()', except make characters
 * uppercase.
 */
char* uppercase(char *str)
{
	char *r = str;
	while (toupper((unsigned char)*str) != '\0')
		str++;
	return r;
}

/*
 * rtrimstr - remove (possibly consecutive) trailing characters
 * specified by the C string `list' (unless a null pointer is passed)
 * from a writable C string pointed to by `str'.
 *
 * If `list' is a null pointer, rtrimstr() will use the character list
 * defined by the `UTIL_SPACE' macro, which is defined in "util.h". It
 * expands to a string literal containing common whitespace
 * characters.
 */
char* rtrimstr(char *str, const char *list)
{
	char *end;

	assert(str != NULL);

	if (list == NULL)
		list = UTIL_SPACE;

	end = LAST_CHAR(str);
	while (end != str && strspn(end, list) != 0)
		end--;
	end[1] = '\0';

	return str;
}

/*
 * ltrimstr - this function behaves exactly like rtrimstr(), except it
 * returns a pointer to the first character not specified in `list'.
 */
char* ltrimstr(char *str, const char *list)
{
	assert(str != NULL);

	if (list == NULL)
		list = UTIL_SPACE;

	return str + strspn(str, list);
}

/*
 * parsenum - search `src' from left to right until an integer value
 * is found or until the first NUL terminator.
 */
long parsenum(const char *src, int *err)
{
	long number = 0;
	char *endp = NULL;
	unsigned char ch = '\0', peek = '\0';

	assert(src != NULL);

	if (err) *err = PARSENUM_NOCONV;

	while (*src != '\0') {
		ch = *src;
		peek = *(src + 1);
		if (!isdigit(ch)) {
			if (ch == '-' && isdigit(peek))
				break;
			else
				src++;
		}
		else {
			break;
		}
	}

	if (*src != '\0') {
		errno = 0;
		number = strtol(src, &endp, 10);
		if (err != NULL && endp != src)
			*err = errno != 0 ? errno : 0;
	}

	return number;
}

/*
 * formatnum - formats `n' by grouping `group' amount of digits,
 * separated by `sep'. The result is written to `src'.
 *
 * The caller is responsible for ensuring the result fits in `dest'.
 */
char* formatnum(char *dest, long n, char sep, int group)
{
	int neg = n < 0;
	int i = 1, digit = 0;
	char *r = dest;

	while (n) {
		if ((digit = n % 10) < 0)
			digit = -digit;
		*dest++ = digit + '0';

		if (n / 10 != 0 && (i % group) == 0)
			*dest++ = sep;

		n /= 10;
		i++;
	}
	if (neg)
		*dest++ = '-';

	*dest = '\0';

	return revstr(r);
}

/*
 * Convert `n' into a value in base `base' and store in `dest'.
 *
 * The caller is responsible for ensuring the result fits in `dest'.
 * The range of `base' must be in [2,16], otherwise `convbase()'
 * returns NULL.
 */
char* convbase(char *dest, unsigned long n, int base)
{
	if (base < 2 || base > (int)sizeof HEX_DIGITS - 1)
		return NULL;

	do {
		*dest++ = HEX_DIGITS[n % base];
		n /= base;
	} while (n != 0);
	*dest = '\0';

	return revstr(dest);
}

/*
 * dyn_getline - get a line from the stream pointed to by `fp',
 * storing the result into the buffer pointed to by `buf'. The size of
 * the buffer will be extended automatically if the line is
 * sufficiently long. However, if `maxsz' is nonzero, a line longer
 * than `maxsz' will not be copied. The size of the buffer will be
 * stored in the size_t object pointed to by `sz'
 *
 * If `*buf == NULL', initial memory will be allocated automatically.
 * Otherwise, `getline()' will attempt to use the buffer as-is, in
 * which case, `sz' should point to the size of the buffer you
 * allocated.
 *
 * Regardless of whether or not the buffer is allocated by
 * `getline()', the caller is responsible for `free()'ing the memory.
 *
 * Return values
 *
 *		GETLINE_MAXMEM	- The line was longer than `maxsz'
 *		GETLINE_NOMEM	- Memory allocation error
 *
 *		EOF				- End of file reached (you must call ferror()
 *						  on the stream to distinguish between a read
 *						  error and EOF)
 */
int getline( char **buf, size_t *sz, size_t maxsz, FILE *fp )
{
	int ch = 0, rc = 0;
	int chkmax = maxsz > 0;
	size_t len;
	size_t newsz = *sz;
	char *tmp = NULL;

	assert(buf != NULL && sz != NULL);

	if (*buf == NULL) {
		*sz = *sz == 0 ? BUFSIZ : *sz;
		if ((*buf = malloc(*sz)) == NULL)
			rc = GETLINE_NOMEM;
	}

	len = 0;
	while (rc == 0 && (ch = fgetc(fp)) != EOF && ch != '\n') {
		if (chkmax && *sz >= maxsz) {
			rc = GETLINE_MAXMEM;
			break;
		}

		if (len + 2 >= *sz) {
			if (newsz < 250) {
				newsz += 100;
			}
			else {
				newsz = 3 * newsz / 2;
			}

			if (chkmax && newsz > maxsz) {
				newsz = maxsz;
			}

			/* Attempt to resize memory block */
			if ((tmp = realloc(*buf, newsz)) != NULL) {
				*buf = tmp;
				*sz = newsz;
				tmp = NULL;
			}
			else {
				rc = GETLINE_NOMEM;
			}
		}

		/* Store char read from input stream */
		if (rc == 0) {
			(*buf)[len++] = ch;
		}
	}

	if (rc != GETLINE_NOMEM)
		(*buf)[len] = '\0';

	if (ch == EOF)
		rc = EOF;

	return rc;
}
