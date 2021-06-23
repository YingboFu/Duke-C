#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: ./poker [input_file] [number of trials]!\n");
    exit(EXIT_FAILURE);
  }
  unsigned numberOfTrials = 0;
  if (argc == 3) {
    numberOfTrials = atoi(argv[2]);
  } else {
    numberOfTrials = 10000;
  }
  char * inputFile = argv[1];

  FILE * f = fopen(inputFile, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file: %s\n", inputFile);
    exit(EXIT_FAILURE);
  }

  //deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc);
  size_t n_hands = 0;
  future_cards_t fc;
  fc.n_decks = 0;
  fc.decks = NULL;
  future_cards_t * fcp = &fc;
  deck_t ** hands = read_input(f, &n_hands, fcp);

  //deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands);
  deck_t * remainingDeck = build_remaining_deck(hands, n_hands);

  unsigned winCounts[n_hands + 1];
  for (size_t i = 0; i < n_hands + 1; i++) {
    winCounts[i] = 0;
  }

  for (unsigned i = 0; i < numberOfTrials; i++) {
    shuffle(remainingDeck);
    future_cards_from_deck(remainingDeck, fcp);
    //int compare_hands(deck_t * hand1, deck_t * hand2) ;
    //Are those hands Tie?
    /*
    int Tie = 1;
    for (size_t i = 1; i < n_hands; i++) {
      if (compare_hands(hands[0], hands[i]) != 0) {
        Tie = 0;
      }
    }
    if (Tie) {
      winCounts[n_hands] += 1;
      } else { */
    size_t winHandIdx = 0;
    for (size_t i = 1; i < n_hands; i++) {
      if (compare_hands(hands[i], hands[winHandIdx]) > 0) {
	winHandIdx = i;
      }
    }
        
    deck_t * tmp[n_hands-1];
    size_t j = 0;
    for (size_t i = 0; i < n_hands; i++) {
      if (i != winHandIdx) {
	tmp[j] = hands[i];
	j++;
      }
    }
    size_t secondWinHandIdx = 0;
    for (size_t i = 1; i < n_hands-1; i++) {
      if (compare_hands(tmp[i], tmp[secondWinHandIdx]) > 0) {
        secondWinHandIdx = i;
      }
    }
    if (compare_hands(hands[winHandIdx], tmp[secondWinHandIdx]) > 0) {
      winCounts[winHandIdx] += 1; // Win
    } else {
      winCounts[n_hands] += 1; // Tie
    }
  }
  
  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, winCounts[i], numberOfTrials,
	   winCounts[i] / (double)numberOfTrials * 100);
  }
  printf("And there were %u ties\n", winCounts[n_hands]);
  
  free_deck(remainingDeck);
  for (size_t i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);
  for (size_t i = 0; i < fcp->n_decks; i++){
    free(fcp->decks[i].cards);
  }
  free(fcp->decks);
  if (fclose(f) != 0) {
    fprintf(stderr, "Cannot close the file: %s\n", inputFile);
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
