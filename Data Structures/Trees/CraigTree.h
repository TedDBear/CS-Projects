#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <string>
using namespace std;

template<typename T>
class TreeNode
{
public:
	T data;
	TreeNode<T>* left, * right;

	TreeNode() {};
	TreeNode(const T& data)
	{
		this->data = data;
	}
	bool isLeaf()
	{
		if (left == nullptr && right == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Traverses the tree in level order
	void levelOrderTraversal(TreeNode<T>* root)
	{
		queue<TreeNode<T>*> treeNodeQueue;
		int nodeCounter = 1;

		treeNodeQueue.push(root);
		

		while (!treeNodeQueue.empty())
		{
			TreeNode<T>* current;
			current = treeNodeQueue.front();
			treeNodeQueue.pop();
			cout << current->data << ", ";
			if (current->left != nullptr)
			{
				nodeCounter++;
				treeNodeQueue.push(current->left);
			}
			if (current->right != nullptr)
			{
				nodeCounter++;
				treeNodeQueue.push(current->right);
			}
			
		}
		
	}

	// Traverses the tree in alphabetic/numeric order (assuming it is a binary search tree)
	void inOrderTraverse(TreeNode<T>* root)
	{
		if (root != nullptr)
		{
			inOrderTraverse(root->left);
			cout << root->data << ", ";
			inOrderTraverse(root->right);
		}
	}

	// counts number of leaves in a tree
	int getLeafCount(TreeNode<T>* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int leafCount = 0;
		stack<TreeNode<T>*> nodeStack;
		nodeStack.push(root);

		while (!nodeStack.empty())
		{
			TreeNode<T>* current = nodeStack.top();

			nodeStack.pop();

			if (current->left != nullptr)
			{
				nodeStack.push(current->left);
			}
			if (current->right != nullptr)
			{
				nodeStack.push(current->right);
			}
			if (current->isLeaf())
			{
				leafCount++;
			}
		}
		return leafCount;
	}

	// inserts a node in alphabetic/numeric order
	TreeNode<T>* insertBTSNode(TreeNode<T>* root, T value)
	{
		if (root == nullptr)
		{
			root = new TreeNode<T>(value);
		}
		else if (value < root->data)
		{
			root->left = insertBTSNode(root->left, value);
		}
		else
		{
			root->right = insertBTSNode(root->right, value);
		}
		return root;
	}

	// gets the level of a value in a tree
	int getNodeLevel(TreeNode<T>* root, T targetValue, int level)
	{
		if (root == nullptr)
		{
			return -1;
		}
		if (root->data == targetValue)
		{
			return level;
		}
		int leftLevel = getNodeLevel(root->left, targetValue, level + 1);
		int rightLevel = getNodeLevel(root->right, targetValue, level + 1);

		if (leftLevel == -1)
		{
			return rightLevel;
		}

		else
		{
			return leftLevel;
		}
	}
};

template<typename T>
class nAryTreeNode
{
public:
	T data;
	vector<nAryTreeNode<T>*> childrenLinks;

	nAryTreeNode() {};
	nAryTreeNode(const T& data)
	{
		this->data = data;
	}
	bool isLeaf()
	{
		if (left == nullptr && right == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

