#include "Output.h"

#include <iostream>
#include <fstream>
#include <exception>

// in compress mode a binary code and a tree are being written in a file
void Output::setCompressMode (const string& _outputFile, 
                              const string& _treeFile, const string& _visualizeFile){
    outputFile = _outputFile;
    treeFile = _treeFile;
    visualizeFile = _visualizeFile;
}

// in debug compress mode a tree is being written in a file, but a binary code is not
void Output::setDebugCompressMode (const string& _treeFile, const string& _visualizeFile)
{
    outputFile = "";
    treeFile = _treeFile;
    visualizeFile = _visualizeFile;
}

// in decompress mode a text is being written in a file, but a tree is not
void Output::setDecompressMode (const string& _outputFile)
{
    outputFile = _outputFile;
    treeFile = "";
}

// outputs the transformed form in a file
void Output::outputResult (const string& output) const
{
    std::ofstream outputStream(outputFile,std::ios::trunc);

    if (!outputStream.good())
    {
        throw std::invalid_argument("Invalid output file.");
    }

    outputStream << output;

    outputStream.close();
}

// saves the constructed tree in a file
void Output::saveTree (const string& nodesData) const
{
    std::ofstream treeStream(treeFile,std::ios::trunc);

    treeStream << nodesData;

    treeStream.close();
}

// outputs the transformed form in debug mode in the terminal
void Output::outputDebugMode (const vector<int>& decimalCode) const
{
    for (int number: decimalCode)
    {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

// prints the degree of compression afrer every successful compression
void Output::printDegreeOfCompression (const int& degreeOfCompression) const
{
    std::cout << "  File successfully compressed!\n" <<
                 "  Degree of compression: " << degreeOfCompression << "%\n";
}

// prints after successful decompression
void Output::printAfterDecompress () const
{
    std::cout << "  File successfully decompressed!\n";
}

// makes the dot file for the visualization of the tree
void Output::visualizeTree (const string& dotInfo) const
{
    std::ofstream visualizeStream(visualizeFile,std::ios::trunc);

    visualizeStream << dotInfo;

    visualizeStream.close();
}
