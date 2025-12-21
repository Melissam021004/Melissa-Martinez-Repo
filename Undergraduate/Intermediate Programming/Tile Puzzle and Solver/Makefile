GCC = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

puzzle: puzzle.o puzzle_funcs.o ppm_io.o
	$(GCC) -o puzzle puzzle.o puzzle_funcs.o ppm_io.o

puzzle.o: puzzle.c puzzle.h
	$(GCC) -c puzzle.c $(CFLAGS)

puzzle_funcs.o: puzzle_funcs.c puzzle.h
	$(GCC) $(CFLAGS) -c puzzle_funcs.c

ppm_io.o: ppm_io.c ppm_io.h
	$(GCC) $(CFLAGS) -c ppm_io.c

puzzle_tests.o: puzzle_tests.c puzzle.h
	$(GCC) $(CFLAGS) -c puzzle_tests.c 

test: puzzle_tests.o puzzle_funcs.o ppm_io.o
	$(GCC) -o test puzzle_tests.o puzzle_funcs.o ppm_io.o
	$ ./test

clean: 
	rm -f *.o *.gch puzzle test *~