#pragma once
#include "handler_interface.h"

class PalindromsHandler : public IHandler {
 public:
  PalindromsHandler() = default;
  ~PalindromsHandler() = default;
  std::string handle(std::string message) override;
 private:
   bool isPalindrome(std::string word);
};