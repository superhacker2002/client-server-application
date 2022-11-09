#pragma once

#include "string"

class IHandler {
 public:
  virtual ~IHandler() = default;
  virtual std::string handle(const std::string& message) = 0;
};
