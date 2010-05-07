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

#ifndef HEXDUMPS_H_
#define HEXDUMPS_H_

#ifdef __cplusplus
exter "C" {
#endif

/* Macros */
#define BYTE_COLS		8
#define BYTE_SEP_LEN	4

#define IS_NEW_ROW(n) ( 0 == ((n) % (BYTE_COLS)) )
#define SPACES(n) ( (((BYTE_COLS) - ((n) % (BYTE_COLS))) * (BYTE_SEP_LEN)) )

/* Prototypes */
void	vardump(void *data, size_t n);
void	hexdump(FILE *in);

#ifdef __cplusplus
}
#endif

#endif
