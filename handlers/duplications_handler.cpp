#include "duplications_handler.h"

std::string DuplicationsHandler::handle(const std::string& message) {
    std::string result = message;

    for (size_t i = 0; i < result.size() - 1; ++i) {
        for (size_t j = i + 1; result[j] != '\0'; ++j) {
            if (result[i] != result[j]) {
                break;
            } else {
                result.erase(j, 1);
                --j;
            }
        }
    }
    return "Message without duplicative ssymbols: " + result;
}
