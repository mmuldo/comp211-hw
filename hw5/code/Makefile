# COMP 211, Spring 2019, Wesleyan University
#

# Required flags for compilation.
CFLAGS+=-std=c99 -Wall

driver : driver.c hw5a.c hw5a.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o driver driver.c hw5a.c

tests : tests.c hw5a.c hw5a.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o tests tests.c hw5a.c

clean :
	rm -f driver driver.o
	rm -f tests tests.o
	rm -f hw5a.o


