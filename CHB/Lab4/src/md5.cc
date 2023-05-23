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
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <md5.hh>
#include <sstream>

void pad_message(uint8_t* input, uint8_t* output, size_t* message_len) {
  // Calculate how many bits remaining.
  uint64_t diff = (MD5_BLOCK_LEN + MD5_MESSAGE_LEN_REMAINDER -
                   *message_len % MD5_BLOCK_LEN) %
                  MD5_BLOCK_LEN;
  // If diff = 0, we set it to 512.
  if (diff == 0) {
    diff = MD5_BLOCK_LEN;
  }

  uint8_t* buffer = new uint8_t[*message_len + diff];
  memset(buffer, 0, *message_len + diff);
  // First we do a memcpy on the output.
  memcpy(static_cast<void*>(buffer), static_cast<void*>(input), *message_len);
  // Pad 1 => 10000000 = 0x80.
  *(buffer + *message_len) = 0x80;
  // Pad zeros.
  memset(buffer + *message_len + 1, 0, diff - 1);
  // Prepare for the output.
  memset(output, 0, MD5_HEADER + *message_len + diff);
  // Get the 64-bit string of the length variable and then pad it to output.
  to_64_bits(*message_len * 8, output + *message_len + diff);
  memcpy(output, buffer, *message_len + diff);
  // Finally set the length of the message.
  *message_len = *message_len + diff + MD5_HEADER;
}

void to_64_bits(const uint64_t& input, uint8_t* output) {
  // Process input in 8-bit batch. We use mask to do this.
  for (uint8_t i = 0; i < 8; i++) {
    *(output + i) = ((mask << (8 * i)) & input) >> (8 * i);
  }
}

void message_digest(unsigned char* input, unsigned char* output,
                    size_t* message_len) {
  assert((*message_len % MD5_BLOCK_LEN == 0) &&
         "Message length is not correct!");

  uint16_t round = *message_len / MD5_BLOCK_LEN;

  uint32_t state[4];
  memcpy(state, initial_buffer, 4 * sizeof(uint32_t));
  // The first round we shall use the initial vector, namely, the four
  // registers.
  for (size_t i = 0; i < round; i++) {
    digest_one_block(input + i * MD5_BLOCK_LEN, state);
  }

  uint32_t* out_ptr = reinterpret_cast<uint32_t*>(output);
  memcpy(out_ptr, state, 4 * sizeof(uint32_t));
}

