#pragma once
#include <vector>
#include <string>
#include "GenericPayload.h"

int countLeftEq(const std::string& line);
int countRightEq(const std::string& line);

struct Node {
    enum NodeKind {nkLanguage, nkPronunciation, nkEtymology, nkPos,
            nkSynonyms, nkHyponyms, nkDerivedTerms, nkDescendants,
            nkTranslations, nkSeeAlso,nkReferences, nkAnagrams, nkUnknown};
    int level;
    int eqCnt;
    std::string name;
    Node();
    Node(const std::string& line);
    ~Node();
    Node* parent = nullptr;
    std::vector<Node*> childs;
    GenericPayload* payload;
    void link(Node* node);
};
