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

#include <algorithm>
#include <base64.hh>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief to_int function that converts a char to the int it represents.
 * @param c the char to be parsed as int.
 * @return the int contained in c. E.g. '0' returns 0.
 * Throws an exception if the char is not a number.
 */
static inline int to_int(char c) { return c - '0'; }

/**
 * @brief The ZZ class represents a limitless number.
 * Can hold and operate values way larger than 2 to 64.
 */
class ZZ {
 public:
  ZZ(std::string string) {
    if (string.length() > 0) {
      if (string.at(0) == '-' || string.at(0) == '+') {
        positive = string.at(0) == '+';
        string = string.substr(1);  // remove the signal.
      }
      ZZ_raw_value.reserve(string.length());
      for (int i = string.size() - 1; i >= 0; i--) {  // Little endian.
        ZZ_raw_value.push_back(to_int(string[i]));
      }
    } else {
      ZZ_raw_value.push_back(0);  // init with 0 by default.
    }
    remove_leading_zeros();  // call remove_leading_zeros, and not
                             // ZZ_epilogue since the object has not been
                             // completelly initialized.
  }

  ZZ() : ZZ("0") {}  // zero by default.

  ZZ(long long value)
      : ZZ(std::to_string(value)) {
  }  // just call the string constructor since its easier to parse.

  /**
   * @brief Get the base64 encoding of the ZZ.
   *
   * @return std::string
   */
  inline std::string to_base64(void) const {
    std::string out;
    const std::string str = to_string();
    Base64::Encode(str, &out);
    return out;
  }

  /**
   * @brief Decode from base64.
   *
   * @param in
   * @return ZZ
   */
  static inline ZZ from_base64(const std::string& in) {
    std::string out;
    Base64::Decode(in, &out);
    return ZZ(out);
  }

  /**
   * @brief binary_to_ZZ instantiates a ZZ from a binary string
   * representation.
   *
   * @param binary a binary like string. No checking is done to see if it is
   * valid, any char number than 0 and 1 can lead to undefined behavior.
   *
   * @param is_signed if true, as default, the first bit will be interpreted
   as
   * the signal, like any signed integers.
   *
   * @return a ZZ with the value of the binary string.
   */
  static inline ZZ binary_to_ZZ(std::string binary, bool is_signed = true) {
    ZZ number(0);
    if (is_signed) {
      number.positive = binary.at(0) == '0';
      binary = binary.substr(1);
    }

    ZZ power_two(1);
    for (int i = binary.length() - 1; i >= 0; i--) {
      if (binary.at(i) == '1') {
        number += power_two;
      }
      power_two *= 2;
    }
    return number;
  }

  /**
   * @brief static method that generate random ZZs.
   * THIS IS A PSEUDO-RANDOM FUNCTION. DO NOT RELY IN IT BEING COMPLETELY
   * RANDOM.
   *
   * @param size the desired ZZ size.
   *
   * @return a random ZZ with the desired number of digits.
   */
  static inline ZZ random_zz_from_bits(const unsigned long long& length,
                                       bool is_signed = true) {
    ZZ bit = ZZ(2).pow(length);
    ZZ lower = bit;
    ZZ higher = ZZ(2) * bit - 1;
    return ZZ::random_zz(lower, higher);
  }

  /**
   * @brief static method that generate random ZZs.
   * THIS IS A PSEUDO-RANDOM FUNCTION. DO NOT RELY IN IT BEING COMPLETELY
   * RANDOM.
   *
   * @param size the desired ZZ size.
   *
   * @return a random ZZ with the desired number of digits.
   */
  static inline ZZ random_zz(const unsigned long long& length) {
    if (length <= 0) {
      throw std::invalid_argument(
          "[ZZ] {Random ZZ} ->  random_zz size must be "
          "larger or equal to 1.");
    }

    std::ostringstream ss;
    std::random_device rand_gen;
    std::mt19937 seed{rand_gen()};

    while (ss.tellp() < length) {  // add random digits until its larger than
                                   // the desired length.
      ss << seed();
    }

    std::string random_digits = ss.str().substr(0, length);
    return ZZ(random_digits);
  }

