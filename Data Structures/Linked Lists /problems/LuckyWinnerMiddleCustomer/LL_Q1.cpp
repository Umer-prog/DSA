#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

//Structure for Customer Node 
struct Node {
    int customerID;
    struct Node* next;
    struct Node* previous;

};

// setting start pointer to NULL 
struct Node* start = NULL;


struct Node* mid1 = start;
struct Node* mid2 = start;

// foring number of enteries
int counter = 0;

int checker = 1; //1 for even 0 for odd

// Node insertion function
void ADD(int num) {
    // Allocating memory for int node
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->customerID = num;
    counter = counter + 1;
    temp->next = NULL;
    temp->previous = NULL;

    if (start == NULL) {
        start = temp;
        mid1 = start;
    }
    else {
        struct Node* current = start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
        temp->previous = current;

        if (checker == 1)  //when even
        {
            mid2 = mid1->next;
            checker = 0;
        }
        else if (checker == 0)   //when odd
        {
            mid1 = mid2;
            checker = 1;
        }
    }
}

// Node Deletion function
void delete_Node() {
    if (start == NULL) {
        return;
    }
    struct Node* current = start;
    while (current->next != NULL)
    {
        current = current->next;
    }
    if (current->customerID == start->customerID) {
        start = start->next;
        if (start != NULL) {
            start->previous = NULL;
        }
        free(current);
        mid1 = start;
    }
    else {
        Node* prev = start;
        Node* curr = start->next;
        while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        free(curr);
        if (checker == 1)  //when even
        {
            mid2 = mid1;
            mid1 = mid1->previous;
            checker = 0;
        }
        else if (checker == 0)   //when odd
        {
            checker = 1;
        }
    }
    counter = counter - 1;

}

void GetTrump() {
    if (counter % 2 == 0)  //when even
    {
        cout << "Mid value1: " << mid1->customerID << endl;
        cout << "Mid value2: " << mid2->customerID << endl;
    }
    else   // when odd
    {
        cout << "Mid value1: " << mid1->customerID << endl;
    }
}

void print_Node() {
    struct Node* current = start;
    if (current == NULL) {
        cout << "Linked List is empty";
    }
    else {
        while (current != NULL) {
            cout << "ID : " << current->customerID << endl;
            current = current->next;
        }
    }
}

int main() {
    int Input_Number;
    string Operation_Type;
    ifstream File_Input("E:/chrome downloads/assignment 2/TestCases/01/Test05.txt");
    Operation_Type = File_Input.get();
    while (Operation_Type != "E") {
        if (Operation_Type == "A") {
            File_Input.seekg(3, ios::cur);
            File_Input >> Input_Number;
            ADD(Input_Number);
            File_Input.get();
        }
        if (Operation_Type == "D") {
            delete_Node();
            File_Input.seekg(7, ios::cur);
        }
        Operation_Type = File_Input.get();
    }
    GetTrump();
}