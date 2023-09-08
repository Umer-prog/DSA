#include <iostream>
#include <stdlib.h>
using namespace std;

struct data{
    int val;
    struct data* next;
    struct data* prev;
};

struct data* front = NULL;
struct data* back = NULL;

void InsertQueue(){

    struct data* temp = (struct data*)malloc(sizeof(struct data));
    cout << "Enter val: ";
    cin >> temp -> val;

    temp->next = NULL;
    temp->prev = NULL;

    if (back == NULL){
        back = temp;
        front = temp;
    }
    else{
        temp->next = back;
        back->prev = temp;
        back = temp;
        
    }
    
}

void printQueue(){
	struct data* current = front;
	if(current == NULL){
		cout << "QUEUE is empty" << endl;
	}else{
		while(current != NULL ){
			cout << "Value : " << current -> val << endl;
			current = current ->prev;
		}
        cout << "back of Queue is : " << back->val << endl;
        cout << "front of Queue is : " << front->val << endl;
	}
}

void deleteFront(){
    struct data* current = front;
	front = front->prev;
    free(current);
    cout << "queue popped" << endl;
}


int main(){
	    while (true) {
        int choice;
        cout << "Enter your choice (1: Push, 2: Print Stack, 3: Pop, 4: Exit ): ";
        cin >> choice;

        switch (choice) {
            case 1:
                InsertQueue();
                break;
            case 2:
                printQueue();
                break;
            case 3:
            	deleteFront();
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