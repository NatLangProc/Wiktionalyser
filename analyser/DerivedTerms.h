#pragma once
#include "GenericPayload.h"
#include <string>
#include <vector>

class DerivedTerms: public GenericPayload {
    std::vector<std::string> terms;
};
