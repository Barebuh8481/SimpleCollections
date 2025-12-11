#pragma once
#include <stdexcept>
#include <utility> // Для std::move, std::swap

template <class T>
class Stack {
private:
    T* data;    // Динамический массив
    size_t sz;  // Вершина стека
    size_t cap; // Вместимость

public:

    Stack() : data(nullptr), sz(0), cap(0) {}

    ~Stack() {
        delete[] data;
    }


    Stack(const Stack& other) : sz(other.sz), cap(other.cap) {
        if (other.data) {
            data = new T[cap];
            for (size_t i = 0; i < sz; ++i) data[i] = other.data[i];
        }
        else {
            data = nullptr;
        }
    }

    // Конструктор перемещения 
    Stack(Stack&& other) noexcept : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // Оператор присваивания (Copy-and-Swap) 
    Stack& operator=(Stack other) {
        std::swap(data, other.data);
        std::swap(sz, other.sz);
        std::swap(cap, other.cap);
        return *this;
    }

    // Добавление элемента 
    void push(const T& value) {
        if (sz >= cap) {
            // Ручное расширение памяти (как в векторе)
            size_t newCap = (cap == 0) ? 1 : cap * 2;
            T* newData = new T[newCap];
            for (size_t i = 0; i < sz; ++i) newData[i] = std::move(data[i]);
            delete[] data;
            data = newData;
            cap = newCap;
        }
        data[sz++] = value;
    }

    // Добавление перемещением
    void push(T&& value) {
        if (sz >= cap) {
            size_t newCap = (cap == 0) ? 1 : cap * 2;
            T* newData = new T[newCap];
            for (size_t i = 0; i < sz; ++i) newData[i] = std::move(data[i]);
            delete[] data;
            data = newData;
            cap = newCap;
        }
        data[sz++] = std::move(value);
    }

    // Удаление элемента 
    void pop() {
        if (sz > 0) sz--;
    }

    // Получение верхнего элемента 
    const T& top() const {
        if (sz == 0) throw std::out_of_range("Stack is empty");
        return data[sz - 1];
    }

    // Проверка на пустоту 
    bool empty() const {
        return sz == 0;
    }

    // Геттеры
    size_t size() const { return sz; }
};