void digest_one_block(unsigned char* input, uint32_t* state) {
  uint32_t* pointer = reinterpret_cast<uint32_t*>(input);

  uint32_t a = state[0];
  uint32_t b = state[1];
  uint32_t c = state[2];
  uint32_t d = state[3];

  /* Round 1 */
  FF(a, b, c, d, pointer[0], shift_table[0][0], 0xd76aa478);
  FF(d, a, b, c, pointer[1], shift_table[0][1], 0xe8c7b756);
  FF(c, d, a, b, pointer[2], shift_table[0][2], 0x242070db);
  FF(b, c, d, a, pointer[3], shift_table[0][3], 0xc1bdceee);

  FF(a, b, c, d, pointer[4], shift_table[0][0], 0xf57c0faf);
  FF(d, a, b, c, pointer[5], shift_table[0][1], 0x4787c62a);
  FF(c, d, a, b, pointer[6], shift_table[0][2], 0xa8304613);
  FF(b, c, d, a, pointer[7], shift_table[0][3], 0xfd469501);

  FF(a, b, c, d, pointer[8], shift_table[0][0], 0x698098d8);
  FF(d, a, b, c, pointer[9], shift_table[0][1], 0x8b44f7af);
  FF(c, d, a, b, pointer[10], shift_table[0][2], 0xffff5bb1);
  FF(b, c, d, a, pointer[11], shift_table[0][3], 0x895cd7be);

  FF(a, b, c, d, pointer[12], shift_table[0][0], 0x6b901122);
  FF(d, a, b, c, pointer[13], shift_table[0][1], 0xfd987193);
  FF(c, d, a, b, pointer[14], shift_table[0][2], 0xa679438e);
  FF(b, c, d, a, pointer[15], shift_table[0][3], 0x49b40821);

  /* Round 2 */
  GG(a, b, c, d, pointer[1], shift_table[1][0], 0xf61e2562);
  GG(d, a, b, c, pointer[6], shift_table[1][1], 0xc040b340);
  GG(c, d, a, b, pointer[11], shift_table[1][2], 0x265e5a51);
  GG(b, c, d, a, pointer[0], shift_table[1][3], 0xe9b6c7aa);

  GG(a, b, c, d, pointer[5], shift_table[1][0], 0xd62f105d);
  GG(d, a, b, c, pointer[10], shift_table[1][1], 0x2441453);
  GG(c, d, a, b, pointer[15], shift_table[1][2], 0xd8a1e681);
  GG(b, c, d, a, pointer[4], shift_table[1][3], 0xe7d3fbc8);

  GG(a, b, c, d, pointer[9], shift_table[1][0], 0x21e1cde6);
  GG(d, a, b, c, pointer[14], shift_table[1][1], 0xc33707d6);
  GG(c, d, a, b, pointer[3], shift_table[1][2], 0xf4d50d87);
  GG(b, c, d, a, pointer[8], shift_table[1][3], 0x455a14ed);

  GG(a, b, c, d, pointer[13], shift_table[1][0], 0xa9e3e905);
  GG(d, a, b, c, pointer[2], shift_table[1][1], 0xfcefa3f8);
  GG(c, d, a, b, pointer[7], shift_table[1][2], 0x676f02d9);
  GG(b, c, d, a, pointer[12], shift_table[1][3], 0x8d2a4c8a);

  /* Round 3 */
  HH(a, b, c, d, pointer[5], shift_table[2][0], 0xfffa3942);
  HH(d, a, b, c, pointer[8], shift_table[2][1], 0x8771f681);
  HH(c, d, a, b, pointer[11], shift_table[2][2], 0x6d9d6122);
  HH(b, c, d, a, pointer[14], shift_table[2][3], 0xfde5380c);

  HH(a, b, c, d, pointer[1], shift_table[2][0], 0xa4beea44);
  HH(d, a, b, c, pointer[4], shift_table[2][1], 0x4bdecfa9);
  HH(c, d, a, b, pointer[7], shift_table[2][2], 0xf6bb4b60);
  HH(b, c, d, a, pointer[10], shift_table[2][3], 0xbebfbc70);

  HH(a, b, c, d, pointer[13], shift_table[2][0], 0x289b7ec6);
  HH(d, a, b, c, pointer[0], shift_table[2][1], 0xeaa127fa);
  HH(c, d, a, b, pointer[3], shift_table[2][2], 0xd4ef3085);
  HH(b, c, d, a, pointer[6], shift_table[2][3], 0x4881d05);

  HH(a, b, c, d, pointer[9], shift_table[2][0], 0xd9d4d039);
  HH(d, a, b, c, pointer[12], shift_table[2][1], 0xe6db99e5);
  HH(c, d, a, b, pointer[15], shift_table[2][2], 0x1fa27cf8);
  HH(b, c, d, a, pointer[2], shift_table[2][3], 0xc4ac5665);

  /* Round 4 */
  II(a, b, c, d, pointer[0], shift_table[3][0], 0xf4292244);
  II(d, a, b, c, pointer[7], shift_table[3][1], 0x432aff97);
  II(c, d, a, b, pointer[14], shift_table[3][2], 0xab9423a7);
  II(b, c, d, a, pointer[5], shift_table[3][3], 0xfc93a039);

  II(a, b, c, d, pointer[12], shift_table[3][0], 0x655b59c3);
  II(d, a, b, c, pointer[3], shift_table[3][1], 0x8f0ccc92);
  II(c, d, a, b, pointer[10], shift_table[3][2], 0xffeff47d);
  II(b, c, d, a, pointer[1], shift_table[3][3], 0x85845dd1);

  II(a, b, c, d, pointer[8], shift_table[3][0], 0x6fa87e4f);
  II(d, a, b, c, pointer[15], shift_table[3][1], 0xfe2ce6e0);
  II(c, d, a, b, pointer[6], shift_table[3][2], 0xa3014314);
  II(b, c, d, a, pointer[13], shift_table[3][3], 0x4e0811a1);

  II(a, b, c, d, pointer[4], shift_table[3][0], 0xf7537e82);
  II(d, a, b, c, pointer[11], shift_table[3][1], 0xbd3af235);
  II(c, d, a, b, pointer[2], shift_table[3][2], 0x2ad7d2bb);
  II(b, c, d, a, pointer[9], shift_table[3][3], 0xeb86d391);

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
}

std::string to_string(unsigned char* in, size_t* message_len) {
  std::ostringstream stream;

  for (uint8_t i = 0; i < *message_len; i++) {
    stream << "0x" << std::setfill('0') << std::setw(2) << std::hex
           << (int)*(in + i) << " ";
  }
  return stream.str();
}

std::string md5_hash(const std::string& message) {
  uint8_t* input = new uint8_t[message.size()];
  uint8_t padded[1024];
	uint8_t out[16];
  size_t message_len = message.size();
  memcpy(static_cast<void*>(input), static_cast<const void*>(message.c_str()),
         message.size());
	pad_message(input, padded, &message_len);
  message_digest(padded, out, &message_len);

  message_len = 16;
  return to_string(out, &message_len);
}