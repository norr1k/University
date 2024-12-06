#pragma once
#include <iostream>


template <typename T>
class stack
{
private:
    T* arr;       // ������ ��� �������� ��������� �����
    int top;        // ������ �������� �������� �����
    size_t capacity;   // ������������ ����������� �����

public:
    stack(size_t size=40);      // �����������
    ~stack();             // ����������

    void push(T _elem);     // �������� ������� � ����
    T pop();            // ������� ������� ������� � ������� ���
    T peek();           // �������� ������� ������� �����
    bool empty();       // ���������, ���� �� ����
    bool full();        // ���������, ����� �� ����
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
        std::cout << "���� �����\n";
        return;
    }
    arr[++top] = _elem;
}

template <typename T>
T stack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("���� ����\n");
    }
    return arr[top--];
}

template <typename T>
T stack<T>::peek() {
    if (!empty()) {
        return arr[top];
    }
    throw std::out_of_range("���� ����\n");
}

template <typename T>
bool stack<T>::empty() {
    return top == -1;
}

template <typename T>
bool stack<T>::full() {
    return top == capacity - 1;
}