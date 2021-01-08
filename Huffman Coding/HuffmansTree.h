/** \file HuffmansTree.h 
    \brief Implemented Huffman tree and its methods
*/

#ifndef __HUFFMANSTREE__HH
#define __HUFFMANSTREE__HH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <optional>

using std::string;
using std::vector;
using std::pair;
using std::optional;

/// Class implementing the tree and the needed member functions
class HuffmansTree
{
    private:
    /// The Node of the tree (symbol is present when the node is a leaf and represents a symbol from the text)
    struct Node
    {
        int data;
        Node* left;
        Node* right;
        optional<char> symbol;

        Node (const int& _data, Node* _left, Node* _right);
    };

    /// Pair of a node and a string containing all the symbols which leaves are children of this node,
    /// two pairs are compaired by the data of their nodes
    struct PairType: public pair<Node*,string>
    {   
        PairType (Node* _first, const string& _second);

        bool operator < (const PairType& b) const;
        bool operator > (const PairType& b) const;
    };
    
    Node* root; ///< the root of the tree

    /// Definition of priority queue of PairType in which the front of the queue will be the smallest element
    using priorityQueue = std::priority_queue<PairType, vector<PairType>, std::greater<PairType>>;


    /// -compress- returns a map with key the symbol and value - it's frequency 
    std::map<char,int> createFrequencyTable (const string& input) const;

    /// -compress- creates and returns the frequency table into prioriry queue 
    /// to always easy access the unprocessed nodes with the least frequency
    priorityQueue frequencyTableToQueue (std::map<char,int> frequencyTable) const;

    /// -compress- constructs the tree for mode compress from the priority queue frequency table
    void createTreeForCompress (priorityQueue frequencyQueue);

    /// -compress- creates and returns a map with key a symbol from the text and value - it's compressed value
    std::map<char,string> createCodeTable () const;
    void createCodeTableHelper (Node* currRoot, const string& path, std::map<char,string>& codeTable) const;

    /// -compress- returns the degree of compression using the length of the input text and its compressed version
    int getDegreeOfCompression (const string& input, const string& compressed) const;

    /// -debug compress- turns the bits of binary code from fromIndex to fromIndex + highestPower into an integer
    int turnToDecimal (const string& binaryCode, const int& fromIndex, const int& highestPower) const;

    /// -decompress- decompresses a single symbol
    char decompressSymbol (const string& binaryCode, int& currIndex, Node* currRoot) const;
    
    void printDotHelper (string& dotInfo, Node* currRoot) const;
    void saveTreeHelper (string& savedTree, Node* currRoot) const;

    public:
    /// -compress- constructs the tree for mode compress from the read text
    void setCompressMode (const string& input);

    /// -debug compress- constructs the tree (same as in compress mode)
    void setDebugCompressMode (const string& input);

    /// -decompress- constructs the tree for mode decompress from the read tree
    void setDecompressMode (const vector<pair<int,optional<char>>>& nodesData); 


    /// -compress- returns a pair of string (the compressed text) and int (the degree of compression)
    pair<string,int> compress (const string& input) const;

    /// -debug compress- returns a pair of vector (the integers computed from the compressed text)
    /// and int (the degree of compression)
    pair<vector<int>,int> debugCompress (const string& input) const;

    /// -decompress- returns a string with the decompressed text
    string decompress (const string& binaryCode) const;


    /// returns a string with the information of the nodes in postorder (left, right, root) traversal 
    string saveTree () const;

    /// returns a string with the content of a file visualizing the tree
    string printDot () const;
};

#endif
