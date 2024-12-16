#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
class FileHandler
{
public:
    static std::vector< std::vector<std::string> > readFromFile(std::string &fileName);
    static void writeOutputFile(std::vector<double> &outputs);
};
#endif 
