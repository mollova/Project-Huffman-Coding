#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

#include "HuffmansTree.h"
// #include "HuffmanCoding.h"

std::string readInput (std::ifstream& in)
{
    std::string input;
    char c;

    while (in.get(c))
    {
        input += c;
    }

    return input;
}

std::vector<std::pair<int,std::optional<char>>> readTree (std::ifstream& in)
{
    std::vector<std::pair<int,std::optional<char>>> nodesData;
    char c;
    std::string data;

    while (in.get(c))
    {
        int number = 0;
        while (c >= '0' && c <= '9')
        {
            number = number * 10 + (c - '0');
            in.get(c);
        }

        std::optional<char> symbol;
        if (c == '|')
        {
            in.get(c);
            symbol.emplace(c);
            in.ignore();
        }

        nodesData.push_back(std::make_pair(number, symbol));
    }

    return nodesData;
}

int main ()
{
    std::ifstream in ("input.txt");
    std::string input = readInput(in);

    HuffmansTree tree(input);

    std::ofstream treeVisualize ("myTree.dot");
    tree.printDot(treeVisualize);
    treeVisualize.close();

    std::ofstream out ("compressed.txt");
    tree.compress(input,out);
    out.close();

    tree.debugCompress(input);

    std::ifstream toDecompress ("compressed.txt");
    string compressed;
    toDecompress >> compressed;
    toDecompress.close();

    std::ofstream printDecompressed ("decompressed.txt");
    // tree.decompress(compressed, printDecompressed);

    std::cout << tree.getDegreeOfCompression(input,compressed) << "%\n";

    std::ofstream savedTree ("savedTree.txt");
    tree.saveTree(savedTree);
    savedTree.close();

    std::ifstream readSavedTree ("savedTree.txt");
    std::vector<std::pair<int,std::optional<char>>> nodesData = readTree(readSavedTree);

    HuffmansTree tree2(nodesData);
    tree2.decompress(compressed, printDecompressed);

    return 0;
}
