# Tyler Taormina - taormina@pdx.edu

CC = gcc
DEBUG = -g
DEFINES = 
MATH = -lm
PTHREAD = -pthread
CFLAGS = $(DEBUG) -Wall -Wshadow -Wextra -Wunreachable-code -Wredundant-decls \
		-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
		-Wdeclaration-after-statement -Wno-return-local-addr \
		-Wunsafe-loop-optimizations -Wuninitialized

PROG1 = helpme
PROG2 = linked_list
PROG3 = bin_cat
PROG4 = init_file
PROGS = $(PROG1) $(PROG3) $(PROG4)

INCLUDES = linked_list.h

all: $(PROGS)

$(PROG1): $(PROG1).o $(PROG2).o
	$(CC) $(CFLAGS) -o $@ $^ 

$(PROG1).o: $(PROG1).c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

$(PROG2).o: $(PROG2).c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

$(PROG3).o: $(PROG3).c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

$(PROG4).o: $(PROG4).c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

clean cls: 
	rm -f $(PROGS) *.o *~ \#* *.txt

test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./helpme && tail valgrind-out.txt

tar: 
	tar cvfa taormina_helpme.tar.gz *.[ch] [mM]akefile

open: 
	vim *.c *.h Makefile -p
