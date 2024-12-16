#ifndef VARIABLEHANDLER_H
#define VARIABLEHANDLER_H

#include <string>
#include <map>

class VariableHandler
{
private:
    std::map<std::string, double> variables;
    double convertToDouble(const std::string &number);

public:
    void addVariable(std::string &varDef);
    std::map<std::string, double> getVariables();
    static bool isVariableDefinition(std::string &str);
};

#endif 
