# GNU Make
#
# General utility library makefile.
#
# Copyright (C) 2010  Curtis Dyer
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#
# The author may be contacted at:  <dyer85@gmail.com>

CC = gcc
ASM = nasm
FORMAT = coff
LIB = ar

CFLAGS = -Wall -Wextra -pedantic -ansi -O3

#LIB_DIR = /usr/local/lib
#INC_DIR = /usr/local/include/dutils
LIB_DIR = /cygdrive/c/MinGW/lib
INC_DIR = /cygdrive/c/MinGW/include/dutils

# static library name
libname = libdutil.a

# Assembly build
asm_src := $(wildcard *.asm)
asm_obj := $(patsubst %.asm,%.o,$(asm_src))

# C build
src := $(wildcard *.c)
obj := $(patsubst %.c,%.o,$(src))
hdr := $(wildcard include/*.h)


$(libname) : $(obj)
	$(LIB) cr $@ $^ $(asm_obj)

$(obj) : $(src)
	$(ASM) -f $(FORMAT) $(asm_src)
	$(CC) $(CFLAGS) -c $^

$(src) : $(hdr)


.PHONY : clean install
clean :
	rm -f $(obj) $(asm_obj)
install :
	mkdir -p $(INC_DIR)
	cp $(hdr) $(INC_DIR)
	mv $(libname) $(LIB_DIR)

