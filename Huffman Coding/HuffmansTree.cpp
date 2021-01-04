#include "HuffmansTree.h"

#include <stack>
#include <cmath>

std::map<char, int> HuffmansTree::createFrequencyTable(const string& input) const
{
    std::map<char, int> frequencyTable;

    for (char symbol : input)
    {
        frequencyTable[symbol]++;
    }

    return frequencyTable;
}

HuffmansTree::priorityQueue HuffmansTree::frequencyTableToQueue(std::map<char,int> frequencyTable) const
{
    priorityQueue frequencyQueue;

    for (std::pair<char,int> elem : frequencyTable)
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

    // std::cout << toPush.second << ": " << _left.second << " " << _right.second << std::endl;

    createTreeForCompress(frequencyQueue);
}

void HuffmansTree::createTreeForDecompress (const std::vector<std::pair<int,std::optional<char>>>& nodesData)
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

std::map<char,string> HuffmansTree::createCodeTable() const
{
    std::map<char,string> codeTable;
    createCodeTableHelper(root, "", codeTable);

    return codeTable;
}

void HuffmansTree::createCodeTableHelper (Node* currRoot, const string& path, 
                                          std::map<char,string>& codeTable) const
{
    if (currRoot->symbol.has_value()) // && !currRoot->right
    {
        codeTable[currRoot->symbol.value()] = path;

        return;
    }

    createCodeTableHelper(currRoot->left, path + "0", codeTable);
    createCodeTableHelper(currRoot->right, path + "1", codeTable);
}

HuffmansTree::HuffmansTree(const string& input)
{
    std::map<char, int> frequencyTable = createFrequencyTable(input);
    priorityQueue frequencyQueue = frequencyTableToQueue(frequencyTable);

    createTreeForCompress(frequencyQueue);
}

HuffmansTree::HuffmansTree (const std::vector<std::pair<int,std::optional<char>>>& nodesData)
{
    createTreeForDecompress(nodesData);
}

string HuffmansTree::getBinaryCode(const string& input) const
{
    std::map<char, string> codeTable = createCodeTable();

    // <------------- DELETE WHEN PRESENTING --------------->
    // for (std::pair<char,string> code: codeTable)
    // {
    //     std::cout << code.first << " = " << code.second << std::endl;
    // }

    string binaryCode;
    for (char symbol : input)
    {
        binaryCode += codeTable[symbol];
    }

    return binaryCode;
}

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

void HuffmansTree::compress(const string& input, std::ostream& out) const
{
    out << getBinaryCode(input);
}

void HuffmansTree::debugCompress(const string& input) const
{
    string binaryCode = getBinaryCode(input);

    int decimalCode = 0,
        currStartDecimal = 0,
        binarySize = binaryCode.size();

    while ((binarySize - currStartDecimal) / 8 > 0)
    {
        std::cout << turnToDecimal(binaryCode, currStartDecimal, 8) << " ";
        currStartDecimal += 8;
    }

    std::cout << turnToDecimal(binaryCode, currStartDecimal, binarySize - currStartDecimal) << std::endl;
}

char HuffmansTree::decompressSymbol(const std::string& binaryCode, int& currIndex, Node* currRoot) const
{
    if (currRoot->symbol.has_value()) // && !currRoot->right
    {
        return currRoot->symbol.value();
    }

    if (binaryCode[currIndex] == '0')
    {
        return decompressSymbol(binaryCode, ++currIndex, currRoot->left);
    }

    return decompressSymbol(binaryCode, ++currIndex, currRoot->right);
}

void HuffmansTree::decompress(const std::string& binaryCode, std::ostream& out) const
{
    int currIndex = 0;
    string decompressed;

    while (currIndex < binaryCode.size())
    {
        decompressed += decompressSymbol(binaryCode, currIndex, root);
    }

    out << decompressed;
}

void HuffmansTree::saveTreeHelper (std::ostream& out, Node* currRoot) const
{
    if (currRoot->symbol.has_value())
    {
        out << currRoot->data << "|" << currRoot->symbol.value() << " ";
        return;
    }

    saveTreeHelper(out, currRoot->left);
    saveTreeHelper(out, currRoot->right);

    out << currRoot->data << " ";
}

void HuffmansTree::saveTree (std::ostream& out) const
{
    saveTreeHelper(out, root);
}

int HuffmansTree::getDegreeOfCompression(const string& input, const string& compressed) const
{
    return round((double)compressed.size() / (8 * input.size()) * 100);
}

void HuffmansTree::printDotHelper(std::ostream& out, Node* currRoot) const
{
    if (!currRoot)
    {
        return;
    }

    printDotHelper(out, currRoot->left);

    out << (long)currRoot << "[label=\"" << currRoot->data << "\"]";
    if (currRoot->symbol.has_value())
    {
        out << "[xlabel = \"" << currRoot->symbol.value() << "\"]";
    }
    out << ";\n";

    if (currRoot->left)
    {
        out << (long)currRoot << "->" << (long)(currRoot->left) << "[color=red][label = \"0\"]" << std::endl;
    }
    if (currRoot->right)
    {
        out << (long)currRoot << "->" << (long)(currRoot->right) << "[color=blue][label = \"1\"]" << std::endl;
    }

    printDotHelper(out, currRoot->right);
}

void HuffmansTree::printDot(std::ostream& out) const
{
    out << "digraph G\n{";
    printDotHelper(out, root);
    out << "}\n";
}