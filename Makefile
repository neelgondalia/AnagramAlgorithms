all: makebin Anagram_BruteForce Anagram_PreSorting

Anagram_BruteForce: makebin Anagram_BruteForce.c
	gcc Anagram_BruteForce.c -Wall -lm -o bin/Anagram_BruteForce -ansi -std=c99 -g

Anagram_PreSorting: makebin Anagram_PreSorting.c
	gcc Anagram_PreSorting.c -Wall -lm -o bin/Anagram_PreSorting -ansi -std=c99 -g

del:
	rm bin/*
	
makebin:
	mkdir -p bin
