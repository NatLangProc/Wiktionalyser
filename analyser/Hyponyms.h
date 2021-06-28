#pragma once
#include "GenericPayload.h"
#include <vector>
#include "Sense.h"

class Hyponyms: public GenericPayload {
    std::vector<Sense> senses;
};
