#include <iostream>
#include <stack>
#include <string>
using namespace std;

int precedence(char c){
    if(c == '+' || c =='-')
    {
        return 1;
    }
    if(c == '*' || c =='/')
    {
        return 2;
    }
    if(c == '^')
    {
        return 3;
    }
}

string InfixToPostfix (string w){
    stack<char> stack;
    char character;
    string postfix = "";
    int size = w.length();
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        character = w[i];
        // if operand add to the postfix expression
        if(character >= 'A' && character <= 'Z')          
        {
            postfix += character;
        }
        else            
        {
            while (!stack.empty() && precedence(character) <= precedence(stack.top())){
                postfix += stack.top();
                stack.pop();
            }
            stack.push(character);
        }
    }

    while(!stack.empty()){
        postfix += stack.top();
        stack.pop();
    }
    cout << "Postfix is : " << postfix; //it will print postfix conversion
    return postfix;
}

int main(){
    string Exp = "A+B-C/D";
    string word;
    word  = InfixToPostfix(Exp);
}
