#ifndef SESSIONHANDLER_H
#define SESSIONHANDLER_H

#include <string>
#include <vector>

class SessionHandler
{
private:
    std::vector< std::vector<std::string> > sessions;

    void removeSpace(std::string &str);

public:
    SessionHandler(std::vector< std::vector<std::string> > sessions);
    std::vector<double> evaluateSession();
};

#endif