/*
 * Test driver for dutil library. Outputs hexdump of object's memory.
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
#include <limits.h>
#include <dutils/hexdumps.h>

/*
 * TODO: after implementing a proper hash library, update this
 * approach to not be ugly.
 */
enum { B, S, I, D, STR, P, ARR };

<<<<<<< HEAD
static struct data {
=======
struct data {
>>>>>>> d7e57a9b5358265a322dc44ff1812ce1c3f1b968
	unsigned char b;
	short s;
	unsigned i;
	double d;
	char str[20];
	char *p;
	int arr[5];
<<<<<<< HEAD
} foo = {
	'B', 934, UINT_MAX-100, 3.14159265358979,
	"Hello, world!", "Hello, world!",
	{ 1, 1, 2, 3, 5 }
=======
>>>>>>> d7e57a9b5358265a322dc44ff1812ce1c3f1b968
};

void intro(void)
{
	puts("This program demonstrates vardump() by outputting the");
	puts("hexdumps of the `struct data' object and all of its");
	puts("individual members.\n");

	puts("The hexdump is a representation of how the objects");
	puts("are actually mapped out in memory. hexdump() behaves");
	puts("just like vardump(), except it outputs the contents of");
	puts("a file as a hexdump.\n");
}

<<<<<<< HEAD
#define COLS	8
#define WIDTH	4

=======
>>>>>>> d7e57a9b5358265a322dc44ff1812ce1c3f1b968
int main(void)
{
	size_t i = 0, len;
	const char *member[] = {
		"unsigned char b", "short s",
		"unsigned i", "double d",
		"char str[20]", "char *p",
		"int arr[5]"
	};
<<<<<<< HEAD
=======
	struct data foo = {
		'B', 934, UINT_MAX-100, 3.14159265358979,
		"Hello, world!", "Hello, world!",
		{ 1, 1, 2, 3, 5 }
	};
>>>>>>> d7e57a9b5358265a322dc44ff1812ce1c3f1b968

	intro();

	puts("struct data foo:");
<<<<<<< HEAD
	vardump(&foo, sizeof foo, COLS, WIDTH);
=======
	vardump(&foo, sizeof foo);
>>>>>>> d7e57a9b5358265a322dc44ff1812ce1c3f1b968
	putchar('\n');

	len = sizeof member / sizeof member[0];
	while (i < len) {
		printf("%s:\n", member[i]);
<<<<<<< HEAD
		switch (i++) {
		case B:		vardump(&foo.b,  sizeof foo.b, COLS, WIDTH);   break;
		case S:		vardump(&foo.s,  sizeof foo.s, COLS, WIDTH);   break;
		case I:		vardump(&foo.i,  sizeof foo.i, COLS, WIDTH);   break;
		case D:		vardump(&foo.d,  sizeof foo.d, COLS, WIDTH);   break;
		case STR:	vardump(foo.str, sizeof foo.str, COLS, WIDTH); break;
		case P:		vardump(&foo.p,  sizeof foo.p, COLS, WIDTH);   break;
		case ARR:	vardump(foo.arr, sizeof foo.arr, COLS, WIDTH); break;
		}
		putchar('\n');
	}

	puts("\n`NULL':");
	vardump(NULL, sizeof(void*), COLS, WIDTH);
	putchar('\n');

=======
		switch (i) {
			case B:		vardump(&foo.b,  sizeof foo.b);   break;
			case S:		vardump(&foo.s,  sizeof foo.s);   break;
			case I:		vardump(&foo.i,  sizeof foo.i);   break;
			case D:		vardump(&foo.d,  sizeof foo.d);   break;
			case STR:	vardump(foo.str, sizeof foo.str); break;
			case P:		vardump(&foo.p,  sizeof foo.p);   break;
			case ARR:	vardump(foo.arr, sizeof foo.arr); break;
		}
		++i;
		putchar('\n');
	}

>>>>>>> d7e57a9b5358265a322dc44ff1812ce1c3f1b968
	return 0;
}

