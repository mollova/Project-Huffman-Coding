#include <iostream>
#include <fstream>
#include <string>

#include "Input.h"
#include "Output.h"
#include "HuffmanCoding.h"

void printHelp ()
{
    std::ifstream helpStream("help.txt");
    char c;

    while (helpStream.get(c))
    {
        std::cout << c;
    }
}

void setTreeFiles (std::string& treeFile, std::string& visualizeFile, const std::string& inputFile)
{
    treeFile = "tree_" + inputFile;
    visualizeFile = "treeV_" + inputFile.substr(0,inputFile.find(".")+1) + "dot";
}

// reads the input files, sets everything according to the mode and runs the algorithm
void runHuffmanCoding (const Modes& mode, const std::string& inputFile, 
                       std::string treeFile, const std::string& outputFile)
{
    Input input;
    Output output;

    if (mode == Modes::compress)
    {
        // treeFile = "tree_" + inputFile;
        std::string visualizeFile; //= "treeV_" + inputFile.substr(0,inputFile.find(".")+1) + "dot";
        // std::cout << visualizeFile << std::endl;

        setTreeFiles(treeFile, visualizeFile, inputFile);

        input.setCompressMode(inputFile);
        output.setCompressMode(outputFile, treeFile,visualizeFile);
    }
    else if (mode == Modes::debugCompress)
    {
        // treeFile = "tree_" + inputFile;

        std::string visualizeFile;
        setTreeFiles(treeFile, visualizeFile, inputFile);

        input.setDebugCompressMode(inputFile);
        output.setDebugCompressMode(treeFile,visualizeFile);
    }
    else
    {
        input.setDecompressMode(inputFile, treeFile);
        output.setDecompressMode(outputFile);
    }

    try
    {
        HuffmanCoding coding(mode, input, output);
        coding.runHuffmanCoding();
    }
    catch (const char* message)
    {
        std::cerr << message << std::endl;
    }
}

// reads commands calls and calls the execution of the algorithm
void runProgram ()
{
    Modes mode; 

    std::string inputFile;
    std::string treeFile;
    std::string outputFile;

    char command;
    std::cout << '-';
    std::cin >> command;

    while (command != 'e')
    {
        if (command == 'c')
        {
            mode = Modes::compress;
        }
        else if (command == 'b')
        {
            mode = Modes::debugCompress;
        }
        else if (command == 'd')
        {
            mode = Modes::decompress;
        }
        else if (command == 'i')
        {
            std::cin >> inputFile;

            if (mode == Modes::decompress)
            {
                std::cin >> treeFile;
            }
        }
        else if (command == 'o')
        {
            std::cin >> outputFile;
        }
        else if (command == 'h')
        {
            printHelp();
        }
        else
        {
            std::cout << "Please enter a supported command.\n";
        }

        if ((inputFile != "" && outputFile != "") || 
            (mode == Modes::debugCompress && inputFile != ""))
        {
            runHuffmanCoding(mode, inputFile, treeFile, outputFile);

            inputFile = "";
            treeFile = "";
            outputFile = "";
        }

        std::cout << '-';
        std::cin >> command;
    } 
}

int main ()
{
    runProgram();

    return 0;   
}
