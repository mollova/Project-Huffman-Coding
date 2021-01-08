/** \file tests.h
    \brief Unit tests with some needed functions for them
*/

#include "doctest.h"
#include "HuffmansTree.h"

#include <string>
#include <vector>
#include <optional>

using std::string;

int testsCountSymbol (const char& symbol, const string& output)
{
    int counter = 0;
    for (char elem: output)
    {
        if (elem == symbol)
        {
            counter++;
        }
    }

    return counter;
}

std::vector<std::pair<int,std::optional<char>>> testsReadTree (const string treeInfo)
{
    vector<pair<int,optional<char>>> nodesData;

    for (int i=0; i<treeInfo.size(); i++)
    {
        int number = 0;
        while (treeInfo[i] >= '0' && treeInfo[i] <= '9')
        {
            number = number * 10 + (treeInfo[i] - '0');
            i++;
        }

        std::optional<char> symbol;
        if (treeInfo[i] == '|')
        {
            i++;
            symbol.emplace(treeInfo[i]);
            i++;
        }

        nodesData.push_back(std::make_pair(number, symbol));
    }

    return nodesData;
}


TEST_CASE ("Compress")
{
    string input = "abracadabra";

    HuffmansTree tree;
    tree.setCompressMode(input);

    std::pair<string,int> compressed = tree.compress(input);
    string output = compressed.first;
    int degreeOfCompression = compressed.second;

    int num0and1 = testsCountSymbol('0',output) + testsCountSymbol('1',output);
    CHECK (num0and1 == output.size());

    CHECK (degreeOfCompression < 100);
}

TEST_CASE ("Debug compress")
{
    string input = "abracadabra";

    HuffmansTree tree;
    tree.setDebugCompressMode(input);

    std::pair<std::vector<int>,int> debugCompressed = tree.debugCompress(input);
    std::vector<int> output = debugCompressed.first;
    int degreeOfCompression = debugCompressed.second;

    for (int num: output)
    {
        CHECK (num < 256);
    }
    
    CHECK (degreeOfCompression < 100);
}

TEST_CASE ("Decompress")
{
    string input = "abracadabra";

    HuffmansTree treeCompress;
    treeCompress.setCompressMode(input);

    std::pair<string,int> compressedInfo = treeCompress.compress(input);
    string compressed = compressedInfo.first;
    string treeInfo = treeCompress.saveTree();

    HuffmansTree treeDecompress;
    treeDecompress.setDecompressMode(testsReadTree(treeInfo));

    string decompressed = treeDecompress.decompress(compressed);

    CHECK (input == decompressed);
}
