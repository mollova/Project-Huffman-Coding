/** \file main.cpp 
    \brief Readinf commands and calling the algorithm
*/

#include <iostream>
#include <fstream>
#include <string>

#include "HuffmanCoding.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "tests.h"

using std::string;

void runTests()
{
    doctest::Context().run();
}

/// sets the names of the files where the tree will be saved and visualized
void setTreeFiles (string& treeFile, string& visualizeFile, const string& inputFile)
{
    treeFile = "tree_" + inputFile;
    visualizeFile = "treeV_" + inputFile.substr(0,inputFile.find(".")+1) + "dot";
}

/// sets input and output for compress mode
void setCompressMode (Input& input, Output& output, 
                      const string& inputFile, string treeFile, const string& outputFile)
{
    string visualizeFile;;
    setTreeFiles(treeFile, visualizeFile, inputFile);

    input.setCompressMode(inputFile);
    output.setCompressMode(outputFile, treeFile,visualizeFile);
}

/// sets input and output for debug compress mode
void setDebugCompressMode (Input& input, Output& output, 
                           const string& inputFile, string treeFile, const string& outputFile)
{
    string visualizeFile;
    setTreeFiles(treeFile, visualizeFile, inputFile);

    input.setDebugCompressMode(inputFile);
    output.setDebugCompressMode(treeFile,visualizeFile);
}

/// sets input and output for decompress mode
void setDecompressMode (Input& input, Output& output, 
                        const string& inputFile, string treeFile, const string& outputFile)
{
    input.setDecompressMode(inputFile, treeFile);
    output.setDecompressMode(outputFile);
}

/// reads the input files, sets everything according to the mode and runs the algorithm
void runHuffmanCoding (const Modes& mode, const string& inputFile, 
                       string treeFile, const string& outputFile)
{
    Input input;
    Output output;

    switch (mode)
    {
        case Modes::compress:
            setCompressMode(input, output, inputFile, treeFile, outputFile);
            break;

        case Modes::debugCompress:
            setDebugCompressMode(input,output,inputFile,treeFile,outputFile);
            break;
            
        case Modes::decompress:
            setDecompressMode(input,output,inputFile,treeFile,outputFile);
            break;
    }

    try
    {
        HuffmanCoding coding(mode, input, output);
        coding.runHuffmanCoding();
    }
    catch (const char* message)
    {
        std::cerr << message << std::endl;
        std::cout << "Please enter new input and output files:\n";
    }
}

/// reads a single command
void readCommand (char& command)
{
    std::cout << '-';
    std::cin >> command;
}

/// checks if the command is for the mode and if it is - sets the mode
bool commandMode (const char& command, Modes& mode)
{
    if (command == 'c')
    {
        mode = Modes::compress;
        return true;
    }
    
    if (command == 'b')
    {
        mode = Modes::debugCompress;
        return true;
    }
    
    if (command == 'd')
    {
        mode = Modes::decompress;
        return true;
    }

    return false;
}

/// checks if the command is for input or output and if it is - read the names of the needed files
bool commandIO (const char& command, const Modes& mode,
                string& inputFile, string& treeFile, string& outputFile)
{
    if (command == 'i')
    {
        std::cin >> inputFile;

        if (mode == Modes::decompress)
        {
            std::cin >> treeFile;
        }

        return true;
    }
    
    if (command == 'o')
    {
        std::cin >> outputFile;
        return true;
    }

    return false;
}

/// checks if the command is help and if it is - prints the help.txt file
bool commandHelp (const char& command)
{
    if (command != 'h')
    {
        return false;
    }

    std::ifstream helpStream("help.txt");
    char c;

    while (helpStream.get(c))
    {
        std::cout << c;
    }

    return true;
}

/// reads commands calls, sets the mode and names of the files and calls the execution of the algorithm
void runProgram ()
{
    Modes mode; 
    string inputFile, treeFile, outputFile;

    char command;
    readCommand(command);

    while (command != 'e')
    {
        if (!commandMode(command,mode) && 
            !commandIO(command,mode,inputFile,treeFile,outputFile) && 
            !commandHelp(command))
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

        readCommand(command);
    } 
}

int main ()
{   
    // runTests();
    runProgram();

    return 0;   
}
