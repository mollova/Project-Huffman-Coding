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

class HuffmansTree
{
    private:
    struct Node
    {
        int data;
        Node* left;
        Node* right;
        std::optional<char> symbol;

        Node (const int& _data, Node* _left, Node* _right);
    };

    struct PairType: public std::pair<Node*,string>
    {   
        PairType (Node* _first, const string& _second);

        bool operator < (const PairType& b) const;
        bool operator > (const PairType& b) const;
    };
    
    Node* root;
    using priorityQueue = std::priority_queue<PairType, std::vector<PairType>, std::greater<PairType>>;

    std::map<char,int> createFrequencyTable (const string& input) const;
    priorityQueue frequencyTableToQueue (std::map<char,int> frequencyTable) const;
    void createTreeForCompress (priorityQueue frequencyQueue);
    void createTreeForDecompress (const std::vector<std::pair<int,std::optional<char>>>& nodesData);
    std::map<char,string> createCodeTable () const;
    void createCodeTableHelper (Node* currRoot, const string& path, std::map<char,string>& codeTable) const;
    int turnToDecimal (const string& binaryCode, const int& fromIndex, const int& highestPower) const;
    char decompressSymbol (const std::string& binaryCode, int& currIndex, Node* currRoot) const;
    void printDotHelper (std::ostream& out, Node* currRoot) const;
    void saveTreeHelper (std::string& savedTree, Node* currRoot) const;

    public:
    void setCompressMode (const string& input);
    void setDecompressMode (const std::vector<std::pair<int,std::optional<char>>>& nodesData);

    string compress (const string& input) const;
    void debugCompress (const string& input) const;
    std::string decompress (const std::string& binaryCode) const;
    int getDegreeOfCompression (const string& input, const string& compressed)  const;

    void printDot (std::ostream& out) const;
    std::string saveTree () const;
};

#endif
