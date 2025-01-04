#include <iostream>
#include <stdlib.h>
using namespace std;


// structure
/*structure needed for list
contains double linked list*/
struct Node{
	int Value;
	struct Node* next;
	struct Node* previous;
};
//structure end..


// initialization
/*These are all the variables and pointers
that were initialized for the code*/
struct Node* start = NULL;
struct Node* End = NULL;
struct Node* cursor = NULL;
int count = 0;
int cursorcount = 0;
// intialization end...

//------------------------------------------sub functions------------------------------------------
/*These are all the sub functions*/

// this function adds node at the start
void ADDstart(Node* temp){
	Node* current = start;		
	temp->next = current;
	current->previous = temp;
	start = temp;
}

// this function adds node in the middle
void ADDmiddle(Node* prev, Node* temp){
	prev->next->previous = temp;
	temp->previous = prev;
	temp->next = prev->next;
	prev->next = temp;
}

// this function adds node at the end
void ADDend(Node* temp) {  
	struct Node* current = start;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = temp;
	temp->previous = current;
	End = temp;
}

//this function deletes node at the start
void DeleteStart() { 
	Node* current = start;
	start = start->next;
	if (start!=NULL)
	start->previous = NULL;
	free(current);
}

// this function deletes node in the middle
void DeleteMid(Node* current) {
	current->previous->next = current->next;
	current->next->previous = current->previous;
	free(current);
}

// this function deletes node at the end
void DeleteEnd() {
	Node* current = End;
	End = End->previous;
	End->next = NULL;
	free(current);
}
//----------------------------------------sub function end-----------------------------------------


//----------------------------------------main functions-------------------------------------------
//-------------------------------------------------------------------------------------------------
/*These are the main functions of the program*/

//-----------------------------------insertion functions-------------------------------------------
// this function inserts node in a sequence
void ADD() {
   struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
   cout << "Enter Value: ";
    cin >> temp -> Value;
    temp->next = NULL;
    temp->previous = NULL;
	count += 1;
    if(start == NULL){
    	start = temp;
        End = start;
        start->previous = NULL;
		cursor = start;
	}
	else{
		ADDend(temp);
	}
}

// this function inserts at a given value						
void Add_Index_Num(){
	int index;
	struct Node* temp = (Node*)malloc(sizeof(struct Node));
	cout << "input index for insertion: ";
	cin >> index;
	
	//checks if given index is within range(number of nodes)
	if (index > count || index < 0) {
		cout << "Error, wrong index" << endl;
		return;
	}
	cout << "input value: ";
	cin >> temp -> Value;
	temp->next = NULL;
	temp->previous = NULL;
	count += 1;
	//checks if insertion is in the start
	if (index == 0) {            
		ADDstart(temp);
	}
	else{
		struct Node* prev = start;
		//going to (index - 1) position.
		for (int i=0; i < index-1; i++) {
			prev = prev->next;
		}
		//if insertion at end
		if (prev->next == NULL) {     
			ADDend(temp);
		}
		//if insertion in middle
		else {
			ADDmiddle(prev, temp);
		}
	}
	if (index <= cursorcount)
	{
		cursor = cursor ->previous;
	}
	
}
// -------------------------------------insertion function end------------------------------------

// ---------------------------------------delete functions-----------------------------------------
// this function deletes the end of the list
void Delete(){
	if (start == NULL)
	{
		return;
	}
	if (cursorcount < count)
	{
		cursor = cursor->previous;
		cursorcount -= cursorcount;
	}
	
	count -= 1;
	if (End == start)
	{
		Node* current = start;
		start =NULL;
		End = NULL;
		free(current);
	}
	else
	{
		DeleteEnd();
		cout << "Tail of the list deleted" << endl;
	}

	
}

