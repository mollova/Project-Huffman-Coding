#ifndef __OUTPUT__HH
#define __OUTPUT__HH

#include <string>

class Output
{
    private:
    std::string outputFile;
    std::string treeFile;

    public:
    void setCompressMode (const std::string& _outputFile, const std::string& _treeFile);
    void setDecompressMode (const std::string& _outputFile);

    void outputResult (std::string output) const;
    void saveTree (std::string nodesData) const;
    void outputDebugMode ();
};

#endif
