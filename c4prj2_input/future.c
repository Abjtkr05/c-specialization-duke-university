#include <stdlib.h>
#include <stdio.h>
#include "future.h"

void add_card_ptr_to_future_deck(deck_t *fdeck, card_t *ptr){
  fdeck->cards = realloc(fdeck->cards, (fdeck->n_cards + 1)*sizeof(*fdeck->cards));
  fdeck->cards[fdeck->n_cards] = ptr;
  fdeck->n_cards++;
}

void add_future_card(future_cards_t *fc, size_t index, card_t *ptr){
  while(fc->n_decks <= index){
    fc->decks = realloc(fc->decks,(fc->n_decks + 1)*sizeof(*fc->decks));
    fc->decks[fc->n_decks].cards = NULL;
    fc->decks[fc->n_decks].n_cards = 0;
    fc->n_decks++;
  }
  add_card_ptr_to_future_deck(&fc->decks[index], ptr);
}

void future_cards_from_deck(deck_t *deck, future_cards_t *fc){
  if(fc->n_decks > deck->n_cards){
    printf("Cards needed (%zd) is greater than cards available (%zd)\n", deck->n_cards, fc->n_decks);
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < fc->n_decks; i++){
    if(fc->decks[i].n_cards == 0){
      continue;
    }
    for(int x = 0; x < fc->decks[i].n_cards; x++){
      (*(fc->decks[i].cards[x])).value = (*(deck->cards[i])).value;
      (*(fc->decks[i].cards[x])).suit = (*(deck->cards[i])).suit;
    }
  }
}
