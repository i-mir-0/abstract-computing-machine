#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class Validator {
public:
    static bool isValidPostfix(const std::string& expr);
    static std::string cleanExpression(const std::string& expr);
    static bool isOperator(char ch);
    static bool isOperand(char ch);
};

#endif