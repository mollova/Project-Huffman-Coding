#include "HuffmansTree.h"

#include <stack>
#include <cmath>
#include <exception>

HuffmansTree::Node::Node (const int& _data, Node* _left, Node* _right):
                          data {_data}, left {_left}, right {_right} {}

HuffmansTree::PairType::PairType (Node* _first, const string& _second)
{
    this->first = _first;
    this->second = _second;
}

bool HuffmansTree::PairType::operator < (const PairType& b) const
{
    return this->first->data < b.first->data;
}

bool HuffmansTree::PairType::operator > (const PairType& b) const
{
    return this->first->data > b.first->data;
}

// -compress- returns a map with key the symbol and value - it's frequency
std::map<char,int> HuffmansTree::createFrequencyTable(const string& input) const
{
    std::map<char,int> frequencyTable;

    for (char symbol : input)
    {
        frequencyTable[symbol]++;
    }

    return frequencyTable;
}

// -compress- (re)turns the frequency table into prioriry queue to easy access the nodes with the least frequency
HuffmansTree::priorityQueue HuffmansTree::frequencyTableToQueue(std::map<char,int> frequencyTable) const
{
    priorityQueue frequencyQueue;

    for (pair<char,int> elem : frequencyTable)
    {
        string symbol;
        symbol += elem.first;

        Node* symbolNode = new Node(elem.second, nullptr, nullptr);
        symbolNode->symbol.emplace(elem.first);

        PairType toPush(symbolNode, symbol);
        frequencyQueue.push(toPush);
    }

    return frequencyQueue;
}

// -compress- constructs the tree for mode compress from the priority queue frequency table
void HuffmansTree::createTreeForCompress(HuffmansTree::priorityQueue frequencyQueue)
{
    PairType _left = frequencyQueue.top();
    frequencyQueue.pop();

    if (frequencyQueue.empty())
    {
        root = _left.first;

        return;
    }

    PairType _right = frequencyQueue.top();
    frequencyQueue.pop();

    Node* currRoot = new Node (_left.first->data + _right.first->data, _left.first, _right.first);

    PairType toPush(currRoot, _left.second + _right.second);
    frequencyQueue.push(toPush);

    createTreeForCompress(frequencyQueue);
}

// -compress- creates and returns a map with key a symbol from the text and value - it's compressed value
std::map<char,string> HuffmansTree::createCodeTable() const
{
    std::map<char,string> codeTable;
    createCodeTableHelper(root, "", codeTable);

    return codeTable;
}

// -compress-
void HuffmansTree::createCodeTableHelper (Node* currRoot, const string& path, 
                                          std::map<char,string>& codeTable) const
{
    if (currRoot->symbol.has_value())
    {
        codeTable[currRoot->symbol.value()] = path;

        return;
    }

    createCodeTableHelper(currRoot->left, path + "0", codeTable);
    createCodeTableHelper(currRoot->right, path + "1", codeTable);
}

// -compress- returns the degree of compression using the length of the input text and its compressed version
int HuffmansTree::getDegreeOfCompression(const string& input, const string& compressed) const
{
    return round((double)compressed.size() / (8 * input.size()) * 100);
}

// -debug compress- turns the bits from fromIndex to fromIndex + highestPower into an integer
int HuffmansTree::turnToDecimal(const string& binaryCode, const int& fromIndex, const int& highestPower) const
{
    int decimal = 0,
        currPower = highestPower - 1;

    for (int i = fromIndex; i < fromIndex + highestPower; i++)
    {
        decimal += std::pow(2, currPower) * (binaryCode[i] - '0');
        currPower--;
    }

    return decimal;
}

// -decompress- decompresses a single symbol
char HuffmansTree::decompressSymbol(const string& binaryCode, int& currIndex, Node* currRoot) const
{
    if (currIndex == binaryCode.size() && !currRoot->symbol.has_value())
    {
        throw std::invalid_argument("Last symbol not found, probably entered invalid tree file.");
    }

    if (currRoot->symbol.has_value())
    {
        return currRoot->symbol.value();
    }

    if (binaryCode[currIndex] == '0')
    {
        return decompressSymbol(binaryCode, ++currIndex, currRoot->left);
    }

    return decompressSymbol(binaryCode, ++currIndex, currRoot->right);
}

// -compress- constructs the tree
void HuffmansTree::setCompressMode (const string& input)
{
    std::map<char, int> frequencyTable = createFrequencyTable(input);
    priorityQueue frequencyQueue = frequencyTableToQueue(frequencyTable);

    createTreeForCompress(frequencyQueue);
}

