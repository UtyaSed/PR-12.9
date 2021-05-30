#include <iostream>
using namespace std;
typedef int Info;
struct Node
{
	Node* left,
		* right;
	Info info;
};

Node* CreateTree(int nodeCount);
int Count(Node* root);
Node* BinarySearchInsert(Node*& root, Info value, bool& found);
void PrintTree(Node* root, int level);
void RightRotation(Node*& root);
void LeftRotation(Node*& root);
int Height(Node* root);
int BFactor(Node* root);
void BalanceHeight(Node*& root);
Node* BinarySearchDelete(Node* root, Info value);

int main()
{
	int N;
	cout << "Enter nodes count: "; cin >> N;


	Node* root = NULL;
	Info value;
	bool found = false;
	for (int i = 0; i < N; i++)
	{
		cout << "value: "; cin >> value;
		BinarySearchInsert(root, value, found); 
	}

	cout << endl;
	PrintTree(root, 0);
	cout << endl;

	cout << "Balanced tree:" << endl << endl;
	BalanceHeight(root);

	cout << endl;
	PrintTree(root, 0);
	cout << endl;

	int dn;
	cout << "enter node value you want to delete:"; cin >> value;
	BinarySearchDelete(root, value);

	cout << endl;
	PrintTree(root, 0);
	cout << endl;


	cout << "nodes count: " << Count(root) << endl;
	return 0;
}

Node* CreateTree(int nodeCount)
{
	if (nodeCount == 0)
		return NULL;
	else
	{
		Node* newNode = new Node;
		cout << " Enter node value: ";
		cin >> newNode->info;
		int leftCount = nodeCount / 2;
		int rightCount = nodeCount - leftCount - 1;
		newNode->left = CreateTree(leftCount);
		newNode->right = CreateTree(rightCount);
		return newNode;
	}

}

int Count(Node* root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + Count(root->left) + Count(root->right);
}

Node* BinarySearchInsert(Node*& root, Info value, bool& found)
{
	if (root == NULL)
	{
		root = new Node;
		root->info = value;
		root->left = NULL;
		root->right = NULL;
		found = false;
		return root;
	}
	else
		if (value == root->info)
		{
			found = true;
			return root;
		}
		else
			if (value < root->info)
				return BinarySearchInsert(root->left, value, found);
			else
				return BinarySearchInsert(root->right, value, found);
}

void RightRotation(Node*& root)
{
	Node* tmp1 = root->left;
	Node* tmp2 = tmp1->right;
	tmp1->right = root; 
	root->left = tmp2; 
	root = tmp1; 
}
void LeftRotation(Node*& root)
{
	Node* tmp1 = root->right;
	Node* tmp2 = tmp1->left;
	tmp1->left = root; 
	root->right = tmp2; 
	root = tmp1; 
}
int Height(Node* root)
{
	if (root == NULL)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);
	return (hL > hR ? hL : hR) + 1;
}
int BFactor(Node* root)
{
	return Height(root->right) - Height(root->left);
}
void BalanceHeight(Node*& root)
{
	if (root != NULL)
	{
		while (BFactor(root) >= 2)
		{
			if (BFactor(root->right) < 0)
				RightRotation(root->right);
			LeftRotation(root);
		}
		while (BFactor(root) <= -2)
		{
			if (BFactor(root->left) > 0)
				LeftRotation(root->left);
			RightRotation(root);
		}
		BalanceHeight(root->left);
		BalanceHeight(root->right);
	}
}

Node* FindMax(Node* root)
{
	if (root->right != NULL)
		return FindMax(root->right);
	else
		return root;
}

Node* BinarySearchDelete(Node* root, Info value)
{
	if (NULL == root) return NULL; 
	if (root->info == value)
	{
		if (NULL == root->left && NULL == root->right) 
		{
			delete root;
			return NULL;
		}
		if (NULL == root->right && root->left != NULL) 
		{ 
			Node* temp = root->left;
			delete root;
			return temp;
		}
		if (NULL == root->left && root->right != NULL)
		{ 
			Node* temp = root->right;
			delete root;
			return temp;
		}
	
		root->info = FindMax(root->left)->info;
		root->left = BinarySearchDelete(root->left, root->info);
		return root;
	}
	
	if (value < root->info)
	{ 
		root->left = BinarySearchDelete(root->left, value);
		return root;
	}
	if (value > root->info)
	{
		root->right = BinarySearchDelete(root->right, value);
		return root;
	}
	return root;
}

void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << " ";
		cout << root->info << endl;
		PrintTree(root->left, level + 1);
	}
}