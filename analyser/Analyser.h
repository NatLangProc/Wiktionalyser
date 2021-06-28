#pragma once

#include "SaxParser.h"
#include <fstream>
#include <iostream>
#include <set>

class Analyser: public XSPHandler
{
public:
    Analyser();

    void OnElementBegin(const std::string szName) override;
    void OnElementEnd(const  std::string szName) override;
    void OnCloseSingleElement(const  std::string szName) override;
    void OnText(const std::string szValue) override;
    void ReadTitles(std::string path);

    void Hierarchize(const std::string path);

protected:
    bool SpecialTitle(const std::string& szTitle);
private:
    unsigned int m_nIndentValue;
    bool m_nextTitle = false;
    bool m_nextText = false;
    long m_nCountElems = 0;
    std::string m_choosedTitle;
    std::string m_Dictionary = "en";
    void Incr();
    void Decr();
    void Analyse(const std::string& text);
};
