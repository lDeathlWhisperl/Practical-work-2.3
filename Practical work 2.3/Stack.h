#pragma once
#include <iostream>
#include <string>

template <typename T>
struct Node
{
    T data{};
    Node* next{};
};

template <typename T>
class Stack
{
    int size;
    Node<T>* curr, * base;
public:
    Stack() : size(0), curr(NULL), base(NULL) {}

    int getSize();
    //del
    T getBase();

    void push(T);

    T pop();

    T read();

    std::string readAll();

    std::string readAll_int();
};