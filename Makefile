CC=gcc

make:	main.c
	$(CC) -Wall -Wextra -pedantic --std=c99 -o compiled main.c

run:	compiled
	./compiled

clean: 
	rm compiled

