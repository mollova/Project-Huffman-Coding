#include "HuffmanCoding.h"

// creates the tree according to the mode
void HuffmanCoding::createTree ()
{
    toTransform = input.readInputFile();

    if (mode == Modes::compress)
    {
        tree.setCompressMode(toTransform);
    }
    else if (mode == Modes::debugCompress)
    {
        tree.setDebugCompressMode(toTransform);
    }
    else
    {   
        std::vector<std::pair<int,std::optional<char>>> nodesData = input.readTreeFile();
        tree.setDecompressMode(nodesData);
    }   
}

// calls compress function for compress mode, outputs the result and saves the tree
void HuffmanCoding::compress () const
{
    std::pair<std::string,int> compressed = tree.compress(toTransform);

    output.outputResult(compressed.first);
    output.printDegreeOfCompression(compressed.second);

    output.saveTree(tree.saveTree());
}

// calls debug compress function for debug compress mode, outputs the result and saves the tree
void HuffmanCoding::debugCompress () const
{
    std::pair<std::vector<int>,int> compressed = tree.debugCompress(toTransform);

    output.outputDebugMode(compressed.first);
    output.printDegreeOfCompression(compressed.second);

    output.saveTree(tree.saveTree());
}

// calls decompress function for decompress mode and outputs the result
void HuffmanCoding::decompress () const
{
    std::string text = tree.decompress(toTransform);
    output.outputResult(text); 
}

HuffmanCoding::HuffmanCoding (const Modes& _mode, const Input& _input, const Output& _output)
{
    mode = _mode;
    input = _input;
    output = _output;

    createTree();
}

// calls the appropriate function according to the mode and visualizes the tree
void HuffmanCoding::runHuffmanCoding () const
{
    if (mode == Modes::compress)
    {
        compress();
    }
    else if (mode == Modes::debugCompress)
    {
        debugCompress();
    }
    else
    {
        decompress();
    }

    output.visualizeTree(tree.printDot());
}