  /**
   * @brief random_ZZ generate a random ZZ in desired range,
   * excluding higher. This method may be a little slow compared to the
   others,
   * had'nt any better idea. Does not work with negative numbers. THIS IS A
   * PSEUDO-RANDOM FUNCTION. DO NOT RELY IN IT BEING COMPLETELY RANDOM.
   *
   * @param lower the lower bound, inclusive.
   *
   * @param higher the upper bound, exclusive.
   *
   * @return a random ZZ in range.
   */
  static inline ZZ random_zz(const ZZ& lower, const ZZ& upper) {
    if (lower >= upper) {
      throw std::invalid_argument(
          "[ZZ] {Random ZZ In Range} ->  Lower bound cannot be "
          "bigger or equal to higher bound.");
    }
    if (!lower.is_positive() || !upper.is_positive()) {
      throw std::invalid_argument(
          "[ZZ] {Random ZZ In Range} ->  Only works with "
          "positive ZZs.");
    }

    ZZ diff = upper - lower;

    ZZ random_diff_range = ZZ::random_zz(
        diff.length() +
        1);  // + 1 makes sure the generated value is greater then diff.
    ZZ modR = random_diff_range % diff;

    ZZ random_N = lower + modR;

    return random_N;
  }

  /**
   * @brief operator = copy constructor. Copy the vector and the sign.
   *
   * @param number
   *
   * @return
   */
  inline ZZ& operator=(const ZZ& number) {
    ZZ_raw_value = number.ZZ_raw_value;
    positive = number.positive;
    return *this;
  }

  /**
   * @brief operator + This does NOT return the absolute value.
   *
   * @return the ZZ itself.
   */
  inline ZZ operator+() const { return *this; }

  /**
   * @brief operator - the same as multiplying by -1.
   *
   * @return returns the ZZ with reverted signal.
   */
  inline ZZ operator-() const {
    ZZ number = *this;
    if (!number.is_zero()) {
      number.positive = !number.is_positive();
    }
    return number;
  }

  /*
   * Binary operators.
   */
  /**
   * @brief operator + plus operator. Add one ZZ to this.
   *
   * @param number the number to be added.
   *
   * @return the sum of both ZZs.
   */
  inline ZZ operator+(const ZZ& number) const {
    if (is_positive() && !number.is_positive()) {
      return *this - number.absolute();
    } else if (!is_positive() && number.is_positive()) {
      return (number - absolute());
    }

    if (number.is_zero()) {
      return *this;
    }
    if (is_zero()) {
      return number;
    }
    // At this point, both signs are equal.
    ZZ result = *this;  // not a pointer, since it will hold the result.

    for (int i = 0; i < number.length();
         i++) {  // the numbers will be iterated in normal order, units to
                 // hundreds.
      int digit = number.ZZ_raw_value[i];
      if (i < result.length()) {
        result.ZZ_raw_value[i] += digit;  // sum to it.
      } else {
        result.ZZ_raw_value.push_back(
            digit);  // no digit in this position, add to the end of vector.
      }
    }
    result.do_carry();
    result.ZZ_epilogue();
    return result;
  }

