#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * ans = malloc(sizeof(*ans));
  ans->cards = NULL;
  ans->n_cards = 0;

  long len = 0;
  int i = 0;

  while(i < strlen(str)) {
    if (str[i] == ' ' || str[i] == '\n') {
      i++;
      continue;
    }
    if (str[i] == '?') {
        if (strchr(str + i, ' ') != NULL) {
            len = strchr(str + i, ' ') - (str + i);
        } else if ((strchr(str + i, '\n') != NULL)) {
            len = strchr(str + i, '\n') - (str + i);
        } else {
            len = strlen(str) - i;
        }
        char tmp[len + 1];
        strncpy(tmp, str + i, len);
        tmp[len] = '\0';
	size_t idx = atoi(tmp+1);
	card_t * emptyCard = add_empty_card(ans);
	add_future_card(fc, idx, emptyCard);
        i += len;
    } else {
        char tmp[3];
        strncpy(tmp, str + i, 2);
	tmp[2] = '\0';
        card_t c = card_from_letters(tmp[0], tmp[1]);
	add_card_to(ans, c);
        i += 2;
      }
  }
  if (ans->n_cards < 5) {
    fprintf(stderr, "A hand must have at least 5 cards!\n");
    exit(EXIT_FAILURE);
  }
  return ans;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** ans = NULL;
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;
  while((len = getline(&line, &sz, f)) >= 0) {
    deck_t * temp = hand_from_string(line, fc);
    (*n_hands)++;
    ans = realloc(ans, *n_hands * sizeof(*ans));
    ans[*n_hands - 1] = temp;
  }
  free(line);
  return ans;
}
