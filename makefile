CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

.PHONY: all clean

all: quantization

quantization: main.o input.o atom.o trie.o twowaylist.o
	$(CC) -o $@ $^

twowaylist.o: twowaylist.c twowaylist.h trie.h
	$(CC) $(CFLAGS) -c $<

trie.o: trie.c trie.h twowaylist.h
	$(CC) $(CFLAGS) -c $< 

atom.o: atom.c atom.h trie.h
	$(CC) $(CFLAGS) -c $<

input.o: input.c input.h atom.h trie.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c input.h atom.h trie.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o quantization