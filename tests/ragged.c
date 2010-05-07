/*
 * Test driver for dutil library. This also uses the dynstr library.
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
 * The author may be contacted at:	<dyer85@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dutils/dutil.h>
#include <dynstr.h>

#define MAX_LINES	1000

int main(int argc, char **argv)
{
	DYNSTR *data[MAX_LINES];
	FILE *fp;
	const char *file = __FILE__;
	char *line = NULL;
	int count = 0;
	int status = 0;
	size_t size = 0;

	if (argc == 2) {
		if (strcmp("-h",argv[1]) == 0 || strcmp("--help",argv[1]) == 0) {
			printf("Output a file with line numbers.\n\n"
					"Usage: %s [file]\n\n"
					"If [file] is not specified, the source file used to build this program\n"
					"is used.\n",
					argv[0]);
			return 0;
		}
		else {
			file = argv[1];
		}
	}

	if ((fp = fopen(file, "r")) == NULL) {
		perror("");
		return EXIT_FAILURE;
	}

	for (; (status = getline(&line, &size, 0, fp)) == 0; ++count) {
		if (count >= MAX_LINES)
			break;

		data[count] = dyn_start(strlen(line) + 1);
		if (data[count] != NULL) {
			if (dyn_push(data[count], line) == NULL) {
				fputs("Memory error.\n", stderr);
				return EXIT_FAILURE;
			}
			else {
				printf("% 4d. %s\n", count+1, dyn_get_data(data[count],0));
			}
		}
		else {
			fputs("Memory error.\n", stderr);
		}
	}

	/* Free memory */
	while (count--)
		dyn_clean(data[count]);

	return 0;
}

