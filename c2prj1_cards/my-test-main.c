#include "cards.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(void) {

  card_t c1 = {2, SPADES};
  card_t c2 = {VALUE_ACE, HEARTS};
  card_t c3 = {10, DIAMONDS};

  // Test assert_card_valid
  printf("Testing assert_card_valid\n");
  assert_card_valid(c1);
  assert_card_valid(c2);
  assert_card_valid(c3);

  // Test ranking_to_string
  printf("Testing ranking_to_string\n");
  assert(strcmp(ranking_to_string(THREE_OF_A_KIND), "THREE_OF_A_KIND") == 0);

  // Test value_letter
  printf("Testing value_letter\n");
  assert(value_letter(c1) == '2');
  assert(value_letter(c2) == 'A');
  assert(value_letter(c3) == '0');

  // Test suit_letter
  printf("Testing suit_letter\n");
  assert(suit_letter(c1) == 's');
  assert(suit_letter(c2) == 'h');
  assert(suit_letter(c3) == 'd');

  // Test card_from_letters
  printf("Testing card_from_letters\n");
  card_t c1_new = card_from_letters('2', 's');
  assert(c1_new.value == c1.value && c1_new.suit == c1.suit);
  card_t c2_new = card_from_letters('A', 'h');
  assert(c2_new.value == c2.value && c2_new.suit == c2.suit);
  card_t c3_new = card_from_letters('0', 'd');
  
  assert(c3_new.value == c3.value && c3_new.suit == c3.suit);
  
  // Test card_from_num
  printf("Testing card_from_num\n");
  for (int i = 0; i < 52; i++){
    card_from_num(i);
  }
  
  return EXIT_SUCCESS;
}
