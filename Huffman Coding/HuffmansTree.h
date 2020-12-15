#ifndef __HUFFMANSTREE__HH
#define __HUFFMANSTREE__HH

#include <iostream>
#include <fstream>
#include <string>
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

        Node (const int& _data, Node* _left, Node* _right):
              data {_data}, left {_left}, right {_right} {}
    };

    struct pairType: public std::pair<Node*,string>
    {   
        pairType (Node* _first, const string& _second)
        {
            this->first = _first;
            this->second = _second;
        }

        bool operator < (const pairType& b) const
        {
            return this->first->data < b.first->data;
        }

        bool operator > (const pairType& b) const
        {
            return this->first->data > b.first->data;
        }
    };
    
    using priorityQueue = std::priority_queue<pairType, std::vector<pairType>, std::greater<pairType>>;

    Node* root;

    string alphabet;

    std::map<char,int> createFrequencyTable (const string& input) const;
    priorityQueue frequencyTableToQueue (std::map<char,int> frequencyTable) const;

    void createTree (priorityQueue frequencyQueue);
    std::map<char,string> createCodeTable () const;
    void createCodeTableHelper (Node* currRoot, int& indexAlphabet, const string& path, std::map<char,string>& codeTable) const;

    string getBinaryCode (const string& input) const;
    int turnToDecimal (const string& binaryCode, const int& fromIndex, const int& highestPower) const;

    char decompressSymbol (const std::string& binaryCode, int& currIndex, Node* currRoot) const;

    void printDotHelper (std::ostream& out, Node* currRoot) const;

    public:
    HuffmansTree (const string& input);

    void compress (const string& input, std::ostream& out) const;
    void debugCompress (const string& input) const;
    void decompress (const std::string& binaryCode, std::ostream& out) const;
    int getDegreeOfCompression (const string& input, const string& compressed)  const;

    void printDot (std::ostream& out) const;
};

#endif
