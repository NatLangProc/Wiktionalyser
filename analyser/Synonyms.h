#pragma once
#include "GenericPayload.h"
#include <string>
#include <vector>
#include "Template.h"
#include "Sense.h"

class Synonyms: public GenericPayload {
    std::vector<Template> seeAlso;
    std::vector<Sense> senses;
};
