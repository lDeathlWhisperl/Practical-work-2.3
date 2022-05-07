#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
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

void reverse(std::string str, std::string res, Stack st)
{
    char operations[][130] = {
        "                                                      add to output line                                                       ",
        "                                                       push into stack                                                         ",
        " 1) attach the contents of the stack to the parenthesis in reverse order to the output line; 2) delete the bracket from stack. "};
         
    std::cout << 
        "+======+===============================================================================================================================+=======+===============+\n"
        "| Char |                                                           Operation                                                           | Stack | Result string |\n"
        "+======+===============================================================================================================================+=======+===============+\n";
        
    int j;
    std::string num;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        switch (getOperationWeight(str[i]))
        {
        case 1:
            num = "";
            if (getOperationWeight(st.read()) == 1)
                res += st.pop();
            if (getOperationWeight(st.read()) == 2)
                while (st.getSize())
                {
                    res += st.pop();
                    res += ' ';
                }
            j = 1;
            st.push(str[i]);
            break;

        case 2:
            num = "";
            if (getOperationWeight(st.read()) == 2)
                res += st.pop();
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
                        continue;
                    }
                    res += st.pop();
                    res += ' ';
                }
            else
                st.push(str[i]);
            break;

        case -1:
            j = 0;
            res += str[i];
            num += str[i];
            if (getOperationWeight(str[i + 1]) > -1)
                res += ' ';
        }

        if(num.length() && (getOperationWeight(str[i + 1]) > -1 || i == str.length()-1))
            std::cout << "| " << std::left << std::setw(4) << num << " |" << operations[j] << "|\n";
        else if (!num.length())
            std::cout << "| " << std::left << std::setw(4) << str[i] << " |" << operations[j] << "|\n";
    }                
    std::cout <<
        "+======+===============================================================================================================================+";
    res += ' ';
    res += st.pop();
}

int main()
{
    Stack st;
    int size;

    std::string str, res = "";
    getline(std::cin, str);

    deleteChar(str, ' ');

    reverse(str, res, st);

    std::cout << res << "\n\n\n";




    std::cout << "\nsize: " << st.getSize() << "\nbase: " << st.getBase() << "\n\n";

    size = st.getSize();
    for (int i = 1; i <= size; i++)
        std::cout << st.pop() << ' ';

    std::cout << "\n\nsize: " << st.getSize() << "\nbase: " << st.getBase() << '\n';
}