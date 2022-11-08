#include "handler_factory.h"
#include "handler_interface.h"

std::unique_ptr<IHandler> HandlerFactory::getHandler(handler_type function) {
    switch (function) {
        case duplications:
        return std::make_unique<DuplicationsHandler>();
        case palindromes:
        return std::make_unique<PalindromesHandler>();
    }
}

