#ifndef INSTRUCTIONGENERATOR_H
#define INSTRUCTIONGENERATOR_H

#include <string>
#include <vector>
#include "Stack.h"

class InstructionGenerator {
private:
    int tempCounter;
    std::vector<std::string> instructions;

    std::string newTemp();
    void addInstruction(const std::string& instr, const std::string& operand);

public:
    InstructionGenerator();

    void generate(const std::string& postfix);
    void printInstructions() const;
    void saveToFile(const std::string& filename) const;
    void clear();

    const std::vector<std::string>& getInstructions() const;
};

#endif