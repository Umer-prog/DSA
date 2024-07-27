#include <iostream>

using namespace std;


struct NaryNode {
	int data;
	int length;
	NaryNode* address = NULL;
};

NaryNode* Insert(NaryNode* node, int val, int len) {
	if (node == NULL) {
		NaryNode* temp = new NaryNode;
		temp->data = val;
		temp->length = len;
		NaryNode* arr = new NaryNode[len];
		for (int i = 0; i < len; i++)
		{
			arr[i] = nullptr;
		}
		temp->address = arr;
		cout << "value inserted" << '\n';
		return temp;
	}
	NaryNode* sub = node->address;
	for (int i = 0; i < sub->length; i++)
	{
		if ()
		{
			Insert(node, val, len);
			
		}
	}
	return node;
}

int main() {
	NaryNode* Root = NULL;
	Root = Insert(Root, 2, 4);
//	while (true)
//	{
//		cout << "(1: Insert, 2: search value, 3: Delete, 4: In order, 5: print tree, 6: print height, 7: Exit): ";
//		cin >> choice;
//		if (choice == 1)
//		{
//			int value;
//			int len;
//			cout << "Enter value: ";
//			cin >> value;
//			cout << "Enter length: ";
//			cin >> len;
//			Root = Insert(Root, value, len);
//		}
//		/*else if (choice == 2) {
//			int ToSearch;
//			cout << "Enter value: ";
//			cin >> ToSearch;
//			Search(Root, ToSearch);
//		}
//		else if (choice == 3) {
//			int ToDelete;
//			cout << "Enter value: ";
//			cin >> ToDelete;
//			deleteNode(Root, ToDelete);
//		}
//		else if (choice == 4) {
//			InOrder(Root);
//		}
//		else if (choice == 5) {
//			printBT(Root);
//		}
//		else if (choice == 6) {
//			height(Root);
//		}
//		else if (choice == 7) {
//			cout << "Exiting....";
//			break;
//		}
//		else
//		{
//			cout << "Invalid input!!!\n";
//			continue;
//		}*/
//	}
//}