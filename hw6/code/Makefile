# COMP 211 standard Makefile.
#
# Spring 2019

# Required flags for compilation.
CFLAGS+=-std=c99 -Wall

driver : driver.c hw6.c hw6.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o driver driver.c hw6.c

tests : tests.c hw6.c hw6.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o tests tests.c hw6.c

check :
	for f in comp211.h hw6.h hw6.c driver.c tests.c ; do \
		$(CC) $(CFLAGS) -c -o /dev/null $$f ; \
	done

clean :
	rm -f driver driver.o
	rm -f tests tests.o
	rm -f hw6.o


