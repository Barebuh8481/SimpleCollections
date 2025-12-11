#include <iostream>
#include <chrono>
#include <string>
#include <windows.h>
#include <iomanip>

#include "Vector.hpp"
#include "Stack.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << fixed << setprecision(9);

    const int N = 20000000;

    cout << "Данные: " << N << " элементов.\n" << endl;


    cout << "[Тест Vector]" << endl;
    {
        Vector<int> vec;
        vec.reserve(10);

        // 1. Быстрое добавление (есть место)
        auto start = high_resolution_clock::now();
        vec.push_back(1);
        auto end = high_resolution_clock::now();

        // ПРЕВРАЩАЕМ В СЕКУНДЫ (double)
        duration<double> fastTime = end - start;
        cout << "1. Быстрый push (пустой):   " << fastTime.count() << " сек." << endl;

  
        vec.reserve(N);
        for (size_t i = vec.size(); i < N; ++i) {
            vec.push_back(i);
        }

        // 2. Медленное добавление (нужна новая память)
        start = high_resolution_clock::now();
        vec.push_back(999);
        end = high_resolution_clock::now();

        duration<double> slowTime = end - start;
        cout << "2. Медленный push (полный): " << slowTime.count() << " сек." << endl;
    }

    cout << "\n------------------------------------------------\n";


    cout << "[Тест Stack]" << endl;
    {
        Stack<int> st;

        // 1. Быстрое добавление
        auto start = high_resolution_clock::now();
        st.push(1);
        auto end = high_resolution_clock::now();

        duration<double> fastTime = end - start;
        cout << "1. Быстрый push (пустой):   " << fastTime.count() << " сек." << endl;

        int limit = 16777216;
        for (int i = st.size(); i < limit; ++i) {
            st.push(i);
        }

        // 2. Медленное добавление
        start = high_resolution_clock::now();
        st.push(999);
        end = high_resolution_clock::now();

        duration<double> slowTime = end - start;
        cout << "2. Медленный push (полный): " << slowTime.count() << " сек." << endl;
    }
    return 0;
}