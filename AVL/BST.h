#pragma once
#include "TvSeries.h"
#include <string>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class BST 
{

public:

	struct Node {

		TvSeries value;
		Node* left;
		Node* right;
		int height;

		Node(TvSeries x) : value(x), height(1), left(nullptr), right(nullptr) {}

	};

	//Tree functions
	BST() : root(nullptr) {}
	~BST();
	Node* insert(Node* root, TvSeries value);
	void inorderTraversal(Node* root);
	void levelorderTraversal(Node* root);
	void deleteTree(Node* root);

	//Search functions
	Node* search(Node* root, string name);
	Node* searchRandom(Node* root);
	void find(Node* root, string name, set<Node*>&);

	//AVL functions
	void updateHeight(Node* root);
	int balanceFactor(Node* root);
	Node* balance(Node* root, int balanceFactor);
	Node* rotateLeft(Node* root);
	Node* rotateRight(Node* root);

	//Utility functions
	int getHeight(Node* root);
	Node* getRoot();

private:

	Node* root;


};

