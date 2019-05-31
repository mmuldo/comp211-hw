# COMP 211 standard Makefile.
#
# Spring 2019

# Required flags for compilation.
CFLAGS+=-std=c99 -Wall

driver : driver.c hw8.c hw8.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o driver driver.c hw8.c

tests : tests.c hw8.c hw8.h comp211.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o tests tests.c hw8.c

check :
	for f in comp211.h hw8.h hw8.c driver.c tests.c ; do \
		$(CC) $(CFLAGS) -c -o /dev/null $$f ; \
	done

clean :
	rm -f tests tests.o
	rm -f driver driver.o
	rm -f hw8.o


