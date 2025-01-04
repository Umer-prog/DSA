#include <iostream>

using namespace std;

int precedence(char c) {
    if (c == '=')
    {
        return 1;
    }
    if (c == '|') //or
    {
        return 2;
    }
    if (c == '&') // and
    {
        return 3;
    }
    if (c == '_' || c == '!') // == is represented as '_' and != as '!'
    {
        return 4;
    }
    if (c == '<' || c == '>' || c == ',' || c == '.') //<= is represented as ',' and >= as '.'
    {
        return 5;
    }
    if (c == '+' || c == '-')
    {
        return 6;
    }
    if (c == '*' || c == '/')
    {
        return 7;
    }
    if (c == '^')
    {
        return 8;
    }
    return 0;
}

struct BSTnode {
    char data;
    BSTnode* left;
    BSTnode* right;
};

BSTnode* ExpressionTree(BSTnode* node, string e) {
    // step 1 check for lowest precedence operator and make it a node
    char op = '^';
    char Nodechar= '-';
    char ch;
    int index = 0;
    string left;
    string right;
    int size = e.length();
    // checks for the lowest precedence operator
    for (int i = 0; e[i]; i++) {  //slice the expression i<size
        ch = e[i];
        if (ch == '(')      // first checks bracket and skips till closing bracket
        {
            while (ch != ')') {
                i++;
                ch = e[i];
            }
            if (i == size - 1) { //if bracket exists at last place so just skip it
                break;
            }
            i++;          // else update the variable holding char
            ch = e[i];   
        }
       
        if (!isalnum(ch) && precedence(op) >= precedence(ch)) {   // if operator
            cout << "inside precedence\n";                  // uses right associative strat
            op = ch;                                        // if same precedence operator right most side one is taken
            index = i;
            cout << op << endl;
        }
        else {  // if alpha numeric
            cout << "inside alpha numeric\n";
            Nodechar = ch;
            cout << Nodechar << endl;
        }
        
    }
    BSTnode* temp = new BSTnode;
    // if expression is a single char
    if (e.length() == 1)
    {
        cout << "in final if  string is a single char\n";
        //updates output variable
        op = Nodechar;
    }

    // for making left side and right side expressions
    // and skipping brackets
    else
    {
        if (e[0] == '(' && e[index - 1] == ')')
        {
            for (int j = 1; j < index - 1; j++) { // if bracket exists start from next index
                left += e[j];

            }
        }
        else
        {
            for (int l = 0; l < index; l++)
            {
                left += e[l];
            }
        }
        if (e[index + 1] == '(' && e[size - 1] == ')')
        {
            for (int j = index + 2; j < size - 1; j++) {// if bracket exists start from next index
                right += e[j];
            }

        }
        else
        {
            for (int r = index + 1; r < e.length(); r++)
            {
                right += e[r];
            }
        }
        
    }
    
    // for checking / debugging
    cout << "left side:" << left << endl;
    cout << "right side:"  << right << endl;
    // value of node is set 
    temp->data = op;
    // if leaf node then set left right to null
    temp->left = NULL;
    temp->right = NULL;
    // if there is an expression then it further breaks it
    if (e.length() != 1)
    {
        temp->left = ExpressionTree(node, left);
        temp->right = ExpressionTree(node, right);
    }
    return temp;
}

void printt(const string& prefix, BSTnode* parent, bool isLeft, bool isRoot) {
    if (parent == nullptr)
        return;

    if (isRoot) {
        cout << "RT----";
    }
    else {
        cout << prefix <<
            (isLeft ? "(L)|----" : "(R)L----");
    }
    // print the value of the node
    cout << parent->data << endl;

    // enter the next tree level - left and right branch
    printt(prefix + (isLeft ? "   | " : "    "),
        parent->left, true, false);
    printt(prefix + (isLeft ? "   | " : "    "),
        parent->right, false, false);
}

 //pass the root node of your binary tree
void printBT(BSTnode* node) {
    printt("", node, false, true);
}

void In_Order(BSTnode* node) {
    if (node != NULL) {
        In_Order(node->left);
        cout << node->data << endl;
        In_Order(node->right);
    }
}

struct BSTnode* Root = NULL;
int main() {
    

    string exp;
    cout << "enter your expression: ";
    cin >> exp;
    Root = ExpressionTree(Root, exp);
    cout << "expression tree made succesfully\n";
    In_Order(Root);
    printBT(Root);
    
}