/*
 * hexdumps.h - output memory representations of objects and files in
 * the form of hex dumps.
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
#include <ctype.h>

#include "include/hexdumps.h"

/*
 * Output the binary memory representation of the object pointed to by
 * `data', whose size is `n'.
 */
void vardump(void *data, size_t n)
{
	unsigned char *p;
	unsigned char ascii[BYTE_COLS + 1];
	size_t i;

	for (p = data, i = 0; i < n; ++i, ++p) {
		unsigned col = i % BYTE_COLS;

		if (IS_NEW_ROW(i)) {
			if (i > 0)
				printf("    %s\n", ascii);
			printf("%p:    ", (void*)p);
		}

		printf("%02X  ", *p);
		ascii[col] = !isprint(*p) ? '.' : *p;
		ascii[col + 1] = '\0';

		if (i + 1 == n)
			printf("%*s%s\n", SPACES(i), " ", ascii);
	}
}

/*
 * Output the binary representation of the file represented by `in'.
 */
void hexdump(FILE *in)
{
	int c, nc, i;
	unsigned char ascii[BYTE_COLS + 1];

	i = 0;
	while ((c = fgetc(in)) != EOF) {
		unsigned col = i % BYTE_COLS;
		nc = fgetc(in);

		if (IS_NEW_ROW(i)) {
			if (i > 0)
			printf("    %s\n", ascii);
			printf("0x%08x:    ", i);
		}

		printf("%02X  ", c);
		ascii[col] = !isprint(c) ? '.' : c;
		ascii[col + 1] = '\0';

		if (nc == EOF)
			printf("%*s%s\n", SPACES(i), " ", ascii);

		ungetc(nc, in);
		i++;
	}
}

