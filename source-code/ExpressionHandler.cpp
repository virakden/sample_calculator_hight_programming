#include "ExpressionHandler.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>  //pow()
#include <map>

using namespace std;

ExpressionHandler::ExpressionHandler(string exp, map<string, double> vars): 
inputExpression(exp), variables(vars){}

//get var and nuber
double ExpressionHandler::getVariable(const string &key){
    map<string, double>::iterator variable = variables.find(key);
    if (variable == variables.end()) {
        throw runtime_error("variable " + key + " is not found");
    }
    return variable->second;
}

double ExpressionHandler::convertToDouble(string expression)
{
    try
    {
        // Check if the expression is binary
        if (regex_match(expression, regex("^[01]+b$")))
        {
            return static_cast<double>(stoi(expression.substr(0, expression.size() - 1), nullptr, 2));
        }
        // Check if the string is hexadecimal
        else if (regex_match(expression, regex("^0[xX][0-9a-fA-F]+$")))
        {
            return static_cast<double>(stoi(expression.substr(2), nullptr, 16));
        }
        // Check if the string is decimal number
        else if (regex_match(expression, regex("^[-+]?\\d*\\.?\\d+$")))
        {
            return stod(expression);
        }

        if(regex_match(expression, regex("[a-zA-Z]+"))){
            return getVariable(expression);
        }
        throw runtime_error(string("Invalid argument: ") + expression);
    }
    catch (const exception &e)
    {
        throw runtime_error(e.what());
    }
}

// apply
double ExpressionHandler::applyOperation(double a, double b, char &op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            throw runtime_error("Division by zero!");
        }
        return a / b;
    case '^':
        return pow(a, b);
    case '\0':
        op = '+';
        return a + b;
    }
    throw runtime_error("Invalid operation argument!");
}

double ExpressionHandler::applyFunction(string &func, double radius) {
    if (func == "sin") {
        return sin(radius);
    } else if (func == "cos") {
        return cos(radius);
    } else {
        throw runtime_error("Invalid funtion argument!");
    }
}

// check 
bool ExpressionHandler::isArithmeticOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

bool ExpressionHandler::isFuntion(string &expression) {
    return expression == "sin" || expression == "cos";
}

//get index
int ExpressionHandler::getParentheseEndIndex(const string &str)
{
    int openNumber = 0;
    int endNumber = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
        {
            openNumber++;
        }
        if (str[i] == ')')
        {
            endNumber++;

            if (openNumber == endNumber)
            {
                return i;
            }
        }
    }

    throw runtime_error(str +", not found the end of parenthese!");
}

int ExpressionHandler::getTermBlockEndIndex(const string &str)
{
    int startIndex;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
        {
            startIndex = getParentheseEndIndex(str.substr(i, str.length()));
            i = i + startIndex;
        }
        if (str[i] == '+' || str[i] == '-')
        {
            return i;
        }
    }

    return str.length();
}

int ExpressionHandler::getExponentBlockEndIndex(const string &str)
{
    int startIndex;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
        {
            startIndex = getParentheseEndIndex(str.substr(i, str.length()));
            i = i + startIndex;
        }
        if (str[i]!= '^' && isArithmeticOperator(str[i]))
        {
            return i;
        }
    }

    return str.length();
    if (str[0] == '(')
    {
        return getParentheseEndIndex(str);
    }
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            return i;
        }
    }

    return str.length();
}


double ExpressionHandler::evaluate(const string &expression)
{
    string exp;
    char op = '\0';
    double total = 0;
    for (size_t i = 0; i < expression.length(); i++)
    {

        if (expression[i] == '(') // calc parenthese or function block and con and covert its result to expression
        {
            if (!exp.empty() && !isFuntion(exp)) // check if it's func block
            {
                throw runtime_error(string("Invalid argument! at index ") + to_string(i));
            }

            int endIndex = getParentheseEndIndex(expression.substr(i, expression.size()));
            double blockTotal = evaluate(expression.substr(i + 1, endIndex - 1));

            if (!exp.empty()) // if func apply funtion 
            {
                blockTotal = applyFunction(exp, blockTotal);
            }

            i = i + endIndex;
            exp = to_string(blockTotal);
            continue;
        }

        if (isArithmeticOperator(expression[i]))
        {

            if ((expression[i] == '*' | expression[i] == '/') && (op == '+' | op == '-')) //calc term block and apply operation with total
            {
                int endIndex = getTermBlockEndIndex(expression.substr(i + 1, expression.size() - 1));
                string subExpression = exp + expression.substr(i, endIndex + 1);
                double subTotal = evaluate(subExpression);
                total = applyOperation(total, subTotal, op);
                exp.clear();

                i = i + endIndex + 1;

                continue;
            }

            if (expression[i] == '^') // calc the power block and covert its result to expression
            {
                int endIndex = getExponentBlockEndIndex(expression.substr(i + 1, expression.size() - 1));

                double exponentValue = evaluate(expression.substr(i + 1, endIndex));
                char temp_op = expression[i];
                double powerValue = applyOperation(convertToDouble(exp), exponentValue, temp_op);
                exp = to_string(powerValue);
                i = i + endIndex;
                continue;
            }

            if (!exp.empty())
            {
                double expValue = convertToDouble(exp);
                total = applyOperation(total, expValue, op);
                exp.clear();
            }
            // change new operator
            op = expression[i];
            continue;
        }
        exp += expression[i];
    }

    if (!exp.empty())
    {
        double expValue = convertToDouble(exp);
        total = applyOperation(total, expValue, op);
    }
    return total;
}


// public class
double ExpressionHandler::evaluate() {
    return evaluate(inputExpression);
}