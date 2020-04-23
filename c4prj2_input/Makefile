CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic
FNAME=test-future
build: $(FNAME).c
	gcc $(CFLAGS) -o $(FNAME) $(FNAME).c deck.c cards.c future.c input.c

test: $(FNAME).c
	gcc $(CFLAGS) -o $(FNAME) $(FNAME).c deck.c cards.c future.c input.c
	./$(FNAME)
clean:
	rm -f $(FNAME)
