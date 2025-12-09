#include <iostream>
#include <string>
#include <chrono>   
#include <windows.h>

#include "Vector.hpp"
#include "Stack.hpp"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Демонстрация Vector <int> ===" << endl;
    Vector<int> myVec;
    myVec.push_back(10);
    myVec.push_back(20);
    myVec.push_back(30);

    // Использование итераторов (range-based for)
    cout << "Элементы вектора: ";
    for (const auto& val : myVec) {
        cout << val << " ";
    }
    cout << "\nРазмер: " << myVec.size() << endl;

    cout << "\n=== Демонстрация Stack <string> ===" << endl;
    Stack<string> myStack;
    myStack.push("Петров");
    myStack.push("Лев");
    myStack.push("Евгеньевич");

    cout << "Верхний элемент: " << myStack.top() << endl;
    myStack.pop();
    cout << "Верхний элемент после pop(): " << myStack.top() << endl;

    cout << "\n=== Сравнение производительности (100,000,000 push) ===" << endl;

    // Тест скорости Vector
    auto start = chrono::high_resolution_clock::now();
    Vector<int> testVec;
    for (int i = 0; i < 100000000; ++i) {
        testVec.push_back(i);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Vector push_back: " << diff.count() << " сек." << endl;

    // Тест скорости Stack
    start = chrono::high_resolution_clock::now();
    Stack<int> testStack;
    for (int i = 0; i < 100000000; ++i) {
        testStack.push(i);
    }
    end = chrono::high_resolution_clock::now();
    diff = end - start;
    cout << "Stack push:       " << diff.count() << " сек." << endl;

    cout << "\nПрограмма завершена успешно." << endl;
    return 0;
}