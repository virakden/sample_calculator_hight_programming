#include "FileHandler.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

vector< vector<string> > FileHandler::readFromFile(string &fileName){
    ifstream inputFile(fileName);
    if (!inputFile)
    {
        throw runtime_error("Can't open file " + fileName + ". Make sure this file exits.");
    }

    string line;
    vector< vector<string> > sessions;
    vector<string> session_lines;

    int session_number = 1;

    while (getline(inputFile, line))
    {
        if (line.compare("---") == 0)
        {
            if (session_lines.empty())
                continue;

            // push lines into sessions and clear line for the next session
            sessions.push_back(session_lines);
            session_lines.clear();
            continue;
        }
        session_lines.push_back(line);
    }

    if(!session_lines.empty()) {
        sessions.push_back(session_lines);
    }
    
    // Close the file
    inputFile.close();

    return sessions;
}

void FileHandler::writeOutputFile(vector<double> &outputs){
    ofstream outputFile("result.txt");

    for (int i = 0; i < outputs.size(); i++)
    {
        outputFile << "---" << endl;
        outputFile << outputs[i] << endl;
    }

    outputFile.close();
    cout << "Calculation completed." << endl 
    <<"File \"result.txt\" generated." << endl;
}