  /**
   * @brief operator - minus operator. Subtracts one ZZ from this.
   *
   * @param number the ZZ to be subtracted.
   *
   * @return the result of the subtraction
   */
  inline ZZ operator-(const ZZ& number) const {
    if (is_positive() && !number.is_positive()) {
      return *this + number.absolute();
    } else if (!is_positive() && number.is_positive()) {
      return -(number + absolute());
    }

    if (number.is_zero()) {
      return *this;
    }
    if (is_zero()) {
      return -number;
    }

    ZZ result;  // result is not a pointer, since it will hold the result.
    const ZZ* smaller;  // pointer to the smaller number. Read only.
    if (length() >= number.length()) {
      result = *this;
      smaller = &number;
    } else {
      result = number;
      smaller = this;
    }

    for (int i = 0; i < smaller->length();
         i++) {  // iterate in normal order, units to hundreds.
      int dif = result.ZZ_raw_value[i] - smaller->ZZ_raw_value[i];
      if (dif < 0) {  // subtraction cannot be done without borrowing.
        // search for a number to borrow.
        for (int j = i + 1; j < result.length(); j++) {
          if (result.ZZ_raw_value[j] ==
              0) {  // replace 0's with 9 until finding a non-zero number.
            result.ZZ_raw_value[j] = 9;
          } else {  // subtract one from it and add 10 to the dif.
            dif += 10;
            result.ZZ_raw_value[j]--;
            break;
          }
        }
      }

      result.ZZ_raw_value[i] = dif;
    }
    result.positive = *this >= number;
    result.ZZ_epilogue();
    return result;
  }

  /**
   * @brief operator * the multiplier operator.
   *
   * Uses Karatsuba Algorithm, see
   * https://en.wikipedia.org/wiki/Karatsuba_algorithm for info.
   *
   * @param number the number to be multiplied by.
   *
   * @return the result of the multiplication.
   */
  inline ZZ operator*(const ZZ& number) const {
    if (is_zero() || number.is_zero()) {
      return ZZ(0);
    }
    if (is_one()) {
      return number;
    }
    if (number.is_one()) {
      return *this;
    }

    if (length() < 10 &&
        number.length() < 10) {  // result can fit in a long long.
      return ZZ(to_long_long() * number.to_long_long());
    }

    int max_length = std::max(length(), number.length());
    int split_point = std::ceil(max_length / 2);  // round down.

    // Apply the Karatsuba algorithm, you should read about it before reading
    // this code.
    std::pair<ZZ, ZZ> split_lhs = split(split_point);
    std::pair<ZZ, ZZ> split_rhs = number.split(split_point);

    ZZ prod_second = split_lhs.second * split_rhs.second;
    ZZ prod_first = split_lhs.first * split_rhs.first;
    ZZ prod_mid = (split_lhs.second + split_lhs.first) *
                  (split_rhs.second + split_rhs.first);  // Reduce plus.

    ZZ first = prod_first.times10(split_point * 2);
    ZZ delta = (prod_mid - prod_first - prod_second).times10(split_point);

    return first + delta + prod_second;
  }

  /**
   * @brief operator / divide one number by number.
   * Keep in mind that the return is a ZZ, so 10 / 4 is 2, not 2.5.
   * If you want the reaminder of a division, see the `%` operator.
   *
   * @param number number to divide by.
   *
   * @return result of division.
   * Throws in case of division by 0.
   */
  inline ZZ operator/(const ZZ& number) const { return divide(number).first; }

  /**
   * @brief operator % module operator. This function does not work with
   * negative numbers.
   * @param number the divisor number.
   * @return the result of the module operator.
   * Throws in case of module by 0.
   */
  inline ZZ operator%(const ZZ& number) const { return divide(number).second; }

  /**
   * @brief pow power method. Solves with Exponentiation by Squaring.
   * Throws an exception in case of 0 to the power of 0 and in case of any
   * number to a negative one. This function is slow with big numbers. If you
   * want to apply a mod after, use mod_pow, since it is faster. See
   * https://en.wikipedia.org/wiki/Exponentiation_by_squaring
   *
   * @param number the desired power.
   *
   * @return THIS to the power of NUMBER.
   */
  inline ZZ pow(ZZ number) const {
    if (is_zero()) {
      return ZZ(0);
    }
    if (number.is_zero()) {
      return ZZ(1);
    }
    if (number.is_one()) {
      return *this;
    }
    if (number.is_odd()) {
      return *this * (*this * *this).pow((number - 1) / 2);
    } else {
      return (*this * *this).pow(number / 2);
    }
  }

