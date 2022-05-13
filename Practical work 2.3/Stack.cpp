#include "Stack.h"
#include <iostream>
#include <string>

template <typename T>
int Stack<T>::getSize()
{
    return size;
}

//del
template <typename T>
T Stack<T>::getBase()
{
    if (base)
        return base->data;
    return -1;
}

template <typename T>
void Stack<T>::push(T num)
{
    Node<T>* temp = new Node<T>;
    temp->data = num;
    if (curr)
    {
        curr->next = temp;
        curr = curr->next;
    }
    else
    {
        curr = temp;
        base = temp;
    }
    size++;
}

template <typename T>
T Stack<T>::pop()
{
    if (base)
    {
        curr = base;
        for (int i = 1; i < size; i++)
            curr = curr->next;

        int res = curr->data;
        delete curr;
        size--;

        if (!size)
            curr = base = NULL;

        return res;
    }
    return NULL;
}

template <typename T>
T Stack<T>::read()
{
    if (base)
    {
        curr = base;
        for (int i = 1; i < size; i++)
            curr = curr->next;

        return curr->data;
    }
    return NULL;
}

template <typename T>
std::string Stack<T>::readAll()
{
    std::string res;
    if (base)
    {
        curr = base;
        int temp = size;
        for (int i = 1; i < temp; i++)
        {
            res += curr->data;
            res += ',';
            curr = curr->next;
        }
        //res += curr->data;
        return res;
    }
    return "\0";
}

template<class T>
std::string Stack<T>::readAll_int()
{
    std::string res;
    if (base)
    {
        curr = base;
        int temp = size;
        for (int i = 1; i < temp; i++)
        {
            res += std::to_string(curr->data);
            res += ',';
            curr = curr->next;
        }
        res += std::to_string(curr->data);
        return res;
    }
    return "\0";
}
