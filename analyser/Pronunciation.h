#pragma once
#include "GenericPayload.h"
#include "Template.h"
#include <vector>

class Pronunciation: public GenericPayload {
    std::vector<std::vector<Template>> IPA;
    std::vector<Template> audio;
    Template rhymes;
    Template homophones;
};
