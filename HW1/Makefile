CC = gcc
CFLAGS = -g -Wall -Werror -std=c99

all: csim

csim: cachesim.c cacheline.c cacheline.h functions.c functions.h
	$(CC) $(CFLAGS) -o cachesim cachesim.c cacheline.c functions.c -lm 

#
# cleanup
#
clean:
	rm -rf *.o
	rm -rf *.tmp
	rm -f cachesim 
	rm -f trace.all trace.f*

