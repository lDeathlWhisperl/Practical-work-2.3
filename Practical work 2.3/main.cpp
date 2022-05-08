#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "Stack.h"
//15*(3-4)/5+1
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

void reverse(std::string str, std::string res, Stack st)
{
    deleteChar(str, ' ');

    std::cout << 
        "+==========+===============+=============================+\n"
        "|   Char   |     Stack     |        Result string        |\n"
        "+==========+===============+=============================+\n";

    std::string num;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        switch (getOperationWeight(str[i]))
        {
        case 1:
            num = "";
            if (getOperationWeight(st.read()) == 1)
            {
                res += st.pop();
                res += ' ';
            }
            if (getOperationWeight(st.read()) == 2)
                while (st.getSize())
                {
                    res += st.pop();
                    res += ' ';
                }
            st.push(str[i]);
            break;

        case 2:
            num = "";
            if (getOperationWeight(st.read()) == 2)
            {
                res += st.pop();
                res += ' ';
            }

            st.push(str[i]);
            break;

        case 0:
            num = "";
            if (str[i] == ')')
                while (st.getSize())
                {
                    if (st.read() == '(')
                    {
                        st.pop();
                        break;
                    }
                    res += st.pop();
                    res += ' ';
                }
            else
                st.push(str[i]);
            break;

        case -1:
            res += str[i];
            num += str[i];
            if (getOperationWeight(str[i + 1]) > -1)
                res += ' ';
        }

        if(num.length() && (getOperationWeight(str[i + 1]) > -1 || i == str.length()-1))
            std::cout << "| " << std::left << std::setw(8) << num << " | " << std::setw(14) << st.readAll() << "| " << std::setw(28) << res << "|\n";
        else if (!num.length())
            std::cout << "| " << std::left << std::setw(8) << str[i] << " | " << std::setw(14) << st.readAll() << "| " << std::setw(28) << res << "|\n";
    }                
    std::cout <<
        "+==========+===============+=============================+\n\nAttach the stack in reverse order to the output line: ";

    while (st.getSize())
    {
        res += ' ';
        res += st.pop();
    }

    std::cout << res << "\n\n\n";
}

int main()
{
    Stack st;
    int size;

    std::string str, res = "";
    getline(std::cin, str);

    reverse(str, res, st);
    /*
    for (int i = 1; i <= 5; i++)
        st.push(i);


    std::cout << "\nsize: " << st.getSize() << "\nbase: " << st.getBase() << "\n\n";


    std::cout << st.readAll() << '\n';

    size = st.getSize();
    for (int i = 1; i <= size; i++)
        std::cout << st.pop() << ' ';

    std::cout << "\n\nsize: " << st.getSize() << "\nbase: " << st.getBase() << '\n';
    */
}