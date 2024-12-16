#include "VariableHandler.h"
#include <iostream>
#include <string>
#include <map>
#include <regex>

using namespace std;

void VariableHandler::addVariable(string &varDef) {
    int equalIndex = varDef.find('=');

    string varName = varDef.substr(0, equalIndex);
    double value = convertToDouble(varDef.substr(equalIndex + 1, varDef.length() - 1));

    if(!regex_match(varName, regex("[a-zA-Z]+"))){
        throw runtime_error("Invalid variable name! " + varName);
    }
    variables[varName] = value;
}

map<string, double> VariableHandler::getVariables(){
    return variables;
}

bool VariableHandler::isVariableDefinition(string &str)
{
    bool hasAssignment = false;
    int equalsIndex = -1;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '=') {
            if (hasAssignment) {
                throw runtime_error("There is more than one \"=\" !");
            }
            hasAssignment = true;
            equalsIndex = i;
        }
    }

    if (hasAssignment && (equalsIndex == 0 || equalsIndex == str.length() - 1)) {
        throw runtime_error("Invalid variable assignment, no value or variable name!");
    }

    return hasAssignment;
}

double VariableHandler::convertToDouble(const string &number)
{
    try
    {
        // Check if the number is binary
        if (regex_match(number, regex("^[01]+b$")))
        {
            return static_cast<double>(stoi(number.substr(0, number.size() - 1), nullptr, 2));
        }
        // Check if the string is hexadecimal
        else if (regex_match(number, regex("^0[xX][0-9a-fA-F]+$")))
        {
            return static_cast<double>(stoi(number.substr(2), nullptr, 16));
        }
        // Check if the string is decimal number
        else if (regex_match(number, regex("^[-+]?\\d*\\.?\\d+$")))
        {
            return stod(number);
        }

        throw runtime_error(string("Invalid argument: ") + number);
    }
    catch (const exception &e)
    {
        throw runtime_error(e.what());
    }
}
