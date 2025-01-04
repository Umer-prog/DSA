#include <iostream>
#include <queue>
using namespace std;

struct Node {
	string value;
	int h = 0;
	int level;
	Node* left;
	Node* right;
};

Node* ADD(Node* node, string value) {
	if (node == NULL) {
		Node* temp = new Node;
		temp->value = value;
		temp->left = NULL;
		temp->right = NULL;

		return(temp);
	}
	//Else, do level order traversal until we find an empty
	// place, i.e. either left child or right child of some
	// node is pointing to NULL.
	queue<Node*> q;
	q.push(node);

	while (!q.empty()) {
		Node* temp1 = q.front();
		q.pop();

		if (temp1->left != NULL)
			q.push(temp1->left);
		else {
			temp1->left = ADD(temp1->left, value);
			return node;
		}

		if (temp1->right != NULL)
			q.push(temp1->right);
		else {
			temp1->right = ADD(temp1->right, value);
			return node;
		}
	}
}

//umer print
void printt(const string& prefix, Node* parent, bool isLeft, bool isRoot) {
	if (parent == NULL)
		return;

	if (isRoot) {
		cout << "RT----";
	}
	else {
		cout << prefix <<
			(isLeft ? "(L)|----" : "(R)L----");
	}
	// print the value of the node
	cout << parent->value << endl;

	// enter the next tree level - left and right branch
	printt(prefix + (isLeft ? "   | " : "    "),
		parent->left, true, false);
	printt(prefix + (isLeft ? "   | " : "    "),
		parent->right, false, false);
}
// pass the root node of your binary tree
void printBT(Node* node) {
	printt("", node, false, true);
}

bool Equal(Node* a, Node* b) {
	if (a == nullptr && b == nullptr) {
		return true;
	}

	if (a != nullptr && b != nullptr) {
		if (a->value == b->value) {
			return (Equal(a->left, b->left) && Equal(a->right, b->right));
		}
	}
	return false;
}

bool Same(Node* a, Node* b) {
	if (a == nullptr && b == nullptr) {
		return true;
	}

	if (a != nullptr && b != nullptr)
	{
		return (Same(a->left, b->left) && Same(a->right, b->right));
	}
	return false;
}

bool Mirror(Node* a, Node* b) {
	if (a == nullptr && b == nullptr) {
		return true;
	}

	if (a != nullptr && b != nullptr)
	{
		if (a->value == b->value) {
			return (Mirror(a->left, b->right) && Mirror(a->right, b->left));
		}
	}
	return false;
}


int main() {
	Node* Root1 = nullptr;
	Node* Root2 = nullptr;

	Root1 = ADD(Root1, "9");
	Root1 = ADD(Root1, "17");
	Root1 = ADD(Root1, "20");
	Root1 = ADD(Root1, "19");
	Root1 = ADD(Root1, "18");
	Root1 = ADD(Root1, "95");
	Root1 = ADD(Root1, "55");
	Root1 = ADD(Root1, "75");
	Root1 = ADD(Root1, "29");
	Root1 = ADD(Root1, "85");

	Root2 = ADD(Root2, "9");
	Root2 = ADD(Root2, "20");
	Root2 = ADD(Root2, "17");
	Root2 = ADD(Root2, "55");
	Root2 = ADD(Root2, "95");
	Root2 = ADD(Root2, "18");
	Root2 = ADD(Root2, "19");
	Root2 = ADD(Root2, "85");
	Root2 = ADD(Root2, "29");
	Root2 = ADD(Root2, "75");

	int choice;
	while (true)
	{
		cout << "(1: Insert, 2: Insert in 2nd tree, 3: equal, 4: same, 5: mirror, 6: print1,7: print 2): ";
		cin >> choice;
		if (choice == 1)
		{
			string value;
			cout << "Enter value: ";
			cin >> value;
			Root1 = ADD(Root1, value);
		}
		if (choice == 2)
		{
			string value;
			cout << "Enter value: ";
			cin >> value;
			Root2 = ADD(Root2, value);
		}
		else if (choice == 3) {
			if (Equal(Root1, Root2)) {
				cout << "equal" << endl;
			}
			else if (Equal(Root1, Root2) == false) {
				cout << "unequal" << endl;
			}
		}
		else if (choice == 4) {
			if (Same(Root1, Root2)) {
				cout << "same" << endl;
			}
			else if (Same(Root1, Root2) == false) {
				cout << "not same" << endl;
			}
		}
		else if (choice == 5) {
			if (Mirror(Root1, Root2)) {
				cout << "mirror" << endl;
			}
			else if (Mirror(Root1, Root2) == false) {
				cout << "not mirror" << endl;
			}
		}
		if (choice == 6)
		{
			printBT(Root1);
		}
		if (choice == 7)
		{
			printBT(Root2);
		}
	}
}
