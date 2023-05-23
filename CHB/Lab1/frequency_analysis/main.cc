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
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main(int argc, const char** argv)
{
    std::vector<std::pair<char, double>> freq_table = {
        { 'e', 11.67 }, { 't', 9.53 }, { 'o', 8.22 }, { 'i', 7.81 },
        { 'a', 7.73 }, { 'n', 6.71 }, { 's', 6.55 }, { 'r', 5.97 },
        { 'h', 4.52 }, { 'l', 4.3 }, { 'd', 3.24 }, { 'u', 3.21 },
        { 'c', 3.06 }, { 'm', 2.8 }, { 'p', 2.34 }, { 'y', 2.22 },
        { 'f', 2.14 }, { 'g', 2 }, { 'w', 1.69 }, { 'b', 1.58 },
        { 'v', 1.03 }, { 'k', 0.79 }, { 'x', 0.3 }, { 'j', 0.23 },
        { 'q', 0.12 }, { 'z', 0.09 }
    };

    std::string cipher, plain;
    std::cout << "Enter ciphertext: " << std::endl;
    getline(std::cin, cipher);
    std::cout << "Enter plaintext: " << std::endl;
    getline(std::cin, plain);

    std::transform(cipher.begin(), cipher.end(), cipher.begin(), ::tolower);

    std::vector<uint32_t> freq(26, 0);
    std::string guess;
    // Count characters.
    uint32_t total = 0;
    std::for_each(cipher.begin(), cipher.end(), [&freq, &total](const char& c) {
        if (std::isalpha(c)) {
            freq[c - 'a']++;
            total++;
        }
    });
    // Compute frequency.
    std::vector<std::pair<char, double>> freq_cipher; // Frequency of the cipher.
    char c = 'a';
    std::transform(freq.begin(), freq.end(), std::back_inserter(freq_cipher), [total, &c](const uint32_t& count) {
        std::cout << c << ", " << count * 1.0 / total << std::endl;
        return std::make_pair(c++, count * 1.0 / total);
    });

    // Sort.
    std::sort(freq_cipher.begin(), freq_cipher.end(),
        [](const std::pair<char, double>& lhs, const std::pair<char, double>& rhs) -> bool {
            return lhs.second > rhs.second;
        });

    std::vector<char> map(26, 0);

    for (uint32_t i = 0; i < 26; i++) {
        std::cout << freq_cipher[i].first << ", ";
        map[freq_cipher[i].first - 'a'] = freq_table[i].first;
    }

    for (uint32_t i = 0; i < cipher.size(); i++) {
        if (std::isalpha(cipher[i])) {
            guess.push_back(map[cipher[i] - 'a']);
        } else {
            guess.push_back(cipher[i]);
        }
    }
    std::cout << "Result: " << guess << std::endl;

    return 0;
}