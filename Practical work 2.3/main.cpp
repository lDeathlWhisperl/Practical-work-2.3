#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <conio.h>
#include "Stack.cpp"
//15*(3-4/1)/5+1
// a*(b-c)/d+e
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

void deleteChar(std::string& str, char ch)
{
    str.erase(std::remove(str.begin(), str.end(), ch), str.end());
}

void solveExpression_normal(std::string str)
{
    Stack<int> nums;
    Stack<char> operations;
    size_t size = str.length();
    std::string num;

    for (size_t i = 0; i < size; i++)
    {
        if (isdigit(str[i]))
            num += str[i];

        if (getOperationWeight(str[i]) > 0 || i == size - 1)
        {
            nums.push(std::stoi(num));
            num = "";
        }

        if (getOperationWeight(str[i]) > -1)
            operations.push(str[i]);
    }
    std::cout << nums.readAll_int() << '\n' << operations.readAll();

}

bool isMistake(std::string str)
{
    size_t size = str.length();
    int brackets = 0;

    if (size == 0)
        return true;

    //if the first or the most recent character is an operation
    if (getOperationWeight(str[0]) >= 1 || getOperationWeight(str[size - 1]) >= 1)
        return true;

    for (size_t i = 0; i < size; i++)
    {
        //all characters except +,-,*,/
        if (!isalnum(str[i]) && getOperationWeight(str[i]) < 0)
            return true;

        //if two variables are neighbours
        if (isalpha(str[i]) && isalpha(str[i + 1]))
            return true;

        //if '(' is followed by an operation 
        if (str[i] == '(' && getOperationWeight(str[i + 1]) >= 0)
            return true;

        //if an operation is followed by ')'
        if (getOperationWeight(str[i]) >= 0 && str[i + 1] == ')')
            return true;

        //if two operations are neighbours
        if (getOperationWeight(str[i]) >= 1 && getOperationWeight(str[i + 1]) >= 1)
            return true;

        if (str[i] == '(')
            brackets++;
        if (str[i] == ')')
            brackets--;

        //if the first bracket is the closing one
        if (brackets < 0)
            return true;
    }
    //checking an even bracket count
    if (brackets)
        return true;

    return false;
}

void varInit(std::string& str)
{
    int num = NULL;
    std::string res;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        while (isalpha(str[i]))
        {
            std::cout << "Please init the variable " << str[i] << " = ";
            std::cin >> num;
            if (num != NULL)
                break;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
            }
        }
        if (num != NULL)
            res += std::to_string(num);
        else
            res += str[i];
        num = NULL;
    }

    str = res;
}

void toReverseNotation(std::string str, std::string res)
{
    system("cls");
    Stack<char> st;

    std::cout <<
        "+==========+===============+=============================+\n"
        "|   Char   |     Stack     |        Result string        |\n"
        "+==========+===============+=============================+\n";

    std::string num;
    for (size_t i = 0; i < str.length(); i++)
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
            while (getOperationWeight(st.read()) == 2)
            {
                    res += st.pop();
                    res += ' ';
            }
            st.push(str[i]);
            break;

        case 2:
            num = "";
            while (getOperationWeight(st.read()) == 2)
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

        if (num.length() && (getOperationWeight(str[i + 1]) > -1 || i == str.length() - 1))
            std::cout << "| " << std::left << std::setw(8) << num << " | " << std::setw(14) << st.readAll() << "| " << std::setw(28) << res << "|\n";
        else if (!num.length())
            std::cout << "| " << std::left << std::setw(8) << str[i] << " | " << std::setw(14) << st.readAll() << "| " << std::setw(28) << res << "|\n";
    }
    std::cout <<
        "+==========+===============+=============================+\n\nAttach the stack in reverse order to the output line: ";
    
    if (res[res.length() - 1] == ' ')
        res.pop_back();

    while (st.getSize())
    {
        res += ' ';
        res += st.pop();
    }

    std::cout << res << "\n\n\nThe initial expression: " << str << "\nThe reverse polish notation: " << res << '\n';
}

int main()
{
    std::string str, res = "";
    getline(std::cin, str);
    deleteChar(str, ' ');
    //solveExpression_normal(str);

    if (!isMistake(str))
    {
        varInit(str);
        toReverseNotation(str, res);
    }
    else
        std::cout << "you entered the wrong expression";

}