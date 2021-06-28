#pragma once
#include "GenericPayload.h"
#include <string>
#include <vector>
#include "Definition.h"

//Part of speech

class Pos: public GenericPayload {
    std::string posName;
    std::vector<Definition> definitions;
};
