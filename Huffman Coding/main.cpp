#include <iostream>
#include <fstream>
#include <string>

#include "HuffmansTree.h"

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

    // tree.debugCompress(input);

    std::ifstream toDecompress ("compressed.txt");
    string compressed;
    toDecompress >> compressed;
    toDecompress.close();

    std::ofstream printDecompressed ("decompressed.txt");
    tree.decompress(compressed, printDecompressed);

    std::cout << tree.getDegreeOfCompression(input,compressed) << "%\n";


    return 0;
}
