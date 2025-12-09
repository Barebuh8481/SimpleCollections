#pragma once
#include <stdexcept>
#include <utility>

// Шаблон класса Stack
template <class T>
class Stack {
private:
    T* data;          // Атрибут: Указатель на массив
    size_t sz;        // Атрибут: Текущий размер (вершина стека)
    size_t cap;       // Атрибут: Вместимость

public:
    // Конструктор
    Stack() : data(nullptr), sz(0), cap(0) {}

    // Деструктор
    ~Stack() {
        delete[] data;
    }

    // Конструктор копирования
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

    // Оператор присваивания (реализуем через copy-and-swap идиому для краткости)
    Stack& operator=(Stack other) {
        std::swap(data, other.data);
        std::swap(sz, other.sz);
        std::swap(cap, other.cap);
        return *this;
    }

    // Метод: Добавить в стек
    void push(const T& value) {
        if (sz >= cap) {
            size_t newCap = (cap == 0) ? 1 : cap * 2;
            T* newData = new T[newCap];
            for (size_t i = 0; i < sz; ++i) newData[i] = std::move(data[i]);
            delete[] data;
            data = newData;
            cap = newCap;
        }
        data[sz++] = value;
    }

    // Метод: Удалить последний элемент
    void pop() {
        if (sz > 0) {
            sz--;
            // Мы не удаляем физически память, просто сдвигаем "вершину"
        }
    }

    // Метод: Получить верхний элемент
    const T& top() const {
        if (sz == 0) throw std::logic_error("Stack is empty");
        return data[sz - 1];
    }

    // Метод: Проверка на пустоту
    bool empty() const {
        return sz == 0;
    }
};