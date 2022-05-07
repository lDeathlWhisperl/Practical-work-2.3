#include "Stack.h"
#include <iostream>

int Stack::getSize()
{
    return size;
}

//del
char Stack::getBase()
{
    if (base)
        return base->data;
    return -1;
}

void Stack::push(char num)
{
    Node* temp = new Node;
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

char Stack::pop()
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

char Stack::read()
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