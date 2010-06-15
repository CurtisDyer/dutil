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

# C compiler
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi -O3

# Assembler
# In this case, NASM is required; I like Intel syntax.
ASM = nasm

# *nix:
#FORMAT = elf
# Win32:
FORMAT = coff

# Librarian tool: this stores and manages the object code
LIB = ar


## Installation paths
# Possible Cygwin build
#LIB_DIR = /cygdrive/c/MinGW/lib
#INC_DIR = /cygdrive/c/MinGW/include/dutils
# Possible *nix build
LIB_DIR = /usr/local/lib
INC_DIR = /usr/local/include/dutils

# Library name
PROJECT = libdutil.a

## End of basic user configurable options ##


# Assembly build
asm_src := $(wildcard *.asm)
asm_obj := $(patsubst %.asm,%.o,$(asm_src))

# C build
src := $(wildcard *.c)
obj := $(patsubst %.c,%.o,$(src))
hdr := $(wildcard include/*.h)
file_hdr := $(notdir $(hdr))


$(PROJECT) : $(obj)
	$(LIB) cr $@ $^ $(asm_obj)

$(obj) : $(src)
	$(ASM) -f $(FORMAT) $(asm_src)
	$(CC) $(CFLAGS) -c $^

$(src) : $(hdr)


.PHONY : clean install uninstall
clean :
	rm -f $(obj) $(asm_obj)

install :
	mkdir -p $(INC_DIR)
	cp $(hdr) $(INC_DIR)
	mv $(PROJECT) $(LIB_DIR)

uninstall :
	rm -f $(LIB_DIR)/$(PROJECT)
	for i in $(file_hdr); do \
	rm -f $(INC_DIR)/$$i; \
done;

