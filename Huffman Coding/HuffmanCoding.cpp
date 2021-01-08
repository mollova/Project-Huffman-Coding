#include "HuffmanCoding.h"

// creates the tree according to the mode
void HuffmanCoding::createTree ()
{
    toTransform = input.readInputFile();

    switch (mode)
    {
        case Modes::compress:
            tree.setCompressMode(toTransform);
            break;

        case Modes::debugCompress:
            tree.setDebugCompressMode(toTransform);
            break;
        
        case Modes::decompress:
            vector<pair<int,optional<char>>> nodesData = input.readTreeFile();
            tree.setDecompressMode(nodesData);
            break;
    }
}

// calls compress function for compress mode, outputs the result and saves the tree
void HuffmanCoding::compress () const
{
    pair<string,int> compressed = tree.compress(toTransform);

    output.outputResult(compressed.first);
    output.printDegreeOfCompression(compressed.second);

    output.saveTree(tree.saveTree());
}

// calls debug compress function for debug compress mode, outputs the result and saves the tree
void HuffmanCoding::debugCompress () const
{
    pair<vector<int>,int> compressed = tree.debugCompress(toTransform);

    output.outputDebugMode(compressed.first);
    output.printDegreeOfCompression(compressed.second);

    output.saveTree(tree.saveTree());
}

// calls decompress function for decompress mode and outputs the result
void HuffmanCoding::decompress () const
{
    string text = tree.decompress(toTransform);
    
    output.outputResult(text);
    output.printAfterDecompress(); 
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
    switch (mode)
    {
        case Modes::compress:
            compress();
            break;

        case Modes::debugCompress:
            debugCompress();
            break;
        
        case Modes::decompress:
            decompress();
            break;
    }

    output.visualizeTree(tree.printDot());
}
