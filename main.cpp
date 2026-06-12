#include "InstructionGenerator.h"
#include "Validator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#define NOMINMAX
#include <windows.h>

using namespace std;

void setRussianLocale() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showMenu() {
    cout << endl;
    cout << "   АБСТРАКТНАЯ ВЫЧИСЛИТЕЛЬНАЯ МАШИНА" << endl;
    cout << "========================================" << endl;
    cout << "1. Ввести выражение вручную" << endl;
    cout << "2. Загрузить выражение из файла (input.txt)" << endl;
    cout << "3. Загрузить из файла и сохранить результат" << endl;
    cout << "4. Показать пример (ABC*+DE-/)" << endl;
    cout << "0. Выход" << endl;
    cout << "========================================" << endl;
}

int getUserChoice() {
    int choice;
    while (true) {
        cout << "Выберите пункт: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Ошибка: введите число от 0 до 4!" << endl;
            showMenu();
        }
        else if (choice < 0 || choice > 4) {
            cout << "Ошибка: выберите пункт от 0 до 4!" << endl;
            showMenu();
        }
        else {
            clearInput();
            return choice;
        }
    }
}

bool hasOnlyValidChars(const string& expr) {
    for (char ch : expr) {
        bool isValid = (ch >= 'A' && ch <= 'Z') ||
            ch == '+' || ch == '-' || ch == '*' || ch == '/';
        if (!isValid) {
            return false;
        }
    }
    return true;
}

void processExpression(const string& expression, bool saveToFile = false) {
    if (!hasOnlyValidChars(expression)) {
        cout << "Ошибка: выражение содержит недопустимые символы!" << endl;
        cout << "Разрешены только латинские буквы A-Z и операции + - * /" << endl;
        return;
    }

    string cleaned = Validator::cleanExpression(expression);

    cout << "\nВыражение: " << cleaned << endl;

    if (!Validator::isValidPostfix(cleaned)) {
        cout << "Ошибка: некорректное постфиксное выражение!" << endl;
        cout << "Проверьте, что:" << endl;
        cout << "  - используются только буквы A-Z и операции + - * /" << endl;
        cout << "  - количество операндов на 1 больше количества операций" << endl;
        return;
    }

    InstructionGenerator generator;
    generator.generate(cleaned);

    cout << "\nСгенерированные инструкции:" << endl;
    generator.printInstructions();
    cout << "----------------------------------------" << endl;

    if (saveToFile) {
        try {
            generator.saveToFile("output.txt");
            cout << "\nИнструкции сохранены в файл output.txt" << endl;
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
}

bool loadFromFile(const string& filename, string& expression) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: файл " << filename << " не найден!" << endl;
        return false;
    }

    getline(file, expression);
    file.close();

    if (expression.empty()) {
        cout << "Ошибка: файл " << filename << " пуст!" << endl;
        return false;
    }

    return true;
}

void manualInput() {
    string expression;
    cout << "Введите выражение в постфиксной форме (например, ABC*+DE-/: ";
    getline(cin, expression);

    if (expression.empty()) {
        cout << "Ошибка: выражение не может быть пустым!" << endl;
        return;
    }

    processExpression(expression, false);
}

void fromFile() {
    string expression;
    if (!loadFromFile("input.txt", expression)) {
        cout << "Создайте файл input.txt с постфиксным выражением." << endl;
        cout << "Пример содержимого: ABC*+DE-/" << endl;
        return;
    }
    processExpression(expression, false);
}

void fromFileAndSave() {
    string expression;
    if (!loadFromFile("input.txt", expression)) {
        cout << "Создайте файл input.txt с постфиксным выражением." << endl;
        return;
    }
    processExpression(expression, true);
}

void example() {
    string expression = "ABC*+DE-/";
    processExpression(expression, false);
}

int main() {
    setRussianLocale();

    while (true) {
        showMenu();
        int choice = getUserChoice();

        switch (choice) {
        case 1:
            manualInput();
            break;
        case 2:
            fromFile();
            break;
        case 3:
            fromFileAndSave();
            break;
        case 4:
            example();
            break;
        case 0:
            cout << "Выход из программы." << endl;
            return 0;
        }

        cout << "\nНажмите Enter для продолжения...";
        cin.get();
    }
}