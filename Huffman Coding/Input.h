#ifndef __INPUT__HH
#define __INPUT__HH

#include <string>
#include <vector>
#include <optional>

class Input
{
    private:
    std::string inputFile;
    std::string treeFile;

    public:
    void setCompressMode (const std::string& _inputFile);
    void setDebugCompressMode (const std::string& _inputFile);
    void setDecompressMode (const std::string& _inputFile, const std::string& _treeFile);

    std::string readInputFile () const;
    std::vector<std::pair<int,std::optional<char>>> readTreeFile () const;
};

#endif