// this function deletes at given index
void DeleteIndex(int Index){
	if (start == NULL) {
		cout << "list is empty" << endl;
		return;
	}
	if (Index >= count || Index < 0) {
		cout << "Error, wrong index" << endl;
		return;
	}

	// checking conditions for cursor 
	if (Index <= cursorcount && cursor->next != NULL)
	{
		cursor = cursor->next;
	}
	else if (Index <= cursorcount && cursor->next == NULL)
	{
		cursor = cursor->previous;
		cursorcount -= 1;
	}
	
	
	count -= 1;
	if (Index == 0) {
		DeleteStart();

	}
	else {
		Node* current = start;
		for (int i = 0; i < Index; i++) {
			current = current->next;
		}
		if (current == End) {
			DeleteEnd();
		}
		else {
			DeleteMid(current);
		}
	}
	if (start == NULL) {
		End = NULL;
	}
}
//------------------------------------delete functions end-----------------------------------------

//-------------------------------------cursor functions--------------------------------------------
// this function moves cursor forward by given steps 
void MoveForward(){
	int steps;
	cout << "Enter number of steps: ";
	cin >> steps;
	cursorcount += steps;
	// checking if steps are within range (number of nodes)
	if (cursorcount + 1 > count)
	{
		cursorcount = count - 1;
		cursor = End;
		cout << "Cursor updated." << endl;
		return;
	}
	for (int i = 0; i < steps; i++)
	{
		cursor = cursor->next;
	}
}

// this function moves cursor backwards by givem steps
void MoveBackward(){
	int steps;
	cout << "Enter number of steps: ";
	cin >> steps;
	cursorcount -= steps;
	// checking if steps are within range (number of nodes)
	if (cursorcount < 0)
	{
		cursorcount = 0;
		cursor = start;
		cout << "Cursor updated." << endl;
		return;
	}
	for (int i = 0; i < steps; i++)
	{
		cursor = cursor->previous;
	}
} 

// this function adds number just after cursor position
//void ADDImmediate(int value){
	//int index = cursorcount + 1;
	//Add_Index_Num(index, value);
//}

// this function updates data at which the cursor is pointing
void UpdateImmediate(){
	int newval;
	cout << "Enter the new value: ";
	cin >> newval;
	cursor->Value = newval;
	cout << "Value is updated.." << endl;
}

// this function deletes the index where the cursor is present
void DeleteImmediate(){
	DeleteIndex(cursorcount);  
	cout << "Index succesfully deleted! " << endl;
}

// this function shifts the current data with data of the index specified
void Shift() {
	int index;
	cout << "Enter index: ";
	cin >> index;
	if (index >= count) {
		cout << "Error, index out of bound" << endl;
		return;
	}
	Node* current = start;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	swap(cursor->Value,current->Value);
	cout << "Swapped!!" << endl;
}
//-----------------------------------cursor functions end-----------------------------------------

//--------------------------------------print function--------------------------------------------
void printNode(){
	struct Node* current = start;
	if(current == NULL){
		cout << "Linked List is empty";
	}else{
		while(current != NULL ){
			cout << "value : " << current ->Value << endl;
			current = current ->next;
		}
		cout << "tail: " << End->Value << endl;
	}
}


void printCursor(){
	cout << "cursor data: " << cursor->Value << endl;
}
//---------------------------------------print function end----------------------------------------

//-----------------------------------------main function end---------------------------------------
//-------------------------------------------------------------------------------------------------

int main(){
	while (true) {
        int choice;
        cout << "Enter your choice (1: Insert, 2: Print, 3: Delete, 4: Delete Index, 5: Exit ): ";
        cin >> choice;

        switch (choice) {
            case 1:
                ADD();
                break;
			case 2:
				printNode();
				break;
            case 3:
                Add_Index_Num();
                break;
            case 4:
            	Delete();
            	break;
            case 5:
				int index;
				cout << "Enter index: ";
				cin >> index; 
            	DeleteIndex(index);
            	break;
			case 6:
				MoveForward();
				break;
			case 7:
				MoveBackward();
				break;
			case 8:
				printCursor();
				break;
			// case 9:
			// 	int val;
			// 	cout << "Enter value: ";
			// 	cin >> val;
			//  	ADDImmediate(val);
			// 	break;
            case 9:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid choice.\n";
                break;
        }
    }
    return 0;
}
