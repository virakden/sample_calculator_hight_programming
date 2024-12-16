#include "FileHandler.h"
#include "SessionHandler.h"

#include <iostream>

//calc total run time
#include <chrono>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
    //clock start time
    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();

    // get input file and read it
    if (argc <= 1)
    {
        cout << "No input file!" << endl;
        return 1;
    }

    //read input file
    string inputFileName = argv[1];

    try {
        vector< vector<string> > sessions = FileHandler::readFromFile(inputFileName);

        SessionHandler sessionHandler(sessions);
        vector<double> outputs = sessionHandler.evaluateSession();

        FileHandler::writeOutputFile(outputs);
    }
    catch (const exception &e)
    {
        cout << "Error: "<< e.what() << endl;
    }



    // clock end time
    chrono::high_resolution_clock::time_point end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end_time - start_time;
    std::cout << "Total runtime: " << fixed << setprecision(5) 
              << duration.count() << "s" << endl;

    return 0;
}
