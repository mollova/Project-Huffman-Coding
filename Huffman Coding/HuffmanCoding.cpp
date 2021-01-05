#include "HuffmanCoding.h"

void HuffmanCoding::createTree ()
{
    toTransform = input.readInputFile();

    if (mode == Modes::compress)
    {
        tree.setCompressMode(toTransform);
    }
    else
    {   
        std::vector<std::pair<int,std::optional<char>>> nodesData = input.readTreeFile();
        tree.setDecompressMode(nodesData);
    }   
}

void HuffmanCoding::compress () const
{
    std::string binary = tree.compress(toTransform);
    output.outputResult(binary);
    output.saveTree(tree.saveTree());
}

void HuffmanCoding::compressDebug () const
{

}

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

void HuffmanCoding::runHuffmanCoding () const
{
    if (mode == Modes::compress)
    {
        compress();
    }
    else
    {
        decompress();
    }

    std::string printTreeFile = "myTree.dot";
    std::ofstream printTree(printTreeFile);
    tree.printDot(printTree);
}
