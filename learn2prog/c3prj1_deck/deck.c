#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for(int i = 0; i < hand->n_cards; i++) {
    print_card(*(hand->cards[i]));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for(int i = 0; i < d->n_cards; i++) {
    if ((*(d->cards[i])).value == c.value && (*(d->cards[i])).suit == c.suit) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  for(int i = 0; i < d->n_cards; i++) {
    int r1 = (random() % d->n_cards);
    int r2 = (random() % d->n_cards);
    
    card_t * temp = d->cards[r1];
    d->cards[r1] = d->cards[r2];
    d->cards[r2] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  for(unsigned i = 0; i < 52; i++) {
    card_t temp = card_from_num(i);
    if(!deck_contains(d, temp)) {
      printf("The deck does not contain the card: %c%c", temp.value, temp.suit);
      exit(EXIT_FAILURE);
    }
  }
}

void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*(deck->cards)));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(card_t));
  deck->cards[deck->n_cards - 1]->value = c.value;
  deck->cards[deck->n_cards - 1]->suit = c.suit;
}

card_t * add_empty_card(deck_t * deck) {
  card_t empty;
  empty.value = 0;
  empty.suit = 0;
  add_card_to(deck, empty);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * deck = malloc (sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  for (unsigned i = 0; i < 52; i++){
    card_t c = card_from_num(i);
    if (!deck_contains(excluded_cards, c)) {
      add_card_to(deck, c);
    }
  }
  return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t temp;
  deck_t * allHands = &temp;
  allHands->cards = NULL;
  allHands->n_cards = 0;

  for (size_t i = 0; i < n_hands; i++) {
    for (size_t j = 0; j < hands[i]->n_cards; j++) {
      add_card_to(allHands, *(hands[i]->cards[j]));
    }
  }
  deck_t * ans = make_deck_exclude (allHands);

  for (size_t i = 0; i < allHands->n_cards; i++) {
    free(allHands->cards[i]);
  }
  free(allHands->cards);
  
  return ans;
}

void free_deck(deck_t * deck) {
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