  /**
   * @brief mod_pow fast way of doing apower operation followed by module.
   *
   * @see
   * https://en.wikipedia.org/wiki/Modular_exponentiation#Memory-efficient_method
   *
   * @param power the power wanted.
   *
   * @param mod the module wanted.
   *
   * @return this to the power power module mod.
   */
  inline ZZ mod_pow(const ZZ& power, const ZZ& mod) const {
    if (is_zero()) {
      return ZZ(0);
    }
    if (power.is_zero()) {
      return ZZ(1);
    }
    if (power.is_zero()) {
      return ZZ(1);
    }

    ZZ ans = 1;
    ZZ base = *this % mod;
    ZZ pow = power;

    while (pow > 0) {
      // std::cout << pow.to_string() << std::endl;
      if (pow % 2 == 1) ans = (base * pow) % mod;
      base = (base * base) % mod;
      pow /= 2;
    }
    return ans;
  }

  inline ZZ& operator+=(const ZZ& number) {
    *this = *this + number;
    return *this;
  }

  inline ZZ& operator-=(const ZZ& number) {
    *this = *this - number;
    return *this;
  }

  inline ZZ& operator*=(const ZZ& number) {
    *this = *this * number;
    return *this;
  }

  inline ZZ& operator/=(const ZZ& number) {
    *this = *this / number;
    return *this;
  }

  inline ZZ& operator%=(const ZZ& number) {
    *this = *this % number;
    return *this;
  }

  inline ZZ& operator++() {
    *this += 1;
    return *this;
  }

  inline ZZ& operator--() {
    *this -= 1;
    return *this;
  }

  inline ZZ operator++(int) {
    ZZ copy = *this;
    *this += 1;
    return copy;
  }

  inline ZZ operator--(int) {
    ZZ copy = *this;
    *this -= 1;
    return copy;
  }

  inline bool operator<(const ZZ& number) const {
    if (positive != number.positive) {  // oposite signs.
      return !positive;
    }
    if (length() != number.length()) {  // not the same length.
      return length() < number.length();
    }
    // at this point, both are the same length.
    if (positive) {  // both positives.
      return to_string() <
             number.to_string();  // compare string representation.
    }
    return -(*this) > -number;  // both negatives.
  }

  inline bool operator>(const ZZ& number) const {
    return *this >= number && !(*this == number);
  }

  inline bool operator<=(const ZZ& number) const {
    return *this == number || *this < number;
  }

  inline bool operator>=(const ZZ& number) const { return !(*this < number); }

  inline bool operator==(const ZZ& number) const {
    return positive == number.positive && ZZ_raw_value == number.ZZ_raw_value;
  }

  inline bool operator!=(const ZZ& number) const { return !(*this == number); }

  inline friend std::ostream& operator<<(std::ostream& stream,
                                         ZZ const& number) {
    stream << number.to_string();
    return stream;
  }

  inline friend std::istream& operator>>(std::istream& istream, ZZ& number) {
    std::string in;
    istream >> in;
    number = ZZ(in);
    return istream;
  }

  /**
   * @brief to_string methot that creates a string representation of a ZZ.
   *
   * @return a string representing the ZZ.
   */
  inline std::string to_string() const {
    std::stringstream ss;
    if (!is_positive()) {
      ss << '-';
    }
    for (int i = length() - 1; i >= 0; i--) {
      ss << ZZ_raw_value[i];
    }
    return ss.str();
  }

  /**
   * @brief absolute gets the absolute value of a ZZ,
   *
   * @return a ZZ copy, but positive, the absolute value.
   */
  inline ZZ absolute() const {
    ZZ temp = *this;
    temp.positive = true;
    return temp;
  }

  /**
   * @brief times10 method that multiplies the number by 10, n times. Made to
   be
   * fast.
   *
   * @param times how many times it shoud be multiplied by 10. Default is 1.
   *
   * @return the number times 10 n times.
   */
  inline ZZ times10(int times = 1) const {
    ZZ temp = *this;
    for (int i = 0; i < times; i++) {
      temp.ZZ_raw_value.insert(temp.ZZ_raw_value.begin(), 0);
    }
    temp.ZZ_epilogue();
    return temp;
  }

