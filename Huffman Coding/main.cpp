#include <iostream>
#include <string>

#include "Input.h"
#include "Output.h"
#include "HuffmanCoding.h"

void runHuffmanCoding (const Modes& mode, const std::string& inputFile, 
                       const std::string& treeFile, const std::string& outputFile)
{
    Input input;
    Output output;

    if (mode == compress)
    {
        input.setCompressMode(inputFile);
        output.setCompressMode(outputFile, treeFile);
    }
    else
    {
        input.setDecompressMode(inputFile, treeFile);
        output.setDecompressMode(outputFile);
    }

    HuffmanCoding coding(mode, input, output);
    coding.runHuffmanCoding();
}

void runProgram ()
{
    Modes mode; 

    std::string inputFile;
    std::string treeFile;
    std::string outputFile;

    char command;
    std::cin >> command;

    bool readyToRunAlgorithm = false;

    while (command != 'e')
    {
        if (command == 'c')
        {
            mode = Modes::compress;
        }
        else if (command == 'd')
        {
            mode = Modes::decompress;
        }
        else if (command == 'i')
        {
            std::cin >> inputFile;

            if (mode == decompress)
            {
                std::cin >> treeFile;
            }
        }
        else if (command == 'o')
        {
            std::cin >> outputFile;

            if (mode == compress)
            {
                std::cin >> treeFile;
            }
        }

        if (inputFile != "" && outputFile != "")
        {
            runHuffmanCoding(mode, inputFile, treeFile, outputFile);

            inputFile = "";
            treeFile = "";
            outputFile = "";
        }

        std::cin >> command;
    } 
}

int main ()
{
    runProgram();

    return 0;   
}