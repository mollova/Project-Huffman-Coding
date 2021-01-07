#ifndef __HUFFMANCODING__HH
#define __HUFFMANCODING__HH

#include "HuffmansTree.h"
#include "Input.h"
#include "Output.h"

#include <fstream>
#include <string>

using std::string;

enum Modes {compress, debugCompress, decompress};

class HuffmanCoding
{
    private:
    Modes mode;

    HuffmansTree tree;
    Input input;
    Output output;

    std::string toTransform;

    void createTree ();
    void compress () const;
    void debugCompress () const;
    void decompress () const;

    public:
    HuffmanCoding (const Modes& _mode, const Input& _input, const Output& _output);

    void runHuffmanCoding () const;
};

#endif