  /**
   * @brief divide10 method that divides the number by 10, n times. Made to
   be
   * fast.
   *
   * @param times how many times it shoud be divided by 10. Default is 1.
   *
   * @return the number divided by 10 n times.
   */
  inline ZZ divide10(int times = 1) const {
    if (times >= length()) {
      return ZZ(0);
    }
    ZZ divided = *this;
    for (int i = 0; i < times; i++) {
      divided.ZZ_raw_value.erase(divided.ZZ_raw_value.begin());
    }
    return divided;
  }

  /**
   * @brief to_binary returns a std::string representation of the ZZ as
   * binary. The length of the string will always be the smallest necessary
   to
   * fit the representation, plus the signed bit. The representation is
   * signed-like, so the first char is 1 if the number is negative, 0 if
   * positive.
   *
   * @return a std::string representation of the ZZ as binary.
   */
  inline std::string to_binary() const {
    std::stringstream ss;

    ZZ copy = absolute();

    while (copy > 0) {
      ss << (copy.is_odd() ? '1' : '0');
      copy /= 2;
    }

    ss << (is_positive() ? '0' : '1');  // Big for signed.

    std::string to_string = ss.str();
    std::reverse(to_string.begin(), to_string.end());
    return to_string;
  }

  /**
   * @brief split splits a ZZ at a desired position.
   *
   * @param split_pos the position to be split at.
   * Keep in mind that this position is from right to left, so spliting the
   * number 123456 at pos 1 will result in 12345 and 6. If the param is not
   in
   * range [0, this.length], it will be capped to it.
   *
   * @return a pair of the result ZZs.
   */
  inline std::pair<ZZ, ZZ> split(long long split_pos) const {
    split_pos = std::min(
        std::max(split_pos, (long long)0),
        (long long)this
            ->length());  // cap values to [0, lengh]. I miss C++ 17 clamp.

    std::vector<int> first_half;
    first_half.reserve(split_pos);

    std::vector<int> second_half;
    second_half.reserve(length() - split_pos);

    for (size_t i = 0; i < length(); i++) {
      int digit = ZZ_raw_value[i];
      if (i > split_pos - 1) {
        first_half.push_back(digit);
      } else {
        second_half.push_back(digit);
      }
    }

    return std::make_pair(ZZ(first_half), ZZ(second_half));
  }

  /**
   * @brief fits_in_long_long method that calculates if a number fits in a
   long
   * long type.
   *
   * @return if number fits in long long type.
   * Uses the length to calculate, since long long max is
   9223372036854775807.
   */
  inline bool fits_in_long_long() const { return length() < 19; }

  /**
   * @brief to_long_long returns a long long representation of this ZZ
   * object. Throws exeption of type std::out_of_range if the number does not
   * fit.
   *
   * @return this ZZ as a long long, if possible.
   */
  inline long long to_long_long() const { return std::stoll(to_string()); }

  /**
   * @brief length method to get the length of given number, counting the
   * digits.
   *
   * @return the length of this ZZ.
   */
  inline size_t length() const { return ZZ_raw_value.size(); }

  /**
   * @brief is_odd simple method to se if a ZZ is odd or not.
   * @return if the number is odd.
   */
  inline bool is_odd() const { return ZZ_raw_value[0] & 1; }

  /**
   * @brief is_even just a negative of is_odd.
   *
   * @return if a number is even. Zero is considered even.
   */
  inline bool is_even() const { return !is_odd(); }

  /**
   * @brief is_zero methot that tests if a number is zero, faster than Number
   ==
   * ZZ(0).
   *
   * @return if the object is 0.
   */
  inline bool is_zero() const { return length() == 1 && ZZ_raw_value[0] == 0; }

  /**
   * @brief is_one method that tests if a number is one, faster than creating
   an
   * object.
   *
   * @return is this object is 1.
   */
  inline bool is_one() const {
    return positive && length() == 1 && ZZ_raw_value[0] == 1;
  }

  /**
   * @brief is_positive methot that returns if this number is positive or
   not.
   *
   * @return if this object has positive value or not.
   */
  inline bool is_positive() const { return positive; }

