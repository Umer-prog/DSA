#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;


// Structure for node
struct Node{
	int value;
	struct Node* next;
};

// start pointer
struct Node* start = NULL;

// third last node pointer
struct Node* third = start;

// input counter
int count = 0;

void insertNode(int b) {
   struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp -> value = b;
    temp->next = NULL;
    count = count + 1;

    if(start == NULL){
    	start = temp;
	}else{
		struct Node* current = start;
        struct Node* prev = start;
		while (current -> next != NULL){
            prev = current;
			current = current -> next;
            
		}
		current -> next = temp;
        third = prev;
	}
    
}

void print_third(){
	struct Node* current = start;
	if(count < 3){
		cout << "-1" << endl;
	}else{
		cout << "Value of third last Node is: " << third->value << endl;
		
	}

}

int main(){
	    int numberinput;
	    int condition = 0;
	    ifstream FileInput("E:/chrome downloads/assignment 2/TestCases/05/Test05.txt");
	    while (condition != -1 && condition!=10) {
		    FileInput >> numberinput;
		    insertNode(numberinput);
		    condition = FileInput.get();
	    }
		print_third();
    return 0;
}