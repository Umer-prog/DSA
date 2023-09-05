#include <iostream>
#include <stdlib.h>
using namespace std;
struct Node{
	int ID;
	int marks;
	struct Node* next;
};
struct Node* start = NULL;
void insert_Node() {
   struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
   cout << "Enter ID: ";
    cin >> temp -> ID;
    cout << "Enter marks: ";
    cin >> temp -> marks;
    temp->next = NULL;
    if(start == NULL){
    	start = temp;
	}else{
		struct Node* current = start;
		while (current -> next != NULL){
			current = current -> next;
		}
		current -> next = temp;
	}
}

void search_Node(){
	int toSearchID;
	cout << "Enter to search ID: " << endl;
	cin >> toSearchID;
	struct Node* current = start;
	while (current!=NULL){
		if(toSearchID==current->ID){
			cout << "Node found: ID = " << current -> ID<< ", Marks = " << current->marks << "\n";
			return;
		}
		current = current -> next;
	}
	if (current == NULL){
		cout << "Node not found .\n";
	}
}
void print_Node(){
	struct Node* current = start;
	if(current == NULL){
		cout << "Linked List is empty";
	}else{
		while(current != NULL){
			cout << "ID : " << current ->ID << "\n Marks : " << current-> marks << "\n";
			current = current ->next;
		}
	}
}
void delete_Node(){
	int toDeleteID;
	cout << "Enter to Delete ID : " << endl;
	cin >> toDeleteID;
	struct Node* current = start;
	if(toDeleteID == start->ID){
		start = start->next;
		free(current);
	}else{
		struct Node* prev = start;
		current = start->next;
	while (current!=NULL){
		if(toDeleteID==current->ID){
                prev->next = current->next;
                free(current);
                break;
            }
        prev = current;
        current = current -> next;
		}
	if (current == NULL){
		cout << "Node not found. \n";
	}
	}
}

int main() {
    while (true) {
        int choice;
        cout << "Enter your choice (1: Insert, 2: Search, 3: Delete, 4: Print, 5:Exit):" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                insert_Node();
                break;
            case 2:
                search_Node();
                break;
            case 3:
                delete_Node();
                break;
            case 4:
            	print_Node();
            	break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid choice.\n";
                break;
        }
    }

    return 0;
}