#include "WikiDivider.h"
#include <iostream>

WikiDivider::WikiDivider()
{
    m_file = new std::ofstream("000000.xml");
    m_nIndentValue=0; m_bValue=false; m_bOpen=false;
    m_IndentString="  ";
    m_nPageCount = 0;
    m_nFileCount = 0;
}

void WikiDivider::DoIndent()
{
    for (unsigned int i=0; i < m_nIndentValue; i++)
    {
        Output(m_IndentString);
    }
}


void WikiDivider::NextFile() {
    Output("</mediawiki>");
    m_file->close();
    m_nFileCount++;
    std::cout << m_nFileCount << std::endl;
    std::string name = std::to_string(m_nFileCount);
    m_file->open(std::string(6 - name.length(), '0') + name+".xml");
    Output("<mediawiki xmlns=\"http://www.mediawiki.org/xml/export-0.10/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.mediawiki.org/xml/export-0.10/ http://www.mediawiki.org/xml/export-0.10.xsd\" version=\"0.10\" xml:lang=\"en\">\n");
}

void WikiDivider::OnElementBegin(const std::string szName)
{
    if (m_nIndentValue == 1 && szName == "page" ) {
        m_nPageCount++;
        if (m_nPageCount % 100000 == 0) NextFile();
    }
    if (m_bOpen)
        Output(">");
    DoBreakLine();
    DoIndent();
    Output("<"); Output(ToXML(szName));
    m_bOpen=true;
    m_bValue=false;
    Incr();
}

void WikiDivider::OnCloseSingleElement(const std::string szName)
{
    Output("/>");
    Decr();
    m_bOpen=false;
}

void WikiDivider::OnElementEnd(const std::string szName)
{
    if (m_bOpen)
        Output(">");
    if (!m_bValue && !m_bOpen)
    {
        DoBreakLine();
        Decr();
        DoIndent();
    }
    else
    {
        Decr();
    }
    Output("</"); Output(ToXML(szName)); Output(">");
    m_bOpen=false;
    m_bValue=false;
}

void WikiDivider::OnAttribute(const std::string szName, const std::string szValue)
{
    Output(" "); Output(ToXML(szName)); Output("="); Output("\"");
    Output(ToXML(szValue)); Output("\"");
}

void WikiDivider::OnCDATA(const std::string szValue)
{
    if (m_bOpen)
        Output(">");
    DoBreakLine();
    DoIndent();
    Output("<![CDATA[ "); Output(ToXML(szValue)); Output(" ]]>");
    m_bValue=false;
    m_bOpen=false;
}

void WikiDivider::OnComment(const std::string szText)
{
    if (m_bOpen)
        Output(">");
    DoBreakLine();
    DoIndent();
    Output("<!-- "); Output(ToXML(szText)); Output(" -->");
    m_bValue=false;
    m_bOpen=false;
}

void WikiDivider::OnDeclaration(const std::string szVersion, const std::string szEncoding, const std::string szStandAlone)
{
    DoIndent();
    Output("<?xml ");
    if (!szVersion.empty())
    {Output("version=\""); Output(ToXML(szVersion)); Output("\"");}
    if (!szEncoding.empty())
    {Output(" encoding=\""); Output(ToXML(szEncoding)); Output("\"");}
    if (!szStandAlone.empty())
    {Output("standalone=\""); Output(ToXML(szStandAlone)); Output("\"");}
    Output(" ?>");
}

void WikiDivider::OnProcessing(const std::string szValue)
{
    if (m_bOpen)
        Output(">");
    DoBreakLine();
    DoIndent();
    Output("<? "); Output(ToXML(szValue)); Output(" ?>");
    DoBreakLine();
}

void WikiDivider::OnText(const std::string szValue)
{
    if (m_bOpen)
    {
        Output(">");
        m_bValue=true;
    }
    else
    {
        DoIndent();
    }
    Output(ToXML(szValue));
    m_bOpen=false;
}

void WikiDivider::SetIndentAsTab()
{
    m_IndentString = "\t";
}

void WikiDivider::SetIndentAsBlank(int n)
{
    m_IndentString = "";
    for (int i=0; i<n; i++)
        m_IndentString += ' ';
}

inline void WikiDivider::DoBreakLine()
{
    Output("\n");
}

inline void WikiDivider::Incr()
{
    m_nIndentValue++;
}

inline void WikiDivider::Decr()
{
    m_nIndentValue--;
}

