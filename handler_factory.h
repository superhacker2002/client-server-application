#pragma once

#include "palindromes_handler.h"
#include "duplications_handler.h"
#include <memory>

enum handler_type {
    duplications,
    palindromes
};

class HandlerFactory {
  public:
    std::unique_ptr<IHandler> getHandler(handler_type function);
};
