#include "Output.h"

#include <iostream>
#include <fstream>

// in compress mode a binary code and a tree are being written in a file
void Output::setCompressMode (const std::string& _outputFile, 
                              const std::string& _treeFile, const std::string& _visualizeFile){
    outputFile = _outputFile;
    treeFile = _treeFile;
    visualizeFile = _visualizeFile;
}

// in debug compress mode a tree is being written in a file, but a binary code is not
void Output::setDebugCompressMode (const std::string& _treeFile, const std::string& _visualizeFile)
{
    outputFile = "";
    treeFile = _treeFile;
    visualizeFile = _visualizeFile;
}

// in decompress mode a text is being written in a file, but a tree is not
void Output::setDecompressMode (const std::string& _outputFile)
{
    outputFile = _outputFile;
    treeFile = "";
}

// outputs the transformed form in a file
void Output::outputResult (const std::string& output) const
{
    std::ofstream outputStream(outputFile,std::ios::trunc);

    if (!outputStream.good())
    {
        throw "Invalid output file.";
    }

    outputStream << output;
}

// saves the constructed tree in a file
void Output::saveTree (const std::string& nodesData) const
{
    std::ofstream treeStream(treeFile,std::ios::trunc);
    treeStream << nodesData;
}

// outputs the transformed form in debug mode in the terminal
void Output::outputDebugMode (const std::vector<int>& decimalCode) const
{
    for (int number: decimalCode)
    {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

void Output::printDegreeOfCompression (const int& degreeOfCompression) const
{
    std::cout << "File successfully compressed!\n" <<
                 "Degree of compression: " << degreeOfCompression << "%\n";
}

void Output::visualizeTree (const std::string& dotInfo) const
{
    std::ofstream visualizeStream(visualizeFile,std::ios::trunc);
    visualizeStream << dotInfo;
}
