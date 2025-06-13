
#ifndef KARTI_H
#define KARTI_H

typedef struct {
    char value;
    char color;
} card;

typedef struct {
    card hand[100];
    int count;
} player;

int read_cards(const char *filename, card cards[]);
int has_four_of_a_kind(player *p);
int razdavane(player players[], card cards[]);
int card_value_index(char value);
int card_suit_index(char suit);
void sort_hand(card hand[], int count);
void print_player_hand(player *p);
void IGRAJ();

#endif
