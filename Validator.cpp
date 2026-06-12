#include "Validator.h"
#include <cctype>

using namespace std;

bool Validator::isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool Validator::isOperand(char ch) {
    return (ch >= 'A' && ch <= 'Z') && ch != 'T';
}

bool Validator::isValidPostfix(const string& expr) {
    if (expr.empty()) return false;

    int operandCount = 0;

    for (char ch : expr) {
        if (isOperand(ch)) {
            operandCount++;
        }
        else if (isOperator(ch)) {
            if (operandCount < 2) return false;
            operandCount--;
        }
        else {
            return false;
        }
    }

    return operandCount == 1;
}

string Validator::cleanExpression(const string& expr) {
    string result;
    for (char ch : expr) {
        if (isOperand(ch) || isOperator(ch)) {
            result += ch;
        }
    }
    return result;
}