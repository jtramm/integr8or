COMPILER    = gnu

program = test

source = \
main.c \
integr8or.c\

obj = $(source:.c=.o)

# Standard Flags
CFLAGS := -std=gnu99

# Linker Flags
LDFLAGS = -lm

# Regular gcc Compiler
ifeq ($(COMPILER),gnu)
  CC = gcc
  LDFLAGS += 
  CFLAGS += -Ofast -ffast-math -fopenmp -Wall -flto
endif

# intel Compiler
ifeq ($(COMPILER),intel)
  CC = icc
  LDFLAGS += 
  CFLAGS += -O3 -xhost -ansi-alias -no-prec-div -DINTEL -openmp -ipo
endif

$(program): $(obj) integr8or_header.h
	$(CC) $(CFLAGS) $(obj) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(program) $(obj) data.dat
run:
	./$(program) > data.dat
graph:
	gnuplot graph.gp
edit:
	vim -p $(source) integr8or_header.h
