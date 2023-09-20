#include <iostream>
#include <fstream>
using namespace std;

struct Node {
	int Value;
	Node* next;
	Node* previous;
};
int condition1 = 0;
int counter = 0;
float median = 0;
Node* start = NULL;

void ADD(int b) {
	Node* temp = (Node*)malloc(sizeof(struct Node));
	temp->Value = b;
	if (start == NULL) {
		start = temp;
		start->previous = NULL;
		start->next = NULL;
		median = start->Value;
		condition1 = 1;
		counter = 1;
	}
	// input with sorting directly
	else {
		Node* current = start;
		while (current->next != NULL && current->Value < temp->Value) {
			current = current->next;
		}
		if (current == start && current->Value >= temp->Value) {          

			start = temp;
			start->next = current;
			current->previous = start;

		}
		else if (current->next == NULL && current->Value < temp->Value) {  
			current->next = temp;
			temp->previous = current;
			temp->next = NULL;
		}
		else {                                                      
			Node* Currentprev = current->previous;
			Currentprev->next = temp;
			temp->previous = Currentprev;
			temp->next = current;
			current->previous = temp;
		}
		counter++;
		// storing median
		// For odd
		if (condition1 == 0) {                     
			struct Node* current = start;
			for (int i = 1; i != (counter + 1) / 2; i++) {
				current = current->next;
			}
			median = current->Value;
			condition1 = 1;
		}
		//for even
		else {                             
			Node* current = start;
			for (int i = 1; i != (counter / 2); i++) {
				current = current->next;
			}
			float hold = current->Value;
			current = current->next;
			median = (hold + current->Value) / 2;
			condition1 = 0;
		}
	}

}

int main()
{
	int Input;
	int condition = 0;
	ifstream File_Input("E:/chrome downloads/assignment 2/TestCases/02/Test02.txt");
	while (condition != -1 && condition != 10) {
		File_Input >> Input;
		ADD(Input);
		cout << "median: " << median << endl;
		condition = File_Input.get();
	}

}