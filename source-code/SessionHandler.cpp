#include "SessionHandler.h"
#include "ExpressionHandler.h"
#include "VariableHandler.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //remove()
#include <map>
#include <cmath> 

using namespace std;

SessionHandler::SessionHandler(vector< vector<string> > sessions): sessions(sessions){}

vector<double> SessionHandler::evaluateSession() {
    vector<double> result;

    for (int i = 0; i < sessions.size(); i++)
    {
        double output;
        VariableHandler vars;
        map<string, double> variables;
        for (int j = 0; j < sessions[i].size(); j++)
        {
            removeSpace(sessions[i][j]);
            try
            {
                if(!VariableHandler::isVariableDefinition(sessions[i][j])){ // only evaluate expression once
                    ExpressionHandler exp(sessions[i][j], vars.getVariables());
                    output = exp.evaluate();
                    break;
                }
                vars.addVariable(sessions[i][j]);
            }
            catch (const exception &e)
            {
                cout << "Error! Session " << i+1 << " \""<< sessions[i][j] << "\" "<< e.what() << endl;
                output = NAN;
            }
        }
        result.push_back(output);
    }

    return result;
}

void SessionHandler::removeSpace(string &str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
}