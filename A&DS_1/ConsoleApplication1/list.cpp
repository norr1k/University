#include "list.h"
#include <iostream>

// Конструктор списка
template <typename T>
List<T>::List()
{
    Head = nullptr;
    Tail = nullptr;
    Length = 0;
}

// Деструктор списка
template <typename T>
List<T>::~List()
{
    List_Node<T>* tmpptr;
    while (Head != nullptr)
    {
        tmpptr = Head;
        Head = Head->next;
        delete tmpptr;
    }
    Tail = nullptr;
}

// Получение длины списка
template <typename T>
size_t List<T>::GetLength()
{
    return Length;
}

// Получение узла по индексу
template <typename T>
List_Node<T>* List<T>::GetAt(size_t index)
{
    if (index >= Length)
        throw std::out_of_range("Индекс вне границ списка");

    List_Node<T>* tmpptr = Head;
    for (size_t i = 0; i < index; i++)
    {
        tmpptr = tmpptr->next;
    }

    return tmpptr;
}

// Перегрузка оператора []
template <typename T>
List_Node<T>& List<T>::operator[] (size_t index)
{
    return *GetAt(index);
}

// Добавление элемента в голову списка
template <typename T>
List_Node<T>* List<T>::AddHead(T data)
{
    List_Node<T>* tmpptr = new List_Node<T>(data);
    if (Length == 0)
        Head = Tail = tmpptr;
    else
    {
        Head->prev = tmpptr;
        tmpptr->next = Head;
        Head = tmpptr;
    }
    Length++;
    return tmpptr;
}

// Добавление элемента в хвост списка
template <typename T>
List_Node<T>* List<T>::AddTail(T data)
{
    List_Node<T>* tmpptr = new List_Node<T>(data);
    if (Length == 0)
        Head = Tail = tmpptr;
    else
    {
        Tail->next = tmpptr;
        tmpptr->prev = Tail;
        Tail = tmpptr;
    }
    Length++;
    return tmpptr;
}

// Добавление элемента по индексу
template <typename T>
List_Node<T>* List<T>::Add(T data, int index)
{
    if (index == 0)
        return AddHead(data);
    else if (index == Length)
        return AddTail(data);
    else if (index > Length)
        throw std::out_of_range("Индекс вне границ списка");

    List_Node<T>* tmpptr = new List_Node<T>(data);
    List_Node<T>* ptr_right = GetAt(index);
    List_Node<T>* ptr_left = ptr_right->prev;

    ptr_left->next = tmpptr;
    ptr_right->prev = tmpptr;
    tmpptr->next = ptr_right;
    tmpptr->prev = ptr_left;

    Length++;
    return tmpptr;
}

// Удаление элемента из головы списка
template <typename T>
List_Node<T>* List<T>::PopHead()
{
    if (Head == nullptr)
        throw std::out_of_range("Список пуст");

    List_Node<T>* tmpptr = Head;
    Head = tmpptr->next;

    if (Head != nullptr)
        Head->prev = nullptr;
    else
        Tail = nullptr;

    tmpptr->next = nullptr;
    Length--;
    return tmpptr;
}

// Удаление элемента из хвоста списка
template <typename T>
List_Node<T>* List<T>::PopTail()
{
    if (Tail == nullptr)
        throw std::out_of_range("Список пуст");

    List_Node<T>* tmpptr = Tail;
    Tail = tmpptr->prev;

    if (Tail != nullptr)
        Tail->next = nullptr;
    else
        Head = nullptr;

    tmpptr->prev = nullptr;
    Length--;
    return tmpptr;
}

// Удаление элемента по индексу
template <typename T>
List_Node<T>* List<T>::Pop(int index)
{
    if (index == 0)
        return PopHead();
    else if (index == Length - 1)
        return PopTail();
    else if (index >= Length)
        throw std::out_of_range("Индекс вне границ списка");

    List_Node<T>* tmpptr = GetAt(index);
    List_Node<T>* left_ptr = tmpptr->prev;
    List_Node<T>* right_ptr = tmpptr->next;

    left_ptr->next = right_ptr;
    right_ptr->prev = left_ptr;

    tmpptr->next = tmpptr->prev = nullptr;
    Length--;
    return tmpptr;
}


template class List<int>;
template class List<double>;
template class List<char>;
