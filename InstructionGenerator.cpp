#include "InstructionGenerator.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

InstructionGenerator::InstructionGenerator() : tempCounter(0) {}

string InstructionGenerator::newTemp() {
    tempCounter++;
    return "T" + to_string(tempCounter);
}

void InstructionGenerator::addInstruction(const string& instr, const string& operand) {
    instructions.push_back(instr + " " + operand);
}

void InstructionGenerator::generate(const string& postfix) {
    Stack st(100);

    for (char ch : postfix) {
        if (isalpha(ch) && ch != 'T') {
            st.push(Operand(string(1, ch), false));
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            Operand right = st.pop();
            Operand left = st.pop();

            string tempName = newTemp();

            addInstruction("LD", left.getName());

            switch (ch) {
            case '+': addInstruction("AD", right.getName()); break;
            case '-': addInstruction("SB", right.getName()); break;
            case '*': addInstruction("ML", right.getName()); break;
            case '/': addInstruction("DV", right.getName()); break;
            }

            addInstruction("ST", tempName);
            st.push(Operand(tempName, true));
        }
    }

    if (!instructions.empty()) {
        string lastInstr = instructions.back();
        if (lastInstr.find("ST") == 0) {
            instructions.pop_back();
        }
    }
}

void InstructionGenerator::printInstructions() const {
    for (const string& instr : instructions) {
        cout << instr << endl;
    }
}

void InstructionGenerator::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Ошибка: не удалось открыть файл для записи");
    }
    for (const string& instr : instructions) {
        file << instr << endl;
    }
    file.close();
}

void InstructionGenerator::clear() {
    instructions.clear();
    tempCounter = 0;
}

const vector<string>& InstructionGenerator::getInstructions() const {
    return instructions;
}