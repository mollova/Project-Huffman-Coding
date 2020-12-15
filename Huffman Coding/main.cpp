#include <iostream>
#include <fstream>
#include <string>

#include "HufmansTree.h"

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

    HufmansTree tree(input);

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

// #include <optional>
// #include <iostream>

// int main()
// {
//     std::optional<int> oEmpty;
//     std::optional<int> oTwo(2);
//     std::optional<int> oTen(10);

//     std::cout << std::boolalpha;
//     std::cout << (oTen > oTwo) << "\n";
//     std::cout << (oTen < oTwo) << "\n";
//     std::cout << (oEmpty < oTwo) << "\n";
//     std::cout << (oEmpty == std::nullopt) << "\n";
//     std::cout << (oTen == 10) << "\n";
// }