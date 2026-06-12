#ifndef OPERAND_H
#define OPERAND_H

#include <string>

class Operand {
private:
    std::string name;
    bool isTemp;

public:
    Operand();
    Operand(const std::string& name, bool temp = false);
    Operand(const Operand& other);
    ~Operand();

    std::string getName() const;
    bool isTemporary() const;

    Operand& operator=(const Operand& other);
};

#endif