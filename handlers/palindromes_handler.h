#pragma once
#include "handler_interface.h"

class PalindromesHandler : public IHandler {
 public:
  PalindromesHandler() = default;
  ~PalindromesHandler() = default;
  std::string handle(const std::string& message) override;
 private:
   bool isPalindrome(std::string&& word);
};