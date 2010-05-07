# GNU Make
#
# Create test binaries.
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

ARCHIVE = gzip
EXT = gz
MANDIR = /usr/share/man/man3

SRC := $(wildcard *.3)
OUT := $(patsubst %.3,%.3.$(EXT),$(SRC))

$(OUT) : $(SRC)
	for i in $^; do \
		$(ARCHIVE) -c -9 $$i > $(MANDIR)/$$i.$(EXT); \
	done

.PHONY : clean
clean :
	rm -f *.$(EXT)

