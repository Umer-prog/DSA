#include <iostream>
#include <string>
using namespace std;

struct HTnode {
	string Word;
	HTnode* next;
};

int counter;
int Size = 26;
HTnode* arr = new HTnode[Size];

// hash function that reads a character, convert it to int and return its index
int Hash_Function(char a) {
	int value = int(a) - 65;
	return value;
}

void insert(string w) {
	HTnode* temp = new HTnode;
	temp->Word = w;
	temp->next = NULL;
	counter += 1;
	char character = toupper(w[0]);
	int index = Hash_Function(character);
	if (arr[index].next == NULL) {
		arr[index].next = temp;
	}
	else {
		HTnode* curr = arr[index].next;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = temp;
	}
}

void printNode(int i) {
	HTnode* curr = arr[i].next;
	while (curr != NULL) {
		cout << curr->Word << endl;
		curr = curr->next;
	}
}

void printAll() {
	for (int i = 0; i < Size; i++)
	{
		cout << arr[i].Word << " : ";
		HTnode* current = arr[i].next;
		while (current != NULL)
		{
			cout << current->Word << " | ";
			current = current->next;
		}
		cout << endl;
	}
}

void deleteWord(int index, int position) {
	int jumper = 1;
	HTnode* current = arr[index].next;
	if (position <= counter)
	{
		if (position == 1)
		{
			HTnode* temp = current;
			arr[index].next = current->next;
			free(temp);
		}
		else {
			HTnode* prev = arr[index].next;
			current = current->next;
			
			while (current != NULL) {
				jumper += 1;
				if (jumper == position) {
					prev->next = current->next;
					free(current);
					break;
				}
				prev = current;
				current = current->next;
			}
		}
		
	}
	else
	{
		cout << "list out of bound!!!" << endl;
	}
}


int main() {
	for (int i = 0; i < Size; i++) {
		arr[i].Word = char(65 + i);
		arr[i].next = NULL;
	}
	string word;
	int in = 0;
	while (in != 4)
	{
		cout << "1:insert, 2:print, 3:delete, 4:exit : ";
		cin >> in;

		if (in == 1)
		{
			cout << "Enter your word: ";
			cin >> word;
			insert(word);
		}
		if (in == 2)
		{
			printAll();
		}
		if (in == 3)
		{
			int i;
			int pos;
			cout << "Enter index: ";
			cin >> i;
			cout << "Enter position: ";
			cin >> pos;
			deleteWord(i, pos);
		}
		
	}
	
	
}





