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

void shuffle_deck(Card *deck, int n){
    for (int i = n - 1; i > 0; i--) {
        int j;
        swap_cards(&deck[i], &deck[j]);
    }
}

int main(){
    Card deck[52];
    int index = 0;
    
    const char values[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A'};
    const char colors[] = {'C', 'D', 'H', 'S'};
    
    for (int i = 0; i < 13; i++){
        for (int j = 0; j < 4; j++){
            deck[index].value = values[i];
            deck[index].color = colors[j];
            index++;
        }
    }
        shuffle_deck(deck, 52);
    
    FILE *out = fopen("teste.txt", "w");
    if (!out){
        printf("\n error");
        return 1;
    }
    
    for (int i = 0; i < 52; i++){
        fprintf(out, "%c %c", deck[i].value, deck[i].color);
        if (i < 51) fprintf(out, " ");
    }
    
    fclose(out);
    return 0;
} 