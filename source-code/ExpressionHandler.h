#ifndef EXPRESSIONHANDLER_H
#define EXPRESSIONHANDLER_H

#include <string>
#include <map>
class ExpressionHandler
{
private:
    std::string inputExpression;
    std::map<std::string, double> variables;

    // get var and nuber
    double getVariable(const std::string &key);
    double convertToDouble(std::string expression);
    
    // apply
    double applyOperation(double a, double b, char &op);
    double applyFunction(std::string &func, double radius);

    // check 
    bool isArithmeticOperator(char ch);
    bool isFuntion(std::string &expression);

    //get index
    int getParentheseEndIndex(const std::string &str);
    int getTermBlockEndIndex(const std::string &str);
    int getExponentBlockEndIndex(const std::string &str);

    double evaluate(const std::string &expression);

public:
    ExpressionHandler(std::string exp, std::map<std::string, double> vars);
    double evaluate();
};

#endif