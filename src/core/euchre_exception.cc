//
// Created by ghoey on 5/4/2021.
//
#include "core/euchre_exception.h"

namespace euchre {

    EuchreException::EuchreException(std::string &msg) : msg_(msg) {
    }
    std::string EuchreException::GetMessage() {
        return msg_;
    }
}

