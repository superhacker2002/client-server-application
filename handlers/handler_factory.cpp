#include "handler_factory.h"

#include "palindromes_handler.h"
#include "duplications_handler.h"

namespace HandlerFactory {
    std::unique_ptr<IHandler> getHandler(handlerType function) {
        switch (function) {
            case handlerType::duplications:
            return std::make_unique<DuplicationsHandler>();
            case handlerType::palindromes:
            return std::make_unique<PalindromesHandler>();
        }
    }
}
