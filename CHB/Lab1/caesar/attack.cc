#include <iostream>
#include <string>

int main(int argc, const char** argv)
{
    std::string input;
    std::cout << "Enter string: " << std::endl;
    getline(std::cin, input);

    for (uint32_t i = 0; i < 26; i ++) {
        std::string guess;
        std::transform(input.begin(), input.end(), std::back_inserter(guess), [i](const char& c) -> char {
            if (c == ' ') {
                return c;
            } else {
                return (char)(((std::tolower(c) - 'a' + i) % 25 + 'a'));
            }
        });

        std::cout << "Guess " << i << ": " << guess << std::endl;
    }
    return 0;
}