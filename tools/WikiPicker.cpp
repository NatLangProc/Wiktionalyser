#include "WikiPicker.h"
#include <fstream>
#include <iostream>
#include <algorithm>

WikiPicker::WikiPicker()
{
    m_nIndentValue=0;
}

void WikiPicker::ReadTitles(std::string path) {
    std::ifstream input(path);
    std::string str;
    while (std::getline(input, str)) {
        titles.insert(str);
    }
}

void WikiPicker::OnElementBegin(const std::string szName)
{
    if (szName=="page") {
        m_nCountElems++;
        if (m_nCountElems % 10000 == 0) std::cout << m_nCountElems << std::flush << std::endl;
    }
    if (m_nIndentValue == 2 && szName == "title" ) {
        m_nextTitle = true;
    }
    if (m_nIndentValue == 3 && szName == "text" ) {
        m_nextText = true;
    }
    Incr();
}

void WikiPicker::OnCloseSingleElement(const std::string szName)
{
    Decr();
}

void WikiPicker::OnElementEnd(const std::string szName)
{
    Decr();
}

void WikiPicker::OnText(const std::string szValue)
{
    if (m_nextTitle) {
        std::string title;
        if (szValue.find("Thesaurus:")==0)
            title = szValue.substr(10);
        else if (szValue.rfind("/translations")==szValue.length()-13)
            title = szValue.substr(0, szValue.length()-13);
        else title = szValue;
        if (titles.find(title)!=titles.end()) {
            std::cout << szValue << std::endl;
            m_choosedTitle = szValue;
        }
    }
    else if (m_nextText && !m_choosedTitle.empty()) {
        std::string name = m_choosedTitle;
        std::replace( name.begin(), name.end(), '/', '_');
        std::replace( name.begin(), name.end(), ':', '_');
        name+=".page";
        std::ofstream m_file(name);
        m_file << szValue << std::endl;
        m_choosedTitle = "";
    }

    m_nextTitle = false;
    m_nextText = false;
}

inline void WikiPicker::Incr()
{
    m_nIndentValue++;
}

inline void WikiPicker::Decr()
{
    m_nIndentValue--;
    m_nextTitle = false;
    m_nextText = false;
}

