#pragma once
#include "handler_interface.h"

class DuplicationsHandler : public IHandler {
 public:
    DuplicationsHandler() = default;
    ~DuplicationsHandler() = default;
    std::string handle(const std::string& message) override;
};
