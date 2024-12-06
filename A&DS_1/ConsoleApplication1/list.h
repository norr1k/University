#pragma once


template <typename T>
struct List_Node
{
    T data;
    List_Node* prev = nullptr;
    List_Node* next = nullptr;

    List_Node(T data)
    {
        this->data = data;
    }
};


template <typename T>
class List
{
private:
    size_t Length;
    List_Node<T>* Head;
    List_Node<T>* Tail;

public:
    List();
    ~List();

    size_t GetLength();
    List_Node<T>* GetAt(size_t index);
    List_Node<T>& operator[] (size_t index);

    List_Node<T>* AddHead(T data);
    List_Node<T>* AddTail(T data);
    List_Node<T>* Add(T data, int index);

    List_Node<T>* PopHead();
    List_Node<T>* PopTail();
    List_Node<T>* Pop(int index);
};