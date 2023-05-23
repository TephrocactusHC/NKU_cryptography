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
#ifndef RSA_HH
#define RSA_HH

#include <ZZ.hh>
#include <tuple>

// Test count.
const unsigned short k = 32;

/**
 * @brief Generate a random prime number of given bits.
 * @note  We are using Miller-Rabin's Prime Testing algorithm.
 * 
 * @param bit 
 * @return ZZ 
 */
ZZ generate_prime_number(const unsigned long long& bit = 512ull);

/**
 * @brief Calculate the inverse modulo of a given number using Extended Euclidean Algorithm.
 * 
 * @param number 
 * @param modulo 
 * @return ZZ 
 */
ZZ calculate_inverse_modulo(const ZZ& number, const ZZ& modulo);

/**
 * @brief Extended Euclidean's Alogrithm.
 * 
 * @param a 
 * @param b 
 * @param x 
 * @param y 
 * @return ZZ 
 */
ZZ extended_euclidean(const ZZ& a, const ZZ& b, ZZ& x, ZZ& y);

/**
 * @brief Generate a key pair (public key and private key).
 * 
 * @param bit_len 
 * @return std::pair<ZZ, ZZ, ZZ>  <e, d, n>
 */
std::tuple<ZZ, ZZ, ZZ> generate_key_pairs(const unsigned long long& bit_len);


std::string encrypt(const std::string& message, const ZZ& e, const ZZ& n);

std::string decrypt(const std::string& cipher, const ZZ& d, const ZZ& n);

/**
 * @brief Check if a big number is prime.
 * 
 * @param n 
 * @return true 
 * @return false 
 */
bool miller_rabin_test(ZZ n);

#endif