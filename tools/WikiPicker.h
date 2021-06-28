#pragma once

#include "SaxParser.h"
#include <fstream>
#include <iostream>
#include <set>

class WikiPicker: public XSPHandler
{
public:
    WikiPicker();

    void OnElementBegin(const std::string szName) override;
    void OnElementEnd(const  std::string szName) override;
    void OnCloseSingleElement(const  std::string szName) override;
    void OnText(const std::string szValue) override;
    void ReadTitles(std::string path);
protected:
    std::set<std::string> titles;
private:
    unsigned int m_nIndentValue;
    bool m_nextTitle = false;
    bool m_nextText = false;
    long m_nCountElems = 0;
    std::string m_choosedTitle = "";
    void Incr();
    void Decr();
};
