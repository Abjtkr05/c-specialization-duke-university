#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "input.h"

int main(void){
  printf("Testing add_future_card... ");
  future_cards_t *fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;

  deck_t *hand1 = malloc(sizeof(*hand1));
  hand1->cards = NULL;
  hand1->n_cards = 0;
  card_t *eptrh10 = add_empty_card(hand1);
  card_t *eptrh11 = add_empty_card(hand1);

  deck_t *hand2 = malloc(sizeof(*hand2));
  hand2->cards = NULL;
  hand2->n_cards = 0;
  card_t *eptrh20 = add_empty_card(hand2);

  add_future_card(fc, 0, eptrh10);
  add_future_card(fc, 1, eptrh11);
  add_future_card(fc, 0, eptrh20);

  assert(fc->n_decks == 2);
  assert(fc->decks[0].n_cards == 2);
  assert(fc->decks[1].n_cards == 1);  
  printf("PASSED\n");

  printf("Testing future_cards_from_deck... ");
  deck_t *fullDeck = malloc(sizeof(*fullDeck));
  fullDeck->cards = NULL;
  fullDeck->n_cards = 0;
  for(unsigned i = 0; i < 52; i++){
    add_card_to(fullDeck, card_from_num(i));
  }  
  future_cards_from_deck(fullDeck, fc);
  assert((fc->decks[0].cards[0]->suit == fc->decks[0].cards[1]->suit) || (fc->decks[0].cards[0]->value == fc->decks[0].cards[1]->value));
  assert((fc->decks[0].cards[0]->suit != fc->decks[1].cards[0]->suit) || (fc->decks[0].cards[0]->value != fc->decks[1].cards[0]->value));  
  printf("PASSED\n");

  printf("Testing read_input... ");
  FILE *f = fopen("./hands.txt", "r");
  if(f == NULL){
    printf("Could not open\n");
    exit(EXIT_FAILURE);
  }
  size_t n_hands = 0;
  future_cards_t *fc2 = malloc(sizeof(*fc2));
  fc2->decks = NULL;
  fc2->n_decks = 0;
  deck_t **decks = read_input(f, &n_hands, fc2);
  assert(fc2->n_decks == 4);
  assert(fc2->decks[0].n_cards == 2);
  assert(fc2->decks[1].n_cards == 2);
  assert(fc2->decks[2].n_cards == 1);
  assert(fc2->decks[3].n_cards == 1);
  assert(decks[0]->n_cards == 5);
  assert(decks[1]->n_cards == 5);
  printf("\n");
  print_hand(decks[0]);
  printf("\n");
  print_hand(decks[1]);
  printf("\n");
  printf("PASSED\n");

  return EXIT_SUCCESS;
}
