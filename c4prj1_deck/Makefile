CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic
build: test-c4deck.c
	gcc $(CFLAGS) -o test-c4deck test-c4deck.c

test: test-c4deck.c
	gcc $(CFLAGS) -o test-c4deck test-c4deck.c
	./test-c4deck
clean:
	rm -f test-c4deck
