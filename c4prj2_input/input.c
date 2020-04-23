#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

deck_t * hand_from_string(const char *str, future_cards_t *fc){
  deck_t *deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  
  for(int i = 0; i < strlen(str); i++){
    if(str[i] == ' ' || str[i] == '\n'){
      continue;
    } else if(str[i] == '?'){
      i++;
      size_t index = str[i] - '0';
      while(str[i+1] != ' ' && str[i+1] != '\n'){
	i++;
	index = (index * 10) + str[i] - '0';
      }
      card_t *empty = add_empty_card(deck);
      add_future_card(fc, index, empty);
    } else {
      card_t card = card_from_letters(str[i], str[i+1]);
      add_card_to(deck, card);
      i++;
    }
  }

  if(deck->n_cards < 5){
    fprintf(stderr, "5 cards not present");
    return NULL;;
  }

  return deck;
}

deck_t ** read_input(FILE *f, size_t *n_hands, future_cards_t *fc){
  deck_t **decks = NULL;
  size_t nhands = 0;
  char *line = NULL;
  size_t sz = 0;
  while(getline(&line, &sz, f) >= 0){
    if(line[0] == '\n'){
      continue;
    }
    nhands++;
    decks = realloc(decks, (nhands)*sizeof(*decks));
    decks[nhands - 1] = hand_from_string(line, fc);
  }
  free(line);
  *n_hands = nhands;
  return decks;
}
