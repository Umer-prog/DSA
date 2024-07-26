#include <iostream>

using namespace std;

struct BSTNode {
	int data;
	int h;
	BSTNode* left;
	BSTNode* right;
};

// Function to insert value in node
BSTNode* insert(BSTNode* node, int value) {
	if (node == NULL) {
		BSTNode* temp = (BSTNode*)malloc(sizeof(BSTNode));
		temp->data = value;
		temp->left = NULL;
		temp->right = NULL;
		temp->h = 0;
		cout << "value inserted" << '\n';
		return temp;
	}
	if (value > node->data) {
		node->right = insert(node->right, value);
	}
	else
	{
		node->left = insert(node->left, value);
	}
	return node;
}

// Function to search a value in tree
void Search(BSTNode* node, int value) {
	if (value == node->data) {
		cout << "Value found!!" << '\n';
		return;
	}
	if (value > node->data)
	{
		if (node->right == NULL) {
			cout << "value not found!!" << '\n';
			return;
		}
		Search(node->right, value);
	}
	else
	{
		if (node->left == NULL) {
			cout << "value not found!!" << '\n';
			return;
		}
		Search(node->left, value);
	}
}

// Traversing 
void InOrder(BSTNode* node) {
	if (node != NULL) {
		InOrder(node->left);
		cout << node->data << endl;
		InOrder(node->right);
	}
}
void PostOrder(BSTNode* node) {
	if (node != NULL) {
		PostOrder(node->left);
		PostOrder(node->right);
		cout << node->data << endl;
	}
}
void PreOrder(BSTNode* node) {
	if (node != NULL) {
		cout << node->data << endl;
		PreOrder(node->left);
		PreOrder(node->right);
	}
}


void printt(const string& prefix, BSTNode* parent, bool isLeft, bool isRoot) {
	if (parent == nullptr)
		return;

	if (isRoot) {
		cout << "RT----";
	}
	else {
		cout << prefix <<
			(isLeft ? "(L)|----" : "(R)L----");
	}
	// print the value of the node
	cout << parent->data<< endl;

	// enter the next tree level - left and right branch
	printt(prefix + (isLeft ? "   | " : "    "),
		parent->left, true, false);
	printt(prefix + (isLeft ? "   | " : "    "),
		parent->right, false, false);
}

// pass the root node of your binary tree
void printBT(BSTNode* node) {
	printt("", node, false, true);
}

BSTNode* smallest(BSTNode* node) {
	while (node->left != NULL)
	{
		node = node->left;
	}
	return node;
}

// function for deleting a node
BSTNode* deleteNode(BSTNode* node, int toDelete) {
	if (node == NULL) {
		cout << "Value not found \n";
		return node;
	}
	if (toDelete < node->data)
	{
		node->left = deleteNode(node->left, toDelete);
	}
	else if(toDelete>node->data){
		node->right = deleteNode(node->right,toDelete);
	}
	else {
		// checking for single child
		if (node->left == NULL) {
			BSTNode* temp = node->right;
			free(node);
			cout << "Value deleted!\n";
			return temp;
		}
		else if (node->right == NULL) {
			BSTNode* temp = node->left;
			free(node);
			cout << "Value deleted!\n";
			return temp;
		}

		// if node have 2 childs
		BSTNode* temp = smallest(node->right);
		node->data = temp->data;
		node->right = deleteNode(node->right, temp->data);
	}
	return node;
}

int height(BSTNode* node) {
	if (node == NULL) {
		return -1; // Height of an empty subtree is 0.
	}

	// Calculate the height of the left and right subtrees recursively
	int leftHeight = height(node->left);
	int rightHeight = height(node->right);

	// Determine the maximum height between left and right subtrees
	int maxHeight = max(leftHeight, rightHeight);

	// The height of the current node is one more than the maximum height of its children
	int currentNodeHeight = maxHeight + 1;

	// Print node data and height for debugging
	cout << "Node: " << node->data << " Height: " << currentNodeHeight << endl;

	return currentNodeHeight;
}

int main() {
	BSTNode* Root = NULL;
    int choice;
	while (true)
	{
		cout << "(1: Insert, 2: search value, 3: Delete, 4: In order, 5: print tree, 6: print height, 7: Exit): ";
		cin >> choice;
		if (choice == 1)
		{
			int value;
			cout << "Enter value: ";
			cin >> value;
			Root = insert(Root, value);
		}
		else if (choice == 2) {
			int ToSearch;
			cout << "Enter value: ";
			cin >> ToSearch;
			Search(Root, ToSearch);
		}
		else if (choice == 3) {
			int ToDelete;
			cout << "Enter value: ";
			cin >> ToDelete;
			deleteNode(Root, ToDelete);
		}
		else if (choice == 4) {
			InOrder(Root);
		}
		else if (choice == 5) {
			printBT(Root);
		}
		else if (choice == 6) {
			height(Root);
		}
		else if (choice == 7) {
			cout << "Exiting....";
			break;
		}
		else
		{
			cout << "Invalid input!!!\n";
			continue;
		}
	}
}