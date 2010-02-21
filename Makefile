# GNU Make
#
# General utility library makefile.
#
# Copyright (C) 2010  Curtis Dyer
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#
# The author may be contacted at: <dyer85@gmail.com>

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi -O3
LIB = ar

LIB_DIR = /usr/local/lib
INC_DIR = /usr/local/include/dutils

project = libdutil.a
src := $(wildcard *.c)
headers := $(patsubst %.c,%.h,$(src))
objects := $(patsubst %.c,%.o,$(src))

$(project) : $(objects)
	$(LIB) cr $@ $^

$(objects) : $(src)
	$(CC) $(CFLAGS) -c $^

$(src) : $(headers)


.PHONY : clean install
clean :
	rm -f $(objects)
install :
	mkdir -p $(INC_DIR)
	cp $(headers) $(INC_DIR)
	mv $(project) $(LIB_DIR)
