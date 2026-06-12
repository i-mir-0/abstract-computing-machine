#include "Stack.h"

Stack::Stack(int size) : capacity(size), topIndex(-1) {
    data = new Operand * [capacity];
    for (int i = 0; i < capacity; i++) {
        data[i] = nullptr;
    }
}

Stack::~Stack() {
    for (int i = 0; i <= topIndex; i++) {
        delete data[i];
    }
    delete[] data;
}

void Stack::push(const Operand& value) {
    if (topIndex + 1 >= capacity) {
        throw std::runtime_error("Ошибка: переполнение стека!");
    }
    data[++topIndex] = new Operand(value);
}

Operand Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Ошибка: стек пуст!");
    }
    Operand result = *data[topIndex];
    delete data[topIndex];
    data[topIndex--] = nullptr;
    return result;
}

Operand Stack::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Ошибка: стек пуст!");
    }
    return *data[topIndex];
}

bool Stack::isEmpty() const {
    return topIndex == -1;
}

int Stack::size() const {
    return topIndex + 1;
}