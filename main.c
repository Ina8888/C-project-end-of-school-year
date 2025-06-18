#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "encryption.h"
#include "shuffle.h"
#include "karti.h"

void IGRAJ(void);

void encrypt_cards() {
    FILE *in = fopen("teste.txt", "r");
    FILE *out = fopen("teste.enc", "wb");
    if(!in || !out) { 
        perror("error"); 
        return; 
    }

    uint64_t key = 0x133457799BBCDFF1;

    char value[3], suit[3];
    while (fscanf(in, "%2s %2s", value, suit) == 2) {
        uint64_t card = encode_card(value, suit);
        uint64_t encrypted = encrypt_block(card, key);
        fwrite(&encrypted, sizeof(uint64_t), 1, out);
    }

    fclose(in);
    fclose(out);
}

int main() {
    generate_shuffled_deck();
    encrypt_cards();

    IGRAJ();
    return 0;
}