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

<<<<<<< HEAD
# Don't compress these
INC := hexdumps.3

ZIP := fdump.3 vardump.3 fgetln.3
OUT := $(patsubst %.3, %.3.$(EXT), $(ZIP))

$(OUT) : $(ZIP)
	for i in $^; do \
	$(ARCHIVE) -c -9 $$i > $$i.$(EXT); \
done; \

.PHONY : clean install uninstall
clean :
	rm -f *.$(EXT)

install :
	for i in $(OUT) $(INC); do \
	cp $$i $(MANDIR); \
done;

uninstall :
	for i in $(OUT) $(INC); do \
	rm -f $(MANDIR)/$$i; \
done;

=======
SRC := $(wildcard *.3)
OUT := $(patsubst %.3,%.3.$(EXT),$(SRC))

$(OUT) : $(SRC)
	for i in $^; do \
		$(ARCHIVE) -c -9 $$i > $(MANDIR)/$$i.$(EXT); \
	done

.PHONY : clean
clean :
	rm -f *.$(EXT)

>>>>>>> d7e57a9b5358265a322dc44ff1812ce1c3f1b968
