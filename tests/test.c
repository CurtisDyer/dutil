/*
 * Test driver for util library.
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../util.h"

int main(void)
{
	char data[][BUFSIZ] = {
		"\t\t   String 1iterals!\t\t\n",
		"------ They are so useful..",
		"\tSo are integers: 29384.\n"
	};
	const char *filter = UTIL_SPACE "-.";
	int err;
	long n = 0;
	size_t i = 0;

	while (i < sizeof data / sizeof data[0]) {
		puts(rtrim(ltrim(data[i], filter), filter));
		n = parsenum(data[i], &err);
		if (err == 0)
			printf("\t - Found integer: %ld\n", n);
		i++;
	}

	return 0;
}
