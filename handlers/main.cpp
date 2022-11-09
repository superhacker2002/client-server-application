// #include "duplications_handler.h"
#include "palindromes_handler.h"
#include <iostream>

int main() {
    // std::string message = "aaabbbbccccddddd, llloooollll mmyy name @@@ iss looooool";
    std::string message = " mom i  love yooy mom   ";
    // DuplicationsHandler handler;
    PalindromesHandler handler;
    std::cout << handler.handle(message);
}