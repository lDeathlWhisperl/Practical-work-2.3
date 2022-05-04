#include <iostream>

struct Node
{
    int data{};
    Node* next{};
};

class Stack
{
    int size;
    Node* curr, *base;
public:
    Stack() : size(0), curr(NULL), base(NULL) {}

    int getSize()
    {
        return size;
    }
    //del
    int getBase()
    {
        if(base)
            return *reinterpret_cast<int*>(base);
        return -1;
    }

    void push(int num)
    {
        Node* temp = new Node;
        temp->data = num;
        if(curr)
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

    int pop()
    {
        if(base)
        {
            curr = base;
            for (int i = 1; i < size; i++)
                curr = curr->next;

            int res = *reinterpret_cast<int*>(curr);
            delete curr;
            size--;

            if (!size)
                curr = base = NULL;
        
            return res;
        }
        std::cout << "\x1b[31m[STACK IS EMPTY]\x1b[0m ";
        return NULL;
    }
};

int main()
{
    Stack st;

    int size = 25;

    for (int i = 1; i <= size; i++)
        st.push(i);
    
    std::cout << "\nsize: " << st.getSize() << "\nbase: " << st.getBase() << "\n\n";

    for (int i = 1; i <= size; i++)
        std::cout << st.pop() << ' ';

    std::cout << "\n\nsize: " << st.getSize() << "\nbase: " << st.getBase() << '\n';
}