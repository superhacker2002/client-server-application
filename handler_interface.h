#pragma once
#include "string"

class IHandler {
 public:
  IHandler() = default;
  virtual ~IHandler() = default;
  virtual std::string handle(std::string message) = 0;
};
