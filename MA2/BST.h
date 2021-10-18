#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
using namespace std;


/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
	T value;
	Node* left;
	Node* right;

	Node(T val) {
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}

	~Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {

protected:
	Node<T>* _root;         // Root of the tree nodes

	/* Add new T val to the tree */
	void addHelper(Node<T>* root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	/* Print tree out in inorder (A + B) */
	void printInOrderHelper(Node<T>* root) {
		if (!root) return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	/* Return number of nodes in tree */
	int nodesCountHelper(Node<T>* root) {
		if (!root) {
			return 0;
		}
		else {
			return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
		}
	}

	/* Return height of tree (root == nullptr -> 0) */
	int heightHelper(Node<T>* root) {
		if (!root) {
			return -1;
		}
		else {
			return 1 + max(heightHelper(root->left), heightHelper(root->right));
		}
	}

	/* Delete a given <T> value from tree */
	bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		if (!current) return false;
		if (current->value == value) {
			if (current->left == nullptr || current->right == nullptr) {
				Node<T>* temp = current->left;
				if (current->right) temp = current->right;
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					this->_root = temp;
				}
			}
			else {
				Node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			deleteValueHelper(current, current->right, value);
	}

	/*
	int findHeight(Node<T>* root) {
		/*
		
		int lH = 0;
		int rH = 0;
		int max = 0;

		//if left/right subtrees are not null, findHeight on them
		if (root->left != NULL)
		{
			lH = findHeight(root->left);
		}

		if (root->right != NULL)
		{
			rH = findHeight(root->right);
		}

		//determine which is larger
		if (lH >= rH) 
		{
			max = lH;
		}
		else
		{
			max = rH;
		}
		//add one to the maximum and return
		max = max + 1;
		return max;
		
	}
	*/

	void printAtDepth(Node<T>* root, int depth)
	{
		if(root==NULL) {
			return;
		}
		if (depth == 1)
		{
			cout << root->value << " ";
			return;
		}
		if(depth > 1)
		{
			printAtDepth(root->left, depth - 1);
			printAtDepth(root->right, depth - 1);
		}



	}
	/********************************* PUBLIC API *****************************/
public:

	BST() : _root(nullptr) { }               // Basic initialization constructor

	/**
	 * Destructor - Needs to free *all* nodes in the tree
	 * TODO: Implement Destructor
	 */
	~BST() {
	    //cout << "TODO: Implement Destructor" << endl;

        //calls the recursive destructor function
		this->recursiveDestructor(_root);
	}

	void recursiveDestructor(Node<T>* root) {
		recursiveDestructor(root->left);
		recursiveDestructor(root->right);

		delete root;
	}

	/* Public API */
	void add(T val) {
		if (this->_root) {
			this->addHelper(this->_root, val);
		}
		else {
			this->_root = new Node<T>(val);
		}
	}

	void print() {
		printInOrderHelper(this->_root);
	}

	/**
	 * Print the nodes level by level, starting from the root
	 * TODO: Implement printLevelOrder
	 */
	void printLevelOrder() {
		//cout << "TODO: Implement printLevelOrder" << endl;

		int max = heightHelper(_root);
		for(int i=1; i<=max; i=i+1)
		{
			//do we need an if statement to protect against NULL pcur?
			printAtDepth(_root, i);

			cout << endl;
		}
	}

	int nodesCount() {
		return nodesCountHelper(this->_root);
	}

	int height() {
		return heightHelper(this->_root);
	}

	/**
	 * Print the maximum path in this tree
	 * TODO: Implement printMaxPath
	 */
	void printMaxPath() {
		//cout << "TODO: Implement printMaxPath" << endl;

		//call helper function
		vector<int> path = longPathVector(_root);
		for(int i = 0; i < path.size(); i++)
		{
			cout << path[i] << " ";
		}

		cout << endl;

		return;
	}

	vector<int> longPathVector(Node<T>* root)
	{
		if(root == NULL)
		{
			vector<int> start;
			return start;
		}

		vector<int> rPath = longPathVector(root->right);

		vector<int> lPath = longPathVector(root->left);

		if(lPath.size() > rPath.size()) {
			lPath.push_back(root->value);

			return lPath;
		}
		else {
			rPath.push_back(root->value);

			return rPath;
		}

		
	}

	bool deleteValue(T value) {
		return this->deleteValueHelper(nullptr, this->_root, value);
	}

	/**
	 * Find if the BST contains the value
	 * TODO: Implement contains
	 */
	bool contains(T value) {
	    //cout << "TODO: Implement contains" << endl;
		Node<T>* pCur = _root;
		
		while(pCur != NULL)
		{
			if(pCur->value == value) {
				return 1;
			}
			if(value < pCur->value) {
				pCur = pCur->left;
			}
			else {
				pCur = pCur->right;
			}

		}

		return 0;
	}
};

#endif

