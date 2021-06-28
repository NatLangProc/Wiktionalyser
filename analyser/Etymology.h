#pragma once
#include <string>
#include <vector>
#include "GenericPayload.h"
#include "Template.h"

class Etymology: public GenericPayload {
    std::vector<std::vector<Template>> froms;
    std::string further;
};
