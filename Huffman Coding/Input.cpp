#include "Input.h"

#include <iostream>
#include <fstream>
#include <exception>

// in compress mode a text is being read from a file and a tree is not
void Input::setCompressMode (const string& _inputFile)
{
    inputFile = _inputFile;
    treeFile = "";
}

// in debug compress mode the input is the same as in compress mode
void Input::setDebugCompressMode (const string& _inputFile)
{
    setCompressMode(_inputFile);
}

// in decompress mode a binary code and a tree are being read from a file
void Input::setDecompressMode (const string& _inputFile, const string& _treeFile)
{
    inputFile = _inputFile;
    treeFile = _treeFile;
}

// reads the text or the binary code which will be transformed
string Input::readInputFile () const
{
    std::ifstream inputStream (inputFile);

    if (!inputStream.good())
    {
        throw std::invalid_argument("Invalid input file.");
    }

    string input;
    char c;

    while (inputStream.get(c))
    {
        input += c;
    }

    inputStream.close();

    return input;
}

// reads a tree saved in a file
vector<pair<int,optional<char>>> Input::readTreeFile () const
{
    std::ifstream treeStream (treeFile);

    if (!treeStream.good())
    {
        throw std::invalid_argument("Invalid tree file.");
    }

    vector<pair<int,optional<char>>> nodesData;
    char c;

    while (treeStream.get(c))
    {
        int number = 0;
        while (c >= '0' && c <= '9')
        {
            number = number * 10 + (c - '0');
            treeStream.get(c);
        }

        optional<char> symbol;
        if (c == '|')
        {
            treeStream.get(c);
            symbol.emplace(c);
            treeStream.ignore();
        }

        nodesData.push_back(std::make_pair(number, symbol));
    }

    treeStream.close();

    return nodesData;
}
