#include <iostream>
#include <stdlib.h>
using namespace std;

struct tasks {
    string task;
    int prior;
    struct tasks* next;
    struct tasks* prev;
};

struct tasks* front = NULL;
struct tasks* back = NULL;

void InsertQueue(string t, int p) {

    struct tasks* temp = new tasks;
    temp->task = t;
    temp->prior = p;
    temp->next = NULL;
    temp->prev = NULL;

    if (back == NULL) {
        back = temp;
        front = temp;
    }
    else {
        // we are joining new nodes at the back of the list 
        // back pointer is moved 
        tasks* curr = front;
        while (curr != NULL)
        {
            if (curr->prior < temp->prior)
            {
                if (curr == front)
                {
                    temp->prev = curr;
                    curr->next = temp;
                    front = curr->next;
                    break;
                }
                else
                {
                    temp->prev = curr;
                    temp->next = curr->next;
                    curr->next->prev = temp;
                    curr->next = temp;
                    break;
                }
            }
            curr = curr->prev;
        }
        if (curr == NULL)
        {
            temp->next = back;
            back->prev = temp;
            back = temp;
        }
    }
}

void printQueue() {
    struct tasks* current = front;
    if (current == NULL) {
        cout << "QUEUE is empty" << endl;
    }
    else {
        while (current != NULL) {
            cout << "Value : " << current->task << endl;
            // current pointer going in reverse
            current = current->prev;
        }
        cout << "back of Queue is : " << back->task << endl;
        cout << "front of Queue is : " << front->task << endl;
    }
}

void deleteFront() {
    // front of the queue is deleted and front pointer points to  the previous node
    struct tasks* current = front;
    front = front->prev;
    free(current);
    cout << "queue popped" << endl;
}


int main() {
    while (true) {
        int choice;
        cout << "Enter your choice (1: Push, 2: Print Stack, 3: Pop, 4: Exit ): ";
        cin >> choice;
        if (choice == 1) {
            string task;
            int prior;
            cout << "Enter task name: ";
            cin >> task;
            cout << "Enter priority: ";
            cin >> prior;
            InsertQueue(task, prior);
        }
        if (choice == 2) {
            printQueue();
        }
        if (choice == 3) {
            deleteFront();
        }
        if (choice == 4){
            cout << "Exiting...\n";
            break;
        }
        if (choice == 5){
            cout << "Invalid choice. Please enter a valid choice.\n";
            continue;
        }
    }
}