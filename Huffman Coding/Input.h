/** \file Input.h 
    \brief Reading from files
*/

#ifndef __INPUT__HH
#define __INPUT__HH

#include <string>
#include <vector>
#include <optional>

using std::string;
using std::vector;
using std::pair;
using std::optional;

/// Input class for all the reading from files (containes the names of the files from which is the reading)
class Input
{
    private:
    string inputFile; ///< for the text /compress modes/ or the binary code /decompress mode/
    string treeFile; ///< for the saved tree file needed for decompreess (empty in compress modes)

    public:
    void setCompressMode (const string& _inputFile);
    void setDebugCompressMode (const string& _inputFile);
    void setDecompressMode (const string& _inputFile, const string& _treeFile);

    string readInputFile () const;
    vector<pair<int,optional<char>>> readTreeFile () const;
};

#endif
