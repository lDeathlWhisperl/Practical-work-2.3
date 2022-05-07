#include <iostream>
#include <string>
#include <algorithm>
#include "Stack.h"

int getOperationWeight(char operation)
{
    switch (operation)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
    case ')':
        return 0;
    default:
        return -1;
    }
}

void deleteChar(std::string &str, char ch)
{
    str.erase(std::remove(str.begin(), str.end(), ch), str.end());
}

int main()
{
    Stack st;
    int size;

    std::string str, res = "";
    getline(std::cin, str);

    deleteChar(str, ' ');

    for (unsigned int i = 0; i < str.length(); i++)
    {
        size = st.getSize();
        switch(getOperationWeight(str[i]))
        {
        case 1:
            if(getOperationWeight(st.read()) == 1)
                res += st.pop();
            if(getOperationWeight(st.read()) == 2)
                while (st.getSize())
                {
                    res += st.pop();
                    res += ' ';
                }
            st.push(str[i]);
            break;

        case 2:
            if (getOperationWeight(st.read()) == 2)
                res += st.pop();
            st.push(str[i]);
            break;

        case 0:
            if (str[i] == ')')
                while (st.getSize())
                {
                    if (st.read() == '(')
                    {
                        st.pop();
                        continue;
                    }
                    res += st.pop();
                    res += ' ';
                }
            else 
                st.push(str[i]);
            break;

        case -1:
            res += str[i];
            if(getOperationWeight(str[i+1]) > -1)
                res += ' ';
        }
    }

    res += ' ';
    res += st.pop();

    std::cout << res << "\n\n\n";




    std::cout << "\nsize: " << st.getSize() << "\nbase: " << st.getBase() << "\n\n";

    size = st.getSize();
    for (int i = 1; i <= size; i++)
        std::cout << st.pop() << ' ';

    std::cout << "\n\nsize: " << st.getSize() << "\nbase: " << st.getBase() << '\n';
}