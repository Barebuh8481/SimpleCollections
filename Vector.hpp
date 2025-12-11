#pragma once
#include <algorithm> // Для std::copy, std::move, std::swap
#include <stdexcept> // Для исключений

template <class T>
class Vector {
private:
    T* data;          // Указатель на массив
    size_t sz;        // Текущий размер
    size_t cap;       // Вместимость памяти

public:
    // 1. Конструктор по умолчанию 
    Vector() : data(nullptr), sz(0), cap(0) {}

    // 2. Деструктор 
    ~Vector() {
        delete[] data;
    }

    // 3. Конструктор копирования (Deep Copy) 
    Vector(const Vector& other) : sz(other.sz), cap(other.cap) {
        if (other.data) {
            data = new T[cap];
            // Используем copy для обычных типов
            std::copy(other.data, other.data + sz, data);
        }
        else {
            data = nullptr;
        }
    }

    // 4. Конструктор перемещения (Move) 
    Vector(Vector&& other) noexcept : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // 5. Оператор присваивания (Копирование) 
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            T* newData = new T[other.cap];
            std::copy(other.data, other.data + other.sz, newData);
            delete[] data;
            data = newData;
            sz = other.sz;
            cap = other.cap;
        }
        return *this;
    }

    // 6. Оператор присваивания (Перемещение) 
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            sz = other.sz;
            cap = other.cap;
            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

    // Добавление элемента (копия) 
    void push_back(const T& value) {
        if (sz >= cap) reserve(cap == 0 ? 1 : cap * 2);
        data[sz++] = value;
    }

    // Добавление элемента (перемещение/move) 
    void push_back(T&& value) {
        if (sz >= cap) reserve(cap == 0 ? 1 : cap * 2);
        data[sz++] = std::move(value);
    }

    // Получение размера 
    size_t size() const { return sz; }

    // Получение вместимости
    size_t capacity() const { return cap; }

    // Оператор доступа по индексу
    T& operator[](size_t index) {
        if (index >= sz) throw std::out_of_range("Index out of range");
        return data[index];
    }

    // Итераторы 
    T* begin() { return data; }
    T* end() { return data + sz; }

    // Резервирование памяти
    void reserve(size_t newCap) {
        if (newCap <= cap) return;
        T* newData = new T[newCap];
        if (data) {
            // Перемещаем старые элементы в новую память
            for (size_t i = 0; i < sz; ++i) {
                newData[i] = std::move(data[i]);
            }
            delete[] data;
        }
        data = newData;
        cap = newCap;
    }
};