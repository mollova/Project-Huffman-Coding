/** \file HuffmanCoding.h 
    \brief Runs Huffman coding
*/

#ifndef __HUFFMANCODING__HH
#define __HUFFMANCODING__HH

#include "HuffmansTree.h"
#include "Input.h"
#include "Output.h"

#include <fstream>
#include <string>

using std::string;
using std::vector;
using std::pair;
using std::optional;

/// The possible modes of the program
enum Modes {compress, debugCompress, decompress};

/// Class containing the main components (information) needed for running the algorithm
/// used to control the calling of the right functions for each mode
class HuffmanCoding
{
    private:
    Modes mode; ///< the mode in which the program is called

    HuffmansTree tree; ///< the tree for compressing/decompressing
    Input input; ///< the input for that call of the programm 
    Output output; ///< the input for that call of the progra

    string toTransform; ///< the text/binary code which will be compressed/decompressed

    void createTree ();
    void compress () const;
    void debugCompress () const;
    void decompress () const;

    public:
    HuffmanCoding (const Modes& _mode, const Input& _input, const Output& _output);

    void runHuffmanCoding () const;
};

#endif
