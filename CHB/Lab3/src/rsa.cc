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
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <rsa.hh>

ZZ generate_prime_number(const unsigned long long& bit_length) {
  ZZ number;

  do {
    number = ZZ::random_zz(bit_length);
  } while (miller_rabin_test(number) == false);

  return number;
}

bool miller_rabin_test(ZZ n) {
  // Must have ODD n greater than THREE
  if (n == 2 || n == 3) return true;
  if (n <= 1 || n % 2 == 0) return false;

  // Write n-1 as d*2^s by factoring powers of 2 from n-1
  int s = 0;
  for (ZZ m = n - 1; m % 2 == 0; ++s, m /= 2)
    ;  // loop

  ZZ d = (n - 1) / (1 << s);

  for (int i = 0; i < k; ++i) {
    ZZ a = ZZ::random_zz(2, n - 2);
    ZZ x = a.mod_pow(d, n);

    if (x == 1 || x == n - 1) continue;

    for (int r = 1; r <= s - 1; ++r) {
      x = x.mod_pow(2, n);
      if (x == 1) return false;
      if (x == n - 1) goto LOOP;
    }

    return false;
  LOOP:
    continue;
  }

  // n is *probably* prime
  return true;
}

ZZ extended_euclidean(const ZZ& a, const ZZ& b, ZZ& x, ZZ& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }

  ZZ x1, y1, gcd = extended_euclidean(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return gcd;
}

ZZ calculate_inverse_modulo(const ZZ& number, const ZZ& modulo) {
  ZZ x1, x2;
  extended_euclidean(number, modulo, x1, x2);
  // x2 is not used :)
  // Make sure it is a positive number.
  return (modulo + x1) % modulo;
}

std::tuple<ZZ, ZZ, ZZ> generate_key_pairs(const unsigned long long& bit_len) {
  ZZ e, p, q;

  if (std::filesystem::exists("../rsa.txt")) {
    std::ifstream key("../rsa.txt");
    std::string a, b, c;
    std::getline(key, a);
    std::getline(key, b);
    std::getline(key, c);
    e = ZZ(a);
    p = ZZ(b);
    q = ZZ(c);
  } else {
    e = 3;
    p = generate_prime_number(bit_len);
    q = generate_prime_number(bit_len);
  }

  // Generate n.
  ZZ n = p * q;
  ZZ phi_n = (p - 1) * (q - 1);

  // Calculate inverse modulo.
  ZZ d = calculate_inverse_modulo(e, phi_n);
  std::fstream key("../rsa.txt");
  key << e.to_string() << std::endl
      << p.to_string() << std::endl
      << q.to_string() << std::endl;

  return std::make_tuple(e, d, n);
}

std::string encrypt(const std::string& message, const ZZ& e, const ZZ& n) {
  ZZ message_converted(message);

  return message_converted.mod_pow(e, n).to_base64();
}

std::string decrypt(const std::string& cipher, const ZZ& d, const ZZ& n) {
  std::string cipher_decoded;
  Base64::Decode(cipher, &cipher_decoded);

  ZZ message_converted(cipher_decoded);
  std::cout << message_converted << std::endl;

  return message_converted.mod_pow(d, n).to_string();
}