// -debug compress- constructs the tree (same as in compress mode)
void HuffmansTree::setDebugCompressMode (const string& input)
{
    setCompressMode(input);
}  

// -decompress- constructs the tree for mode decompress from the read tree
void HuffmansTree::setDecompressMode (const vector<pair<int,optional<char>>>& nodesData)
{
    std::stack<Node*> nodes;

    for (auto elem: nodesData)
    {
        Node* newNode;

        if (elem.second.has_value())
        {
            newNode = new Node (elem.first, nullptr, nullptr);
            newNode->symbol = elem.second;
        }
        else
        {
            Node* rightChild = nodes.top();
            nodes.pop();

            Node* leftChild = nodes.top();
            nodes.pop();

            newNode = new Node (elem.first, leftChild, rightChild);
        }

        nodes.push(newNode);
    }

    root = nodes.top();
}

// -compress- returns a pair of string (the compressed text) and int (the degree of compression)
pair<string,int> HuffmansTree::compress(const string& input) const
{
    std::map<char,string> codeTable = createCodeTable();
    string binaryCode;

    for (char symbol : input)
    {
        binaryCode += codeTable[symbol];
    }

    int degreeOfCompression = getDegreeOfCompression(input,binaryCode);

    return std::make_pair(binaryCode,degreeOfCompression);
}

// -debug compress- returns a pair of vector (the integers computed from the compressed text) and
// int (the degree of compression)
pair<vector<int>,int> HuffmansTree::debugCompress(const string& input) const
{
    pair<string,int> compressed = compress(input);
    string binaryCode = compressed.first;
    int degreeOfCompression = compressed.second;

    int currStartDecimal = 0,
        binarySize = binaryCode.size(),
        currentDecimal;
    vector<int> decimalCode;

    while ((binarySize - currStartDecimal) / 8 > 0)
    {
        currentDecimal = turnToDecimal(binaryCode, currStartDecimal, 8);
        decimalCode.push_back(currentDecimal);
        currStartDecimal += 8;
    }

    currentDecimal = turnToDecimal(binaryCode, currStartDecimal, binarySize - currStartDecimal);
    if (currentDecimal != 0)
    {
        decimalCode.push_back(currentDecimal);
    }

    return std::make_pair(decimalCode,degreeOfCompression);
}

// -decompress- returns a string with the decompressed text
string HuffmansTree::decompress(const string& binaryCode) const
{
    int currIndex = 0;
    string decompressed;

    while (currIndex < binaryCode.size())
    {
        decompressed += decompressSymbol(binaryCode, currIndex, root);
    }

    return decompressed;
}

void HuffmansTree::saveTreeHelper (string& savedTree, Node* currRoot) const
{
    if (currRoot->symbol.has_value())
    {
        savedTree += std::to_string(currRoot->data) + "|" + currRoot->symbol.value() + " ";
        return;
    }

    saveTreeHelper(savedTree, currRoot->left);
    saveTreeHelper(savedTree, currRoot->right);

    savedTree += std::to_string(currRoot->data) + " ";
}

// returns a string with the information of the nodes in postorder (left, right, root) traversal 
string HuffmansTree::saveTree () const
{
    string savedTree;
    saveTreeHelper(savedTree, root);

    return savedTree;
}

void HuffmansTree::printDotHelper(string& dotInfo, Node* currRoot) const
{
    if (currRoot->symbol.has_value())
    {
        dotInfo += std::to_string((long)currRoot) + 
                   "[label = \"" + std::to_string(currRoot->data) + 
                   " | '" +  currRoot->symbol.value() + "'\"]" +
                   "[style = bold];\n";
        
        return;
    }

    printDotHelper(dotInfo, currRoot->left);
    
    dotInfo += std::to_string((long)currRoot) + 
               "[label = \"" + std::to_string(currRoot->data) + "\"];\n";

    if (currRoot->left)
    {
        dotInfo += std::to_string((long)currRoot) + "->" + 
                   std::to_string((long)(currRoot->left)) +
                   "[color = red][label = \"0\"]\n";
    }
    
    if (currRoot->right)
    {
        dotInfo += std::to_string((long)currRoot) + "->" +
                   std::to_string((long)(currRoot->right)) + 
                   "[color = blue][label = \"1\"]\n";
    }

    printDotHelper(dotInfo, currRoot->right);
}

// returns a string with the content of a file visualizing the tree
string HuffmansTree::printDot() const
{
    string dotInfo = "digraph G\n{";
    printDotHelper(dotInfo, root);
    dotInfo += "}\n";

    return dotInfo;
}
