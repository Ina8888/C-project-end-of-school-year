#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "karti_maya_variant.h"

const char *values_order = "123456789JQKA";
const char *suits_order = "CDHS";

int read_cards(const char *filename, card cards[]) {

  FILE *f = fopen(filename, "r");
  if (!f) {
    perror("Cannot open file");
    return 0;
  }

  for (int i = 0; i < 52; i++) {
    fscanf(f, " %c %c", &cards[i].value, &cards[i].color);
  }

  fclose(f);
  return 1;
}

int has_four_of_a_kind(player *p) {
  int counts[13] = {0};

  for (int i = 0; i < p->count; i++) {
    for (int j = 0; j < 13; j++) {
      if (p->hand[i].value == values_order[j]) {
        counts[j]++;
        if (counts[j] == 4) {
          return j;
        }
      }
    }
  }
  return -1;
}


int card_point_value(char value) {
  switch (value) {
  case '1':
    return 1;
  case '2':
    return 2;
  case '3':
    return 3;
  case '4':
    return 4;
  case '5':
    return 5;
  case '6':
    return 6;
  case '7':
    return 7;
  case '8':
    return 8;
  case '9':
    return 9;
  case 'J':
    return 10;
  case 'Q':
    return 12;
  case 'K':
    return 15;
  case 'A':
    return 20;
  default:
    return 0;
  }
}

int card_value_index(char value) {

  for (int i = 0; i < 13; i++) {
    if (values_order[i] == value)
      return i;
  }
  return -1;
}

int card_suit_index(char suit) {

  for (int i = 0; i < 4; i++) {
    if (suits_order[i] == suit)
      return i;
  }
  return -1;
}

int total_suit_value(player *p) {
  int sum = 0;
  for (int i = 0; i < p->count; i++) {
    sum += card_suit_index(p->hand[i].color) + 1;
  }
  return sum;
}


int total_hand_value(player *p) {
  int sum = 0;
  for (int i = 0; i < p->count; i++) {
    sum += card_point_value(p->hand[i].value);
  }
  return sum;
}


int razdavane(player players[], card cards[]) {
  int card_index = 0;
  int four_of_kind_players[4] = {-1, -1, -1, -1};

  while (card_index < 52) {
    
    for (int i = 0; i < 4 && card_index < 52; i++) {
      players[i].hand[players[i].count++] = cards[card_index++];
    }

    int winners[4] = {-1, -1, -1, -1};
    int winners_count = 0;

    for (int i = 0; i < 4; i++) {
      int index = has_four_of_a_kind(&players[i]);
      if (index != -1) {
        winners[winners_count++] = i;
        four_of_kind_players[i] = index;
      }
    }

    if (winners_count > 0) {
      int best = winners[0];
      int best_val = four_of_kind_players[best];

      for (int i = 1; i < winners_count; i++) {
        int curr = winners[i];
        int val = four_of_kind_players[curr];
        if (val > best_val) {
          best = curr;
          best_val = val;
        }
      }

      return best;
    }
  }

  int best = 0;
  int best_val = total_hand_value(&players[0]);

  for (int i = 1; i < 4; i++) {
    int val = total_hand_value(&players[i]);
    if (val > best_val) {
      best = i;
      best_val = val;
    } else if (val == best_val) {

      if (total_suit_value(&players[i]) > total_suit_value(&players[best])) {
        best = i;
      }
    }
  }

  return best;
}


void sort_hand(card hand[], int count) {
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      int v1 = card_value_index(hand[j].value);
      int v2 = card_value_index(hand[j + 1].value);

      if (v1 < v2 || (v1 == v2 && card_suit_index(hand[j].color) <
                                      card_suit_index(hand[j + 1].color))) {
        card temp = hand[j];
        hand[j] = hand[j + 1];
        hand[j + 1] = temp;
      }
    }
  }
}


void print_player_hand(player *p) {
  for (int i = 0; i < p->count; i++) {
    printf("card %d: %c%c\n", i + 1, p->hand[i].value, p->hand[i].color);
  }
}

int main() {

  char pile[10];
  card karti[52];
  player players[4];

  for (int i = 0; i < 4; i++) {
    players[i].count = 0;
  }

  printf("kaji imeto na faila: ");
  scanf("%s", pile);

  if (!read_cards(pile, karti)) {
    return 1;
  }

  int winner = razdavane(players, karti);

  printf("\n>>> Победител е играч %d!\n", winner + 1);

  sort_hand(players[winner].hand, players[winner].count);

  print_player_hand(&players[winner]);
  
}