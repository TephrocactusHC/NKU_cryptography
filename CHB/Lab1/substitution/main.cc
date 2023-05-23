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
#include <iostream>
#include <string>
#include <random>
#include <vector>

static std::string substitution_table = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, const char** argv)
{
    std::cout << "Enter string: " << std::endl;
    std::string str;
    getline(std::cin, str);

    std::random_device rd;
    std::mt19937 engine { rd() };
    std::shuffle(substitution_table.begin(), substitution_table.end(), engine);

    std::transform(str.begin(), str.end(), str.begin(), [](char c) -> char {
        if (c != ' ') {
            return substitution_table[std::tolower(c) - 'a'];
        } else {
            return c;
        }
    });

    std::cout << "Result: " << std::endl << str << std::endl;
    return 0;
}