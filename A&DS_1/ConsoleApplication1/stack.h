#pragma once
#include <iostream>


template <typename T>
class stack
{
private:
    T* arr;       // Массив для хранения элементов стека
    int top;        // Индекс верхнего элемента стека
    size_t capacity;   // Максимальная вместимость стека

public:
    stack(size_t size=40);      // Конструктор
    ~stack();             // Деструктор

    void push(T _elem);     // Добавить элемент в стек
    T pop();            // Удалить верхний элемент и вернуть его
    T peek();           // Получить верхний элемент стека
    bool empty();       // Проверить, пуст ли стек
    bool full();        // Проверить, полон ли стек
};

template <class T>
stack<T>::stack(size_t size) {
    arr = new T[size];
    capacity = size;
    top = -1;
}

template <typename T>
stack<T>::~stack() {
    delete[] arr;
}

template <typename T>
void stack<T>::push(T _elem) {
    if (full()) {
        std::cout << "Стек полон\n";
        return;
    }
    arr[++top] = _elem;
}

template <typename T>
T stack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Стек пуст\n");
    }
    return arr[top--];
}

template <typename T>
T stack<T>::peek() {
    if (!empty()) {
        return arr[top];
    }
    throw std::out_of_range("Стек пуст\n");
}

template <typename T>
bool stack<T>::empty() {
    return top == -1;
}

template <typename T>
bool stack<T>::full() {
    return top == capacity - 1;
}