#include <iostream>
#include <stdlib.h>
using namespace std;

struct data{
    int val;
    struct data* link;
};

struct data* top = NULL;

void PUSH(){

    struct data* temp = (struct data*)malloc(sizeof(struct data));
    cout << "Enter val: ";
    cin >> temp -> val;

    temp->link = NULL;

    if (top == NULL){
        top = temp;
    }
    else{

        temp->link = top;
        top = temp;
    }
    
}

void printStack(){
	struct data* current = top;
	if(current == NULL){
		cout << "Linked List is empty";
	}else{
		while(current != NULL ){
			cout << "Value : " << current -> val << endl;
			current = current ->link;
		}
        cout << "top of stack is : " << top->val << endl;
	}
}

void POP(){
    struct data* current = top;
	top = top->link;
    free(current);
    cout << "Stack popped" << endl;
}


int main(){
	    while (true) {
        int choice;
        cout << "Enter your choice (1: Push, 2: Print Stack, 3: Pop, 4: Exit ): ";
        cin >> choice;

        switch (choice) {
            case 1:
                PUSH();
                break;
            case 2:
                printStack();
                break;
            case 3:
            	POP();
            	break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid choice.\n";
                break;
        }
    }
    return 0;
}