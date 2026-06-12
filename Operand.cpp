#include "Operand.h"

Operand::Operand() : name(""), isTemp(false) {}

Operand::Operand(const std::string& name, bool temp) : name(name), isTemp(temp) {}

Operand::Operand(const Operand& other) : name(other.name), isTemp(other.isTemp) {}

Operand::~Operand() {}

std::string Operand::getName() const {
    return name;
}

bool Operand::isTemporary() const {
    return isTemp;
}

Operand& Operand::operator=(const Operand& other) {
    if (this != &other) {
        name = other.name;
        isTemp = other.isTemp;
    }
    return *this;
}