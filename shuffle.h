
#ifndef SHUFFLE_H
#define SHUFFLE_H

typedef struct Card {
    char value;
    char color;
} Card;
void swap_cards(Card *a, Card *b);
void shuffle_deck(Card *deck, int n);
void generate_shuffled_deck();

#endif
