#ifndef __OUTPUT__HH
#define __OUTPUT__HH

#include <string>
#include <vector>

class Output
{
    private:
    std::string outputFile;
    std::string treeFile;
    std::string visualizeFile;

    public:
    void setCompressMode (const std::string& _outputFile, 
                          const std::string& _treeFile, const std::string& _visualizeFile);
    void setDebugCompressMode (const std::string& _treeFile, const std::string& _visualizeFile);
    void setDecompressMode (const std::string& _outputFile);

    void outputResult (const std::string& output) const;
    void saveTree (const std::string& nodesData) const;
    void outputDebugMode (const std::vector<int>& decimalCode) const;
    void printDegreeOfCompression (const int& degreeOfCompression) const;

    void visualizeTree (const std::string& dotInfo) const;
};

#endif
