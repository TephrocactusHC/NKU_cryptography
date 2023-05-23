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
#include <cstdint>
#include <iostream>
#include <random>
#include <string>

#include "utils.hh"
int main(int argc, const char** argv)
{
    std::cout << "Enter string: " << std::endl;
    std::string input;
    getline(std::cin, input);

    const uint32_t distance = random_distance();

    std::transform(input.begin(), input.end(), input.begin(), [distance](char c) -> char {
        if (c != ' ') {
            return (char)(((std::tolower(c) - 'a' + distance) % 25 + 'a'));
        } else {
            return c;
        }
    });

    std::cout << "Result: " << std::endl;
    std::cout << input << std::endl;

    return 0;
}