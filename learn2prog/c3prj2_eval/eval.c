#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;

  if ((*cp1)->value > (*cp2)->value) {
    return -1;
  } else if ((*cp1)->value < (*cp2)->value) {
    return 1;
  }

  if ((*cp1)->suit > (*cp2)->suit) {
    return -1;
  } else if ((*cp1)->suit < (*cp2)->suit) {
    return 1;
  }
  return 0;
}


suit_t flush_suit(deck_t * hand) {
  size_t count_c = 0;
  size_t count_d = 0;
  size_t count_h = 0;
  size_t count_s = 0;
  for (size_t i = 0; i < hand->n_cards; i++) {
    switch (hand->cards[i]->suit) {
    case SPADES:
      count_s++;
      break;
    case HEARTS:
      count_h++;
      break;
    case DIAMONDS:
      count_d++;
      break;
    case CLUBS:
      count_c++;
      break;
    default:
      break;
    }
  }

  if (count_s >= 5) {
    return SPADES;
  } else if (count_h >= 5) {
    return HEARTS;
  } else if (count_d >= 5) {
    return DIAMONDS;
  } else if (count_c >= 5) {
    return CLUBS;
  }
    
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned max = 0;
  for (size_t i = 0; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for (size_t i = 0; i < n; i++) {
    if (match_counts[i] == n_of_akind) {
      return i;
    }
  }
  exit(EXIT_FAILURE);
}

ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  for (size_t i = 0; i < hand->n_cards; i++) {
    if (match_counts[i] > 1 && (hand->cards[i]->value != hand->cards[match_idx]->value)) {
      return i;
    }
  }
  return -1;
}

int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {
  size_t count = 1;
  if (fs == NUM_SUITS) {
    while (index < hand->n_cards - 1) {
      index++;
      if (hand->cards[index]->value == hand->cards[index-1]->value - 1) {
        count++;
        if (count == n) {
	  return 1;
        }
      } else if (hand->cards[index]->value < hand->cards[index-1]->value - 1) {
          return 0;
      }
    }
  } else {
    //This check is for cases like Ac Ad Kd Qd Jd 0d 2d
    if (hand->cards[index]->suit != fs) {
      return 0;
    }
    size_t index_former = index;
    size_t index_latter = index + 1;
     while (index_latter < hand->n_cards) {
       if (hand->cards[index_latter]->suit != fs) {
	 index_latter++;
	 continue;
       }

        //For Debuging:
	//set args testcase9.txt
	//b evaluate_hand
	//b find_straight
	//b is_straight_at
	
	//Ac ->As Kc Ks Qs Js 0s => fs = s; n = 5
	//Ad ->Kh Qh Jh Js 0h 9h => fs = h; n = 5
        if (hand->cards[index_latter]->value == hand->cards[index_former]->value - 1) {
  	  count++;
	  if (count == n) {
	    return 1;
	  }
	  index_former = index_latter;
	  index_latter++;
        } else if (hand->cards[index_latter]->value < hand->cards[index_former]->value - 1) {
	  return 0;
        }
      }
    }
  return 0;
}

int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs) {
  size_t index_5 = 0;
  for (size_t i = 0; i < hand->n_cards; i++) {
    if (fs == NUM_SUITS) {
      if (hand->cards[i]->value == 5) {
        index_5 = i;
        break;
      }
    } else {
      //As Ac 5c 5s 4s 3s 2s
      if (hand->cards[i]->value == 5 && hand->cards[i]->suit == fs) {
	index_5 = i;
	break;
      }
    }
  }
  if (index_5 == 0) {
    return 0;
  }
  if (fs == NUM_SUITS) {
    if ((hand->cards[index]->value == 14) && (is_n_length_straight_at(hand, index_5, fs, 4))) {
      return 1;
    } else {
      return 0;
    }
  } else {
    if ((hand->cards[index]->value == 14) && (hand->cards[index]->suit == fs) && is_n_length_straight_at(hand, index_5, fs, 4)) {
      return 1;
    } else {
      return 0;
    }
  }
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if (is_ace_low_straight_at(hand, index, fs)) {
    return -1;
  }
  if (is_n_length_straight_at(hand, index, fs, 5)) {
    return 1;
  }
  return 0;
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  hand_eval_t ans;
  ans.ranking = what;
  size_t count = n;
  size_t j = 0;
  for (size_t i = 0; i < n; i++) {
    ans.cards[i] = hand->cards[idx+i];
  }

  //Check n == 0 for case what == NOTHING
  //e.g. Kh Js 9h 6c 3s
  while (count < 5 && j < hand->n_cards) {
    if (n == 0 || hand->cards[j]->value != hand->cards[idx]->value) {
      ans.cards[count] = hand->cards[j];
      count++;
    }
    j++;
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
  hand_eval_t eval1 = evaluate_hand(hand1);
  hand_eval_t eval2 = evaluate_hand(hand2);
  if (eval1.ranking < eval2.ranking) {
    return 1;
  } else if (eval1.ranking > eval2.ranking) {
    return -1;
  }

  for (size_t i = 0; i < 5; i++) {
    if (eval1.cards[i]->value > eval2.cards[i]->value) {
      return 1;
    } else if (eval1.cards[i]->value < eval2.cards[i]->value) {
      return -1;
    }
  }

  return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.

unsigned countSameValue (deck_t * hand, card_t c) {
  unsigned count = 0;
  for (size_t i = 0; i < hand->n_cards; i++) {
    if (hand->cards[i]->value == c.value) {
      count++;
    }
  }
  return count;
}

unsigned * get_match_counts(deck_t * hand) {
  unsigned * matchCounts = malloc (hand->n_cards * sizeof(*matchCounts));
  for (size_t i = 0; i < hand->n_cards; i++) {
    unsigned count = countSameValue(hand, *(hand->cards[i]));
    matchCounts[i] = count;
  }
  return matchCounts;
}





// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
