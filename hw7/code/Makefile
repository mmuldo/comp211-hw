# COMP 211 standard Makefile.
#
# Spring 2019

# Required flags for compilation.
CFLAGS+=-std=c99 -Wall

driver : driver.c hw7.c hw7.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o driver driver.c hw7.c

tests : tests.c hw7.c hw7.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o tests tests.c hw7.c

clean :
	rm -f driver driver.o
	rm -f tests tests.o
	rm -f hw7.o


