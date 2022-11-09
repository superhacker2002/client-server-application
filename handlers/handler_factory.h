#pragma once

#include <memory>
#include "handler_interface.h"

namespace HandlerFactory {
    enum struct handlerType {
        duplications = 0,
        palindromes = 1
    };
    std::unique_ptr<IHandler> getHandler(handlerType function);
};
