/*
 * dutil.c - general utilities helpful in various programs
 *
 * Author: Curtis Dyer
 * License: LGPL v2
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

#include "include/dutil.h"

/*
 * revstr - perform in-place reverse of `len' characters in a string
 * pointed to by `str'. If `len' is longer than the length of the
 * string, the whole string will be reversed.
 *
 * The caller must ensure the pointer points to a writable C string.
 */
char* du_revstr(char *str, size_t len)
{
	char t;
	size_t i;
	size_t max = strlen(str) - 1;

	assert(str != NULL);

	len = len > max ? max : len;
	for (i = 0; i < len; ++i, --len)
		t = str[i], str[i] = str[len], str[len] = t;

	return str;
}

/*
 * lowercase - make characters in string pointed to by `str'
 * lowercase.
 *
 * `str' must point to a mutable C string.
 */
char* du_lowercase(char *str)
{
	char *r = str;
	assert(str != NULL);
	while (tolower((unsigned char)*str) != '\0')
		str++;
	return r;
}

/*
 * uppercase - make characters uppercase.
 */
char* du_uppercase(char *str)
{
	char *r = str;
	assert(str != NULL);
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
 * defined by the `UTIL_SPACE' macro, which is defined in "dutil.h".
 * It expands to a string literal containing common whitespace
 * characters.
 */
char* du_rtrimstr(char *str, const char *list)
{
	char *end;

	assert(str != NULL);

	if (list == NULL)
		list = UTIL_SPACE;

	end = strchr(str, '\0') - 1;
	while (end != str && strspn(end, list) != 0)
		end--;
	end[1] = '\0';

	return str;
}

/*
 * ltrimstr - this function behaves exactly like rtrimstr(), except it
 * returns a pointer to the first character not specified in `list'.
 * Also, as indicated by the const-qualified parameter, the string
 * pointed to by `str' is not actually modified, unlike with
 * rtrimstr().
 */
char* du_ltrimstr(const char *str, const char *list)
{
	assert(str != NULL);

	if (list == NULL)
		list = UTIL_SPACE;

	return (char*)(str + strspn(str, list));
}

/*
 * parsenum - search `src' from left to right until an integer value
 * is found or the first NUL terminator is found.
 */
long du_parsenum(const char *src, int *err)
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
 * separated by `sep'. The result is written to `dest'.
 *
 * The caller is responsible for ensuring the result fits in `dest'.
 */
char* du_formatnum(char *dest, long n, char sep, int group)
{
	int sign = n < 0;
	int i = 1, digit = 0;
	char *r = dest;

	assert(dest != NULL);

	while (n > 0) {
		if ((digit = n % 10) < 0)
			digit = -digit;
		*dest++ = digit + '0';

		if (n / 10 != 0 && (i % group) == 0)
			*dest++ = sep;

		n /= 10;
		i++;
	}

	if (sign)
		*dest++ = '-';
	*dest = '\0';

	return revstr(r, (size_t)(dest-r));
}

/*
 * convbase - convert `n' into a value in base `base' and store in
 * `dest'.
 *
 * The caller is responsible for ensuring the result fits in `dest'.
 * The range of `base' must be in [2,16], otherwise `convbase()'
 * returns NULL.
 */
char* du_convbase(char *dest, unsigned long n, int base)
{
	char *r = dest;

	if (base < 2 || base > (int)sizeof HEX_DIGITS - 1)
		return NULL;

	do {
		*dest++ = HEX_DIGITS[n % base];
		n /= base;
	} while (n != 0);
	*dest = '\0';

	return revstr(r, (size_t)(dest-r));
}

/*
 * getline - get a line from the stream pointed to by `fp', storing
 * the result into the buffer pointed to by `buf'. The size of the
 * buffer will be extended automatically if the line is sufficiently
 * long. However, if `maxsz' is nonzero, a line longer than `maxsz'
 * will not be copied and the maximum amount getline() will attempt to
 * allocate will be no larger than `maxsz'. The current size of the
 * buffer will be stored in the size_t object pointed to by `sz'
 *
 * If `*buf == NULL', initial memory will be allocated automatically.
 * Otherwise, `getline()' will attempt to use the buffer as-is, in
 * which case, `sz' should point to the size of the buffer you
 * allocated.
 *
 * Regardless of whether or not the buffer is allocated by getline(),
 * the caller is responsible for the memory of the buffer.
 *
 * Return values
 *
 *		GETLINE_MAXSIZE	- The line was longer than `maxsz'
 *		GETLINE_NOMEM	- Memory allocation error
 *
 *		EOF				- End of file reached (you must call ferror()
 *						  on the stream to distinguish between a read
 *						  error and EOF)
 */
int du_getline(char **buf, size_t *sz, size_t maxsz, FILE *fp)
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
	while (rc == 0 && (ch = getc(fp)) != EOF && ch != '\n') {
		if (chkmax && len+2 >= maxsz)
			rc = GETLINE_MAXSIZE;

		if (rc == 0 && len+2 >= *sz) {
			newsz = newsz < 1024 ? newsz+128 : 5*newsz/4;

			if (chkmax && newsz > maxsz)
				newsz = maxsz;

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
		(*buf)[len++] = ch;
	}

	(*buf)[len] = '\0';

	if (ch == EOF)
		rc = EOF;

	return rc;
}

/*
 * swap - swap two objects of arbitrary type. Behavior may be
 * undefined if the objects pointed to by `a' and `b' are not the same
 * size, as specified by `size'. Obviously, both `a' and `b' should
 * point to mutable storage. The `tmp' parameter is used as scratch
 * space for swapping the two objects. The caller must provide a
 * pointer to storage of the appropriate size.
 *
 * The reason the function doesn't allocate the scratch space
 * internally is because there are situations in which it is
 * undesirable to call malloc()/free() too frequently.
 *
 * The value returned is boolean: "1" indicates success, "0" failure.
 */
int du_swap(void *a, void *b, void *tmp, size_t size)
{
	int rc = 0;

	if (tmp != NULL) {
		rc = 1;
		memcpy(tmp, a, size);
		memcpy(a, b, size);
		memcpy(b, tmp, size);
	}

	return rc;
}

