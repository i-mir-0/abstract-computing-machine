#ifndef STACK_H
#define STACK_H

#include "Operand.h"
#include <stdexcept>

class Stack {
private:
    Operand** data;
    int capacity;
    int topIndex;

public:
    Stack(int size = 100);
    ~Stack();

    void push(const Operand& value);
    Operand pop();
    Operand top() const;
    bool isEmpty() const;
    int size() const;
};

#endif