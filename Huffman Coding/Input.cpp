#include "Input.h"

#include <iostream>
#include <fstream>

void Input::setCompressMode (const std::string& _inputFile)
{
    inputFile = _inputFile;
    treeFile = "";
}

void Input::setDecompressMode (const std::string& _inputFile, const std::string& _treeFile)
{
    inputFile = _inputFile;
    treeFile = _treeFile;
}

std::string Input::readInputFile () const
{
    std::ifstream inputStream (inputFile);
    std::string input;
    char c;

    while (inputStream.get(c))
    {
        input += c;
    }

    return input;
}

std::vector<std::pair<int,std::optional<char>>> Input::readTreeFile () const
{
    std::ifstream treeStream (treeFile);

    std::vector<std::pair<int,std::optional<char>>> nodesData;
    char c;
    std::string data;

    while (treeStream.get(c))
    {
        int number = 0;
        while (c >= '0' && c <= '9')
        {
            number = number * 10 + (c - '0');
            treeStream.get(c);
        }

        std::optional<char> symbol;
        if (c == '|')
        {
            treeStream.get(c);
            symbol.emplace(c);
            treeStream.ignore();
        }

        nodesData.push_back(std::make_pair(number, symbol));
    }

    return nodesData;
}