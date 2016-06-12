# Autoversion makefile
# (C) 2015-2016, Ruben Carlo Benante <rcb@beco.cc>
# GNU License v2

.PHONY: clean cleanall
.PRECIOUS: %.o
SHELL=/bin/bash -o pipefail

MAJOR = 0
MINOR = 1
BUILD = $(shell date +"%g%m%d.%H%M%S")
DEFSYM = $(subst .,_,$(BUILD))
VERSION = "\"$(MAJOR).$(MINOR).$(BUILD)\""
CC = gcc
CFLAGS = -Wall -Wextra -g -O0 -c -std=gnu99 
CPPFLAGS = -DVERSION=$(VERSION) -DBUILD="\"$(BUILD)\"" #-DDEBUG=1
LDLIBS = -Wl,--defsym,BUILD_$(DEFSYM)=0 -lm -lncurses
o = breakme 

#object
%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ |& tee errors.err

#binary
$(o) : % : %.o $(OBJ)
	$(CC) $(LDLIBS) $^ -o $@ |& tee errors.err
	echo $(o) version $(VERSION) > VERSION

clean:
	rm -f *.o errors.err

cleanall:
	rm -i $(o) *.x *.o errors.err

