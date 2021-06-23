#include <stdio.h>
#include <stdlib.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if (index >= fc->n_decks) {
    size_t ori_n_decks = fc->n_decks;
    fc->n_decks = index + 1;
    fc->decks = realloc(fc->decks, fc->n_decks * sizeof(*(fc->decks)));
    for (size_t i = ori_n_decks; i < fc->n_decks; i++) {
      fc->decks[i].n_cards = 0;
      fc->decks[i].cards = NULL;
    }
  }
  fc->decks[index].n_cards++;
  fc->decks[index].cards = realloc(fc->decks[index].cards,
				   fc->decks[index].n_cards * sizeof(*(fc->decks[index].cards)));
  fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  size_t deckCardIndex = 0;
  for (size_t i = 0; i < fc->n_decks; i++) {
    if (fc->decks[i].n_cards > 0) {
      for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
	if(deckCardIndex >= deck->n_cards) {
	  fprintf(stderr, "Run out of deck cards!\n");
	}
	fc->decks[i].cards[j]->value = deck->cards[deckCardIndex]->value;
	fc->decks[i].cards[j]->suit = deck->cards[deckCardIndex]->suit;
      }
      deckCardIndex++;
    }
  }
}
