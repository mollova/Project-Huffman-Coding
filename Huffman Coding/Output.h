/** \file Output.h 
    \brief Writing in files
*/

#ifndef __OUTPUT__HH
#define __OUTPUT__HH

#include <string>
#include <vector>

using std::string;
using std::vector;

/// Output class for printing the results (containes the names of the files in which is the writing)
class Output
{
    private:
    string outputFile; ///< for the binary code /compress mode/ (empty in debug compress mode) or the text /decompress mode/
    string treeFile; ///< for saving the tree in compress modes, empty in decompress mode
    string visualizeFile; /// for visualizing the tree with graphviz

    public:
    void setCompressMode (const string& _outputFile, 
                          const string& _treeFile, const string& _visualizeFile);
    void setDebugCompressMode (const string& _treeFile, const string& _visualizeFile);
    void setDecompressMode (const string& _outputFile);

    void outputResult (const string& output) const;
    void saveTree (const string& nodesData) const;
    void outputDebugMode (const vector<int>& decimalCode) const;
    void printDegreeOfCompression (const int& degreeOfCompression) const;
    void printAfterDecompress () const;

    void visualizeTree (const string& dotInfo) const;
};

#endif
