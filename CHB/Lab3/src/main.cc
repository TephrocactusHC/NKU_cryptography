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
#include <ZZ.hh>
#include <iostream>
#include <rsa.hh>

int main(int argc, const char** argv) {
  auto key_pair = generate_key_pairs(512);
  const ZZ e = std::get<0>(key_pair);
  const ZZ d = std::get<1>(key_pair);
  const ZZ n = std::get<2>(key_pair);
  const std::string cipher = encrypt("103920940380284023850248058320850328043253253292358902385032850523852332", e, n);
  std::cout << cipher << std::endl;
  std::cout << decrypt(cipher, d, n) << std::endl;

  return 0;
}