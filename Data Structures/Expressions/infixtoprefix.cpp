#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

int precedence(char c) {
    if (c == '+' || c == '-')
    {
        return 1;
    }
    if (c == '*' || c == '/')
    {
        return 2;
    }
    if (c == '^')
    {
        return 3;
    }
}

string InfixToPostfix(string w) {
    reverse(w.begin(), w.end());
    stack<char> stack;
    char character;
    string prefix = "";
    int size = w.length();
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        character = w[i];
        // if operand add to the postfix expression
        if (character >= 'A' && character <= 'Z')
        {
            prefix += character;
        }
        else
        {
            while (!stack.empty() && precedence(character) <= precedence(stack.top())) {
                prefix += stack.top();
                stack.pop();
            }
            stack.push(character);
        }
    }

    while (!stack.empty()) {
        prefix += stack.top();
        stack.pop();
    }
    reverse(prefix.begin(), prefix.end());
    cout << "Prefix is : " << prefix; //it will print postfix conversion
    return prefix;
}

int main() {
    string Exp = "A*B+C/D";

    InfixToPostfix(Exp);
}