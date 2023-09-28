#include <iostream>
#include <string>
#include <stack>
using namespace std;

string PrefixToInfix(string w) {
    stack<string> stack;
    string first;
    string second;
    char ch;
    string ch1;
    string infix = "";
    int size = w.length();
    for (int i = 1; i <= size; i++)
    {
        ch = w[size - i];
        if (ch >= 'A' && ch <= 'Z')
        {
            ch1 = ch;
            stack.push(ch1);
        }
        
        else
        {
            first = stack.top();
            stack.pop();
            second = stack.top();
            stack.pop();
            infix = "(" + first + ch + second + ")";

            stack.push(infix);
        }
        
    }
    return infix;
}

int main() {
    string exp = "*+AB/EF";
    cout << PrefixToInfix(exp);
}
