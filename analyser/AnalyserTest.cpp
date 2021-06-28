#include "Analyser.h"

#include <fstream>
#include <iostream>
#include <cstring>

int strcmpi(char const *a, char const *b);

using namespace std;

int main(int argc, char* argv[])
{
   /* switch (argc)
    {
        case 1:
            cout << "Input file is not defined" << endl;
            return 1;
            break;
        case 2:
            cout << "Title list is not defined" << endl;
            return 1;
            break;
    }

    ifstream input(argv[1]);
    if (input.fail())
    {
        cout << "Error open input file" << endl;
        return 1;
    }
*/
    try
    {
        Analyser handler;
        SaxParser parser;
        //parser.Parse(&input, &handler);
        //std::cout << "Successful" << std::endl;
        handler.Hierarchize("../../dumps/book.page");
    }
    catch (SaxParserException& e)
    {
        std::cout << e.what() << " Line: " << e.GetLine() << " Column: " << e.GetColumn() << "  " << e.m_str << std::endl;
    }
    return 0;
}

