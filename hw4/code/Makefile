# COMP 211, Spring 2019, Wesleyan University
#

# Required flags for compilation.
CFLAGS+=-std=c99 -fdiagnostics-color=auto -Wall

driver : driver.c hw4.c hw4.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o driver driver.c hw4.c

tests : tests.c hw4.c hw4.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o tests tests.c hw4.c

clean :
	rm -f driver driver.o
	rm -f tests tests.o
	rm -f hw4.o


