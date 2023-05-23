/*
 Copyright (c) 2021 Haobin Chen

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <algorithm>
#include <cstring>
#include <des.hh>
#include <iostream>

char* bin_to_string(const unsigned char* input, int nbytes) {
  static char output[MAX_BYTES * 2 + 3];
  char* output_ptr = output;
  sprintf(output, "0x");
  output_ptr += 2;
  for (int i = 0; i < nbytes; i++) {
    sprintf(output_ptr, "%02x", input[i]);
    output_ptr += 2;
  }
  return output;
}

void print_hex(unsigned char* input, unsigned char nbytes) {
  printf("%s", bin_to_string(input, nbytes));
}

void xor_op(const unsigned char* block_a, const unsigned char* block_b,
            unsigned char* output, unsigned char nbytes) {
  for (unsigned char i = 0; i < nbytes; i++) {
    output[i] = block_a[i] ^ block_b[i];
  }
}

void permute(const unsigned char* input, const unsigned char* table,
             unsigned char* output, unsigned char nbytes) {
  const unsigned char* table_cell = table;

  for (unsigned char i = 0; i < nbytes; i++) {
    unsigned char result_byte = 0x00;
    for (unsigned char j = 0; j < 8; j++) {
      // Retrieve result_bit from lookup and store in result_byte
      unsigned char bit_pos = *table_cell % 8;
      unsigned char mask = 0x80 >> bit_pos;
      unsigned char result_bit = (input[*table_cell / 8] & mask) << bit_pos;
      result_byte |= result_bit >> j;

      table_cell++;
    }
    output[i] = result_byte;
  }
}

void des_key_shift(unsigned char* key, unsigned char* output,
                   unsigned char amount) {
  unsigned char mask;

  for (unsigned char i = 0; i < 7; i++) {
    output[i] = (key[i] << amount) | (key[i + 1] >> (8 - amount));
  }

  // Set the bit mask.
  if (amount == 1) {
    mask = 0xEF;
  } else {
    mask = 0xCF;
  }
  output[3] &= mask;                              
  output[3] |= (key[0] >> (4 - amount)) & ~mask;

  // Last bit must borrow from left side of right key.
  if (amount == 1) {
    mask = 0x01;
  } else {
    mask = 0x03;
  }
  output[6] = (key[6] << amount) | ((key[3] >> (4 - amount)) & mask);
}

void des_substitution_box(const unsigned char* input, unsigned char* output) {
  unsigned char input_byte;

  // S-Box 0
  input_byte = (input[0] & 0xFC) >> 2;
  output[0] = sbox_0[input_byte] << 4;

  // S-Box 1
  input_byte = ((input[0] & 0x03) << 4) + ((input[1] & 0xF0) >> 4);
  output[0] = output[0] | sbox_1[input_byte];

  // S-Box 2
  input_byte = ((input[1] & 0x0F) << 2) + ((input[2] & 0xC0) >> 6);
  output[1] = sbox_2[input_byte] << 4;

  // S-Box 3
  input_byte = (input[2] & 0x3F);
  output[1] = output[1] | sbox_3[input_byte];

  // S-Box 4
  input_byte = (input[3] & 0xFC) >> 2;
  output[2] = sbox_4[input_byte] << 4;

  // S-Box 5
  input_byte = ((input[3] & 0x03) << 4) + ((input[4] & 0xF0) >> 4);
  output[2] = output[2] | sbox_5[input_byte];

  // S-Box 6
  input_byte = ((input[4] & 0x0F) << 2) + ((input[5] & 0xC0) >> 6);
  output[3] = sbox_6[input_byte] << 4;

  // S-Box 7
  input_byte = (input[5] & 0x3F);
  output[3] = output[3] | sbox_7[input_byte];
}

void des_feistel(const unsigned char* input, const unsigned char* round_key,
                 unsigned char* output) {
  unsigned char expanded[6];
  unsigned char sbox_output[4];

  permute(input, expansion_permutation, expanded, 6);

  xor_op(expanded, round_key, expanded, 6);
  des_substitution_box(expanded, sbox_output);
  permute(sbox_output, feistel_end_permutation, output, 4);
}

void des_encrypt(unsigned char* block, unsigned char* key,
                 unsigned char* output) {
  unsigned char key_halves_a[7];  // left key + right key
  unsigned char key_halves_b[7];  // Also left key + right key
  unsigned char round_key[6];
  unsigned char feistel_output[4];

  unsigned char* left_block = (unsigned char*)malloc(8);
  unsigned char* right_block = left_block + 4;

  permute(block, initial_permutation_left, left_block, 4);
  permute(block, initial_permutation_right, right_block, 4);

  permute(key, permuted_choice_1, key_halves_a, 7);

  for (unsigned char i = 0; i < 16; i += 2) {
    // Generate key (even round)
    des_key_shift(key_halves_a, key_halves_b, key_shift_amounts[i]);
    permute(key_halves_b, permuted_choice_2, round_key, 6);

    // Round calculation (even round)
    des_feistel(right_block, round_key, feistel_output);
    xor_op(feistel_output, left_block, left_block, 4);

    // Generate key (odd round)
    des_key_shift(key_halves_b, key_halves_a, key_shift_amounts[i + 1]);
    permute(key_halves_a, permuted_choice_2, round_key, 6);

    // Round calculation (odd round)
    des_feistel(left_block, round_key, feistel_output);
    xor_op(feistel_output, right_block, right_block, 4);
  }

  permute(left_block, final_permutation, output, 8);
}