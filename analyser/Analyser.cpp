#include "Analyser.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

Analyser::Analyser()
{
    m_nIndentValue=0;
}

void Analyser::OnElementBegin(const std::string szName)
{
    if (szName=="page") {
        m_nCountElems++;
        if (m_nCountElems % 100000 == 0) std::cout << m_nCountElems << std::flush << std::endl;
    }
    if (m_nIndentValue == 2 && szName == "title" ) {
        m_nextTitle = true;
    }
    if (m_nIndentValue == 3 && szName == "text" ) {
        m_nextText = true;
    }
    Incr();
}

void Analyser::OnCloseSingleElement(const std::string szName)
{
    Decr();
}

void Analyser::OnElementEnd(const std::string szName)
{
    Decr();
}

std::string ClearRight(const std::string& line) {
    std::string result = line;
    long pos = result.rfind("</nowiki><br><nowiki>");
    if (pos==result.length()-21) result = result.substr(0,pos);
    pos = result.rfind("<br>");
    if (pos==result.length()-4) result = result.substr(0,pos);
    pos = result.find("<!-");
    if (pos>=0)
        result = result.substr(0,pos);
    pos = result.length()-1;
    while (pos>=0 && (result[pos]==' ' || result[pos]=='\t')) {
        pos--;
    }
    result = result.substr(0,pos+1);
    return result;
}

void Analyser::Analyse(const std::string& text) {
    std::stringstream lines(text);
    std::string line1;
    while (std::getline(lines, line1)) {
        std::string line = ClearRight(line1);
        if (line.empty() || line[0]!='=') continue;
        int leftCnt = countLeftEq(line);
        int rightCnt = countRightEq(line);
        if (leftCnt==1) std::cout<< /*"error = " << line <<*/ m_choosedTitle <<std::endl;
        if (rightCnt==0)
            std::cout<<"error Trim " << line << ":"<< line1 << ":" << m_choosedTitle << std::endl;
        if (abs(leftCnt-rightCnt)>1)
            std::cout<<"error = =" << line <<":" << m_choosedTitle << std::endl;
    }
}

bool Analyser::SpecialTitle(const std::string& szTitle) {
    if (m_Dictionary=="en") {
        if (szTitle.find("Wiktionary:") == 0) return true;
        if (szTitle.find("Appendix:") == 0) return true;
        if (szTitle.find("Index:") == 0) return true;
        if (szTitle.find("Rhymes:") == 0) return true;
        if (szTitle.find("Template:") == 0) return true;
        if (szTitle.find("Thesaurus:") == 0) return true;
        if (szTitle.find("Thread:User talk:") == 0) return true;
        if (szTitle.find("Citations:") == 0) return true;
    } else if (m_Dictionary=="pl") {
        if (szTitle.find("Wikisłownik:") == 0) return true;
        if (szTitle.find("Aneks:") == 0) return true;
        if (szTitle.find("Indeks:") == 0) return true;
        if (szTitle.find("Portal:") == 0) return true;
        if (szTitle.find("Szablon:") == 0) return true;
        if (szTitle.find("Moduł:Wikisłownikarz:") == 0) return true;
    }
    return false;
}

void Analyser::OnText(const std::string szValue)
{
    if (m_nextTitle) {
        m_choosedTitle = szValue;
    }
    else if (m_nextText && !m_choosedTitle.empty() && !SpecialTitle(m_choosedTitle)) {
        Analyse(szValue);
        m_choosedTitle = "";
    }

    m_nextTitle = false;
    m_nextText = false;
}

inline void Analyser::Incr()
{
    m_nIndentValue++;
}

inline void Analyser::Decr()
{
    m_nIndentValue--;
    m_nextTitle = false;
    m_nextText = false;
}

void Analyser::Hierarchize(const std::string path) {
    std::ifstream input(path);
    std::string line1;
    Node* root = new Node;
    Node* lastNode;
    lastNode = root;
    while (std::getline(input, line1)) {
        std::string line = ClearRight(line1);
        if (line.empty() || line[0]!='=') continue;
        if (line.length()<=2 || line[1]!='=') continue;
        Node* child = new Node(line);
        std::cout << child->eqCnt << child->name << std::endl;
        child->link(lastNode);
        lastNode = child;
    }
    delete root;
}
