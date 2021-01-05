#include "Output.h"

#include <iostream>
#include <fstream>

void Output::setCompressMode (const std::string& _outputFile, const std::string& _treeFile)
{
    outputFile = _outputFile;
    treeFile = _treeFile;
}

void Output::setDecompressMode (const std::string& _outputFile)
{
    outputFile = _outputFile;
    treeFile = "";
}

void Output::outputResult (std::string output) const
{
    std::ofstream outputStream(outputFile);
    outputStream << output;
}

void Output::saveTree (std::string nodesData) const
{
    std::ofstream treeStream(treeFile);
    treeStream << nodesData;
}

void outputDebugMode ();