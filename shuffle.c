#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct Card{
    char value;
    char color;
}Card;

void swap_cards(Card *a,Card *b){
    Card temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle_deck(Card *deck, int n){//random gen
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap_cards(&deck[i], &deck[j]);
    }
}

void generate_shuffled_deck(){
    Card deck[52];
    int index = 0;

    const char values[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    const char colors[] = {'C', 'D', 'H', 'S'};

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            deck[index].value = values[i];
            deck[index].color = colors[j];
            index++;
        }
    }

    shuffle_deck(deck, 52);
    FILE *out = fopen("teste.txt", "w");
    if (!out) {printf("\n error");return;}
    for (int i = 0; i < 52; i++) {
        fprintf(out, "%c %c", deck[i].value, deck[i].color);
        if (i < 51)
            fprintf(out, " ");
    }

    fclose(out);
    printf("gotovo\n");
}
