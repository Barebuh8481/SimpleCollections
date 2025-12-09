#pragma once
#include <algorithm> // Для std::swap и std::copy
#include <stdexcept> // Для исключений

// Синтаксис: template <class T> - объявление шаблона класса.
// T - это параметр типа (заполнитель), который станет int, double и т.д.
template <class T>
class Vector {
private:
    T* data;          // Атрибут: Указатель на динамический массив элементов
    size_t sz;        // Атрибут: Текущее количество элементов
    size_t cap;       // Атрибут: Вместимость (сколько памяти выделено)

public:
    // Конструктор по умолчанию
    Vector() : data(nullptr), sz(0), cap(0) {}

    // Деструктор (освобождает память)
    ~Vector() {
        delete[] data;
    }

    // Конструктор копирования (Deep Copy)
    Vector(const Vector& other) : sz(other.sz), cap(other.cap) {
        if (other.data) {
            data = new T[cap]; // Выделение новой памяти
            std::copy(other.data, other.data + sz, data); // Копирование значений
        }
        else {
            data = nullptr;
        }
    }

    // Конструктор перемещения (Move Constructor) - забирает ресурсы у временного объекта
    Vector(Vector&& other) noexcept : data(other.data), sz(other.sz), cap(other.cap) {
        // "Обнуляем" старый объект, так как мы украли его данные
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // Оператор присваивания копированием
    Vector& operator=(const Vector& other) {
        if (this != &other) { // Защита от самоприсваивания
            T* newData = new T[other.cap];
            std::copy(other.data, other.data + other.sz, newData);
            delete[] data; // Удаляем старое
            data = newData;
            sz = other.sz;
            cap = other.cap;
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data; // Очищаем свою память
            // Забираем чужую
            data = other.data;
            sz = other.sz;
            cap = other.cap;
            // Обнуляем чужую
            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

    // Метод: Добавление элемента (копия)
    void push_back(const T& value) {
        if (sz >= cap) {
            reserve(cap == 0 ? 1 : cap * 2); // Увеличиваем память в 2 раза
        }
        data[sz++] = value;
    }

    // Метод: Добавление элемента (перемещение)
    void push_back(T&& value) {
        if (sz >= cap) {
            reserve(cap == 0 ? 1 : cap * 2);
        }
        data[sz++] = std::move(value);
    }

    // Метод: Получение размера
    size_t size() const {
        return sz;
    }

    // Метод: Получение элемента по индексу (для удобства вывода)
    T& operator[](size_t index) {
        if (index >= sz) throw std::out_of_range("Index out of range");
        return data[index];
    }

    // Итераторы для совместимости с range-based for и STL
    T* begin() { return data; }
    T* end() { return data + sz; }

private:
    // Вспомогательный метод для перевыделения памяти
    void reserve(size_t newCap) {
        if (newCap <= cap) return;
        T* newData = new T[newCap];
        if (data) {
            // Перемещаем старые данные в новую память
            for (size_t i = 0; i < sz; ++i) {
                newData[i] = std::move(data[i]);
            }
            delete[] data;
        }
        data = newData;
        cap = newCap;
    }
};