 private:
  bool positive = true;

  std::vector<int> ZZ_raw_value;

  /**
   * @brief remove_leading_zeros removes all the zeroes to the left of a
   number,
   * so 0008 becomes 8 and 000 becomes 0.
   */
  inline void remove_leading_zeros() {
    for (int i = length() - 1; i >= 1;
         i--) {  // until 1, not 0 so that 0 is represented as {0} and not {}
      if (ZZ_raw_value[i] == 0) {
        ZZ_raw_value.pop_back();
      } else {
        break;
      }
    }
  }

  /**
   * @brief do_carry utility method for addition, that does the carryover.
   *
   * @param start the point to start the parsing, used to recall the function
   * recursively.
   */
  inline void do_carry(int start = 0) {
    for (int i = start; i < length(); i++) {
      if (ZZ_raw_value[i] > 9) {
        ZZ_raw_value[i] -= 10;
        if (i + 1 < length()) {
          ZZ_raw_value[i + 1]++;
        } else {
          ZZ_raw_value.push_back(1);
          return do_carry(i);
        }
      }
    }
  }

  /**
   * @brief ZZ_epilogue is just a method that updates internal stuff,
   * should be called after most internal value update operations.
   */
  inline void ZZ_epilogue() {
    remove_leading_zeros();
    if (is_zero()) {  // prevents -0.
      positive = true;
    }
  }

  /**
   * @brief divide method that contains the division logid.
   *
   * @param number to divide by.
   *
   * @return a pair, the first one is the division quocient, the second the
   * division rest. The division rest is ALWAYS positive, since ISO14882:2011
   * says that the sign of the remainder is implementation-defined. Throws in
   * case of division | module by 0.
   */
  inline std::pair<ZZ, ZZ> divide(const ZZ& number) const {
    if (number.is_zero()) {
      throw std::invalid_argument(
          "[ZZ] {Divide} ->  Division | Module by 0 is undefined.");
    }
    if (number.is_one()) {
      return std::make_pair(*this, ZZ(0));
    }
    if (number == *this) {
      return std::make_pair(ZZ(1), ZZ(0));
    }
    if (number > *this) {
      return std::make_pair(ZZ(0), *this);
    }
    // At this point, we can assume *this is larger than number.

    if (fits_in_long_long() &&
        number.fits_in_long_long()) {  // this makes for huge optization.
      long long llThis = to_long_long();
      long long llNumber = number.to_long_long();
      return std::make_pair(ZZ(llThis / llNumber),
                            ZZ(std::abs(llThis % llNumber)));
    }

    ZZ rest = absolute();  // this number will be modified.
    const ZZ absolute_number = number.absolute();

    ZZ quotient;

    // Iterate lenghtDifference times, decreasing.
    int leength_difference = rest.length() - absolute_number.length();
    while (leength_difference-- >= 0) {
      ZZ subtract_operand = absolute_number.times10(leength_difference);
      while (rest >= subtract_operand) {  // if we can subtract it.
        quotient += ZZ(1).times10(leength_difference);
        rest -= subtract_operand;  // subtract the numbers.
      }
    }
    quotient.positive = positive == number.positive;
    quotient.ZZ_epilogue();
    rest.ZZ_epilogue();
    return std::make_pair(quotient, rest);
  }

  /**
   * @brief ZZ this is a private constructor just to copy the vector.
   * No checking is done to see if the vector is valid or not.
   * An empty vector will result in the object being init with 0.
   *
   * @param vector the object ZZ_raw_value.
   *
   * @param reversed if true, the vector will be read in the reverse order.
   */
  inline ZZ(const std::vector<int>& vector, bool reversed = false) {
    if (vector.size() > 0) {
      ZZ_raw_value = vector;
      if (reversed) {
        std::reverse(ZZ_raw_value.begin(), ZZ_raw_value.end());
      }
    } else {
      ZZ_raw_value.push_back(0);
    }
    ZZ_epilogue();
  }
};

#endif