
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdint.h>

extern uint8_t IP[];
extern uint8_t ff[];
extern uint8_t golemo[];
extern uint8_t box[8][4][16];

uint64_t permute(uint64_t input, uint8_t *perm, uint8_t size);
uint32_t func(uint32_t R, uint64_t key);
uint64_t encrypt_block(uint64_t block, uint64_t key);
uint64_t encode_card(const char *value, const char *suit);

#endif
