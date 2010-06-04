/*
 * Test driver for dutil library - examples for trimming strings and
 * parsing integer values.
 *
 * License note: the test driver program itself is licensed under
 * version 2 of the GPL, but the util library itself is licensed under
 * the LGPL.
 *
 * Copyright (C) 2010  Curtis Dyer
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * The author may be contacted at:  <dyer85@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <dutils/dutil.h>

#define MAXLEN	50

int main(void)
{
	long n = 0;
	size_t i = 0, size;
	const char *list = DUTIL_SPACE "-.";
	char data[][MAXLEN] = {
		"\t\t   String 1iterals!\t\t",
		"------ They are so useful..",
		"\tSo are integers: 29384.  \t"
	};

	puts("Trimming strings of white space, dashes, and periods.\n"
			"Any integers found in strings are also reported.\n");

	size = sizeof data / sizeof *data;
	while (i < size) {
		printf("Original string:\n\t[%s]\n", data[i]);
		printf("Trimming both sides:\n\t[%s]\n", TRIMSTR(data[i], list));

		if (parsenum(data[i], &n) == 0)
			printf("\t- Found integer: %ld\n", n);

		putchar('\n');
		i++;
	}

	return 0;
}

