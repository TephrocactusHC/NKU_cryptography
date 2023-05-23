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

#ifndef ZZ_HH
#define ZZ_HH

#include <string>
#include <utility>

// Big Number Class.

class ZZ {
 private:
  // Raw number stored in a string.
  std::string raw_number;

  bool negative = false;

 public:
  // Create a random big number with the given length.
  explicit ZZ(const long& bit_size, const bool& random = true);

  explicit ZZ(const long long& number) : raw_number(std::to_string(number)) {}

  explicit ZZ(const std::string& raw_number, const bool& negative = false)
      : raw_number(raw_number), negative(negative) {}

  ZZ() : raw_number("0") {}

  // Converts the data back to the number (stored in string.)
  inline std::string to_string(void) const {
    return (negative ? "-" + raw_number : raw_number);
  }

  inline bool is_negative(void) const { return negative; }

  inline bool is_zero(void) const {
    return raw_number.size() == 1 && raw_number[0] == '0';
  }

  inline bool is_one(void) const {
    return raw_number.size() == 1 && raw_number[0] == '1';
  }

  inline long long to_long_long(void) const { return std::stoull(raw_number); }

  ZZ times10(const long long& pow) const;

  ZZ abs(void) const;

  std::pair<ZZ, ZZ> split(const long long& split_point) const;
};

ZZ operator+(const ZZ& lhs, const ZZ& rhs);

ZZ operator-(const ZZ& lhs, const ZZ& rhs);

ZZ operator*(const ZZ& lhs, const ZZ& rhs);

ZZ operator/(const ZZ& lhs, const ZZ& rhs);

ZZ operator%(const ZZ& lhs, const ZZ& rhs);

bool operator>(const ZZ& lhs, const ZZ& rhs);

bool operator<(const ZZ& lhs, const ZZ& rhs);

bool operator>=(const ZZ& lhs, const ZZ& rhs);

bool operator<=(const ZZ& lhs, const ZZ& rhs);

bool operator!=(const ZZ& lhs, const ZZ& rhs);

bool operator==(const ZZ& lhs, const ZZ& rhs);

ZZ pow(const ZZ& lhs, const long& exp);

inline int to_digit(const char& c) { return c - '0'; }

inline char to_char(const int& n) { return n + '0'; }

#endif