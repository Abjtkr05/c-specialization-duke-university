#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "deck.c"
#include "cards.c"
#include "eval.c"

int main(void){
  printf("Testing add_card_to... ");
  deck_t deck;
  deck.cards = malloc(sizeof(*deck.cards));
  deck.n_cards = 0;
  card_t d2 = card_from_letters('2', 'd');
  card_t s4 = card_from_letters('4', 's');
  card_t d6 = card_from_letters('6', 'd');
  add_card_to(&deck, d2);
  add_card_to(&deck, s4);
  assert(deck_contains(&deck, d2) == 1);
  assert(deck_contains(&deck, s4) == 1);
  assert(deck_contains(&deck, d6) == 0);
  printf("PASSED\n");

  printf("Testing add_empty_cards... ");
  card_t *emptyCard1 = add_empty_card(&deck);
  assert(deck.n_cards == 3);
  assert(deck_contains(&deck, *emptyCard1));
  printf("PASSED\n");

  printf("Testing make_deck_exclude... ");
  deck_t exclude;
  exclude.cards = malloc(sizeof(*exclude.cards));
  exclude.n_cards = 0;
  card_t qd = card_from_letters('Q', 'd');
  card_t kh = card_from_letters('K', 'h');
  add_card_to(&exclude, qd);
  add_card_to(&exclude, kh);
  deck_t *d_wo_qd_kh = make_deck_exclude(&exclude);
  assert(d_wo_qd_kh->n_cards = 50);
  assert(deck_contains(d_wo_qd_kh, qd) == 0);
  assert(deck_contains(d_wo_qd_kh, kh) == 0);
  printf("PASSED\n");

  printf("Testing build_remaining_deck... ");
  deck_t hand1;
  hand1.cards = malloc(sizeof(*hand1.cards));
  hand1.n_cards = 0;
  card_t h2 = card_from_letters('2', 'h');
  card_t h3 = card_from_letters('3', 'h');
  add_card_to(&hand1, h2);
  add_card_to(&hand1, h3);
  deck_t **hands = malloc(2*sizeof(deck_t));
  hands[0] = &hand1;
  hands[1] = &exclude;
  deck_t *remainingDeck = build_remaining_deck(hands, 2);
  assert(remainingDeck->n_cards = 48);
  assert(deck_contains(remainingDeck, qd) == 0);
  assert(deck_contains(remainingDeck, kh) == 0);
  assert(deck_contains(remainingDeck, h2) == 0);
  assert(deck_contains(remainingDeck, h3) == 0);
  assert(deck_contains(remainingDeck, s4) == 1);
  assert(deck_contains(remainingDeck, d6) == 1);

  deck_t empty;
  empty.cards = NULL;
  empty.n_cards = 0;
  deck_t unknown;
  unknown.cards = malloc(sizeof(*unknown.cards));
  unknown.n_cards = 1;
  add_empty_card(&unknown);
  deck_t **emptyHands = malloc(2*sizeof(deck_t));
  emptyHands[0] = &empty;
  emptyHands[1] = &unknown;
  deck_t *remainingFromEmpty = build_remaining_deck(emptyHands, 1);
  assert_full_deck(remainingFromEmpty);
  print_hand(remainingFromEmpty);
  printf("PASSED\n");

  printf("Testing get_match_counts... ");
  deck_t hand2;
  hand2.cards = malloc(sizeof(*hand2.cards));
  hand2.n_cards = 0;
  add_card_to(&hand2, card_from_letters('7', 'h'));
  add_card_to(&hand2, card_from_letters('7', 'd'));
  add_card_to(&hand2, card_from_letters('8', 'd'));
  unsigned ans[3] = {2, 2, 1};
  unsigned *check = get_match_counts(&hand2);
  for(int i = 0; i < 3; i++){
    assert(ans[i] == check[i]);
  }
  printf("PASSED\n");

  printf("Testing free_deck... ");
  free_deck(&hand1);
  printf("PASSED\n");
  
  printf("\nAll tests passed!\n");
  return EXIT_SUCCESS;
}
