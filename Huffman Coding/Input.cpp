#include "Input.h"

#include <iostream>
#include <fstream>

// in compress mode a text is being read from a file and a tree is not
void Input::setCompressMode (const std::string& _inputFile)
{
    inputFile = _inputFile;
    treeFile = "";
}

// in debug compress mode the input is the same as in compress mode
void Input::setDebugCompressMode (const std::string& _inputFile)
{
    setCompressMode(_inputFile);
}

// in decompress mode a binary code and a tree are being read from a file
void Input::setDecompressMode (const std::string& _inputFile, const std::string& _treeFile)
{
    inputFile = _inputFile;
    treeFile = _treeFile;
}

// reads the text or the binary code which will be transformed
std::string Input::readInputFile () const
{
    std::ifstream inputStream (inputFile);

    if (!inputStream.good())
    {
        throw "Invalid input file.";
    }

    std::string input;
    char c;

    while (inputStream.get(c))
    {
        input += c;
    }

    return input;
}

// reads a tree saved in a file
std::vector<std::pair<int,std::optional<char>>> Input::readTreeFile () const
{
    std::ifstream treeStream (treeFile);

    if (!treeStream.good())
    {
        throw "Invalid tree file.";
    }

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
