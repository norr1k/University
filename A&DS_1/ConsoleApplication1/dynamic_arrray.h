#pragma once
#include <iostream>

template <typename T>
class DynamicArray
{
private:
    T* data;           
    size_t capacity;   
    size_t length;     

    

public:
    void resize(size_t new_capacity);
    DynamicArray();                
    DynamicArray(size_t initial_capacity); // Конструктор с начальной ёмкостью
    ~DynamicArray();               

    size_t size() const;           
    size_t get_capacity() const;   

    void push_back(const T& value);    
    void insert(const T& value, size_t index); 
    void remove_at(size_t index);
    T& operator[](size_t index);

    T* begin();     
    T* end();
};


// Конструктор по умолчанию
template <typename T>
DynamicArray<T>::DynamicArray()
{
    capacity = 1;
    length = 0;
    data = new T[capacity];
}

// Конструктор с начальной ёмкостью
template <typename T>
DynamicArray<T>::DynamicArray(size_t initial_capacity)
{
    capacity = initial_capacity;
    length = 0;
    data = new T[capacity];
}

// Деструктор
template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] data;
}

// Получение текущего размера массива
template <typename T>
size_t DynamicArray<T>::size() const
{
    return length;
}

// Получение ёмкости массива
template <typename T>
size_t DynamicArray<T>::get_capacity() const
{
    return capacity;
}

// Приватный метод для изменения ёмкости массива
template <typename T>
void DynamicArray<T>::resize(size_t new_capacity)
{
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < length; i++)
    {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

// Добавление элемента в конец массива
template <typename T>
void DynamicArray<T>::push_back(const T& value)
{
    if (length == capacity) // Если места недостаточно, увеличиваем ёмкость
    {
        resize(capacity * 2);
    }
    data[length] = value;
    length++;
}

// Вставка элемента по индексу
template <typename T>
void DynamicArray<T>::insert(const T& value, size_t index)
{
    if (index > length)
        throw std::out_of_range("Индекс вне границ массива");

    if (length == capacity)
    {
        resize(capacity * 2);
    }

    for (size_t i = length; i > index; i--)
    {
        data[i] = data[i - 1];
    }

    data[index] = value;
    length++;
}

// Удаление элемента по индексу
template <typename T>
void DynamicArray<T>::remove_at(size_t index)
{
    if (index >= length)
        throw std::out_of_range("Индекс вне границ массива");

    for (size_t i = index; i < length - 1; i++)
    {
        data[i] = data[i + 1];
    }

    length--;

    // Опционально можно уменьшить ёмкость, если данных стало мало
    if (length < capacity / 4)
    {
        resize(capacity / 2);
    }
}

// Перегрузка оператора [] для доступа к элементам
template <typename T>
T& DynamicArray<T>::operator[](size_t index)
{
    if (index >= length)
        throw std::out_of_range("Индекс вне границ массива");
    return data[index];
}

// Указатель на начало массива
template <typename T>
T* DynamicArray<T>::begin()
{
    return data;
}

// Указатель на элемент после конца массива
template <typename T>
T* DynamicArray<T>::end()
{
    return data + length;
}


