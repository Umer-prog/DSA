#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct Node{
	int ID;
	int Amount;
	struct Node* next;
};

struct Node* start = NULL;

void insertNode(int id, int amount) {
   struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->Amount = amount;
	temp->ID = id;
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

void deleteID(int del){
	
	if (start == NULL)
	{
		return;
	}
	if (del == start->ID)
	{
		struct Node* current = start;
		start = start->next;
		free(current);
	}
	else{
		struct Node* prev = start;
		struct Node* current = start->next;
		while (current!=NULL){
			if(del == current->ID){
					prev->next = current->next;
					free(current);
					break;
				}
			prev = prev->next;
			current = current -> next;
			}
	}
}

void printNode(){
	struct Node* current = start;
	if(current == NULL){
		cout << "Linked List is empty";
	}else{
		while(current != NULL ){
			cout  << current ->ID << "	" << current-> Amount << "\n";
			current = current ->next;
		}
	}
}


int main(){
	int TotalTransactions = 0;
	int TotalFraudTransactions = 0;
	int ID;
	int Amount;
	
	ifstream FileInput("E:/chrome downloads/assignment 2/TestCases/03/Test04.txt");
	FileInput >> TotalTransactions;
	FileInput >> TotalFraudTransactions;
	
	for (int i = 0; i < TotalTransactions;i++) {
		FileInput >> ID;
		FileInput.ignore();
		FileInput >> Amount;
		insertNode(ID,Amount);
	}
	for (int i = 0; i < TotalFraudTransactions; i++) {
		FileInput >> ID;
		deleteID(ID);
	}
	printNode();

    return 0;
}
