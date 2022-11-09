#include "palindromes_handler.h"

std::string PalindromesHandler::handle(std::string message) {
    size_t i = 0, palindromes_counter = 0, word_length = 0;
    while (1) {
        if (message[i] == ' ' || message[i] == '\0') {
            if (i != 0 && message[i - 1] != ' ') {
                std::string word = message.substr(i - word_length, word_length);
                if (isPalindrome(word)) {
                    ++palindromes_counter;
                }
                word_length = 0;
            }
        } else {
            ++word_length;
        }
        if (message[i] == '\0') break;
        ++i;
    }
    return std::to_string(palindromes_counter);
}

bool PalindromesHandler::isPalindrome(std::string word) {
    bool is_palindrome = false;
    std::string reversed_word = word;
    std::reverse(reversed_word.begin(), reversed_word.end());
    if (word == reversed_word) {
        is_palindrome = true;
    }
    return is_palindrome;
}
