#pragma once
#include <iostream>

struct Node
{
    char data{};
    Node* next{};
};

class Stack
{
    int size;
    Node* curr, * base;
public:
    Stack() : size(0), curr(NULL), base(NULL) {}

    int getSize();
    //del
    char getBase();

    void push(char num);

    char pop();

    char read();
};