#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  int valid_value = c.value >= 2 && c.value <= VALUE_ACE;
  int valid_suit = c.suit >= SPADES && c.suit < NUM_SUITS;
  assert(valid_value && valid_suit);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch (r){
  case STRAIGHT_FLUSH : return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND : return "FOUR_OF_A_KIND";
  case FULL_HOUSE : return "FULL_HOUSE";
  case FLUSH : return "FLUSH";
  case STRAIGHT : return "STRAIGHT";
  case THREE_OF_A_KIND : return "THREE_OF_A_KIND";
  case TWO_PAIR : return "TWO_PAIR";
  case PAIR : return "PAIR";
  default : return "NOTHING";
  }
}

char value_letter(card_t c) {
  if (c.value < VALUE_JACK){
    return '0' + (c.value % 10);
  }
  switch (c.value){
  case VALUE_JACK : return 'J';
  case VALUE_QUEEN : return 'Q';
  case VALUE_KING : return 'K';
  case VALUE_ACE : return 'A';
  default : exit(EXIT_FAILURE);
  }
}

char suit_letter(card_t c) {
  switch (c.suit){
  case SPADES : return 's';
  case HEARTS : return 'h';
  case DIAMONDS : return 'd';
  case CLUBS : return 'c';
  default : exit(EXIT_FAILURE);
  }
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

unsigned letter_value(char let){
  unsigned ilet = let - '0';
  if (ilet < VALUE_JACK){
    if (ilet == 0){
      return 10;
    }
    return ilet;
  }
  switch (let){
  case 'J' : return VALUE_JACK;
  case 'Q' : return VALUE_QUEEN;
  case 'K' : return VALUE_KING;
  case 'A' : return VALUE_ACE;
  default : exit(EXIT_FAILURE);
  }
}

suit_t letter_suit(char suit){
  switch (suit){
  case 's' : return SPADES;
  case 'd' : return DIAMONDS;
  case 'c' : return CLUBS;
  case 'h' : return HEARTS;
  default : exit(EXIT_FAILURE);
  }
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  temp.value = letter_value(value_let);
  temp.suit = letter_suit(suit_let);
  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.value = (c % 13) + 2;
  temp.suit = c / 13;

  assert_card_valid(temp);
  return temp;
}
