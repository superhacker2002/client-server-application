#include "duplications_handler.h"

std::string DuplicationsHandler::handle(std::string message) {
    for (size_t i = 0; i < message.size() - 1; ++i) {
        for (size_t j = i + 1; message[j] != '\0'; ++j) {
            if (message[i] != message[j]) {
                break;
            } else {
                message.erase(j, 1);
                --j;
            }
        }
    }
    return message;
}


