#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char value;
  char color;
} card; 

const char *values_order = "23456789TJQKA";
const char *suits_order = "CDHS";

typedef struct {
  card hand[100];
  int count;
} player;

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
          return 1;
        }
      }
    }
  }
  // juicy and filled
  return 0;
}

int razdavane(player players[], card cards[]) {
  int card_index = 0;

  while (card_index < 52) {
    for (int i = 0; i < 4; i++) {
      if (card_index >= 52)
        break;

      players[i].hand[players[i].count++] = cards[card_index++];

      if (has_four_of_a_kind(&players[i])) {
        return i;
      }
    }
  }

  return -1;
}


int card_value_index(char value) {
    
  for (int i = 0; i < 13; i++) {
    if (values_order[i] == value) return i;
  }
  return -1;
}

int card_suit_index(char suit) {
    
  for (int i = 0; i < 4; i++) {
    if (suits_order[i] == suit) return i;
  }
  return -1;
}

void sort_hand(card hand[], int count) {
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      int v1 = card_value_index(hand[j].value);
      int v2 = card_value_index(hand[j + 1].value);

      if (v1 < v2 || (v1 == v2 && card_suit_index(hand[j].color) < card_suit_index(hand[j + 1].color))) {
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

void IGRAJ() {
  char golod[10];
    card karti[52];
    player players[4];

    for (int i = 0; i < 4; i++) {
        players[i].count = 0;
    }

    printf("kaji imeto na faila smotanqk: ");
    scanf("%s", golod);
    if (!read_cards("teste.enc", karti)) {
        printf("error\n");
        return;
    }

    int winner = razdavane(players, karti);

    if (winner != -1) {
        printf("\nWinner: %d!\n", winner + 1);
        sort_hand(players[winner].hand, players[winner].count);
        print_player_hand(&players[winner]);
    } else {
        printf("\nno winner\n");
    }
}
