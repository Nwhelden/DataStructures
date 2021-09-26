#include "BST.h"

BST::~BST() {

	deleteTree(root);

}

void BST::deleteTree(Node* root) {

	if (root == nullptr) {

		return;

	}
	else {

		//nodes are stored on the heap
		//uses a postorder traversal to visit each node, then deletes
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;

	}

}

BST::Node* BST::insert(Node* root, TvSeries value) {

	//base case, reached c
	if (root == nullptr) {

		root = new Node(value);
		
		return new Node(value);

	}

	//recurisvely move down desired path depending on comparison of keys
	else if (value.name < root->value.name) {

		root->left = insert(root->left, value);

	}
	else {

		root->right = insert(root->right, value);

	}

	//after traveling down a path and inserting a node, when the base case is reached we travel back up and check balance factors
	//new node was added, so update the height of the current node in the path
	updateHeight(root);

	//before returning and moving up to the next level, check the ancestor of the inserted node for imbalance 
	root = balance(root, balanceFactor(root));

	return root;

}

//calling updateHeight and balance outside of insertion would take O(n) time; requires full traversal
//calling inside insertion takes O(logn) time; only checks nodes in path of recursive calls 


int BST::getHeight(Node* root) {

	if (root == nullptr) {

		return 0;

	}
	else {

		return root->height;

	}

}

void BST::updateHeight(Node* root) {

	int lHeight = getHeight(root->left);
	int rHeight = getHeight(root->right);
	
	//height of the root node is the height of the + 1
	root->height = max(lHeight, rHeight) + 1;

}

int BST::balanceFactor(Node* root) {

	if (root == nullptr) {

		return 0;

	}
	else {

		//balance factor = height of left subtree - height of right subtree
		//getHeight checks to see if root->left or root->right are nullptrs
		return getHeight(root->left) - getHeight(root->right);

	}

}

BST::Node* BST::balance(Node* root, int bf) {

	//type of rotation used is based on balance factor of parent and child
	if (bf == 2) {

		if (balanceFactor(root->left) == 1) {

			//left left imbalance, fix with right rotation
			root = rotateRight(root);

		}
		else {

			//BF of left child is -1; left right imbalance, fix with left right rotation
			//first perform left rotation on the left child, then right rotation on the root of the subtree (get new root after rotating)
			root->left = rotateLeft(root->left);
			root = rotateRight(root);

		}

	}
	else if (bf == -2) {

		if (balanceFactor(root->right) == -1) {

			//right right imbalance, fix with left rotation
			root = rotateLeft(root);

		}
		else {

			//BF of right child is +1; right left imbalance, fix with right left rotation
			//first perform right rotation on the right child, then left roation on the root
			root->right = rotateRight(root->right);
			root = rotateLeft(root);

		}

	}

	//root of tree passed in may change depending on the pivot, so return the new root
	return root;

}

BST::Node* BST::rotateLeft(Node* root) {

	//A is the root of the subtree, B is its child, and C is its possible grandchild 
	//C is the left subtree of B
	Node* A = root;
	Node* B = A->right;
	Node* C = B->left;
	B->left = A;
	A->right = C;

	//A and B positions pivoted by 1, so update height 
	updateHeight(A);
	updateHeight(B);

	//after rotating, B becomes the new root of the subtree
	return B;

}

BST::Node* BST::rotateRight(Node* root) {

	//when rotating parent (A) with child (B), need to account for right subtree (C) of the child
	//when B becomes new root, subtree C is inherited by A to prevent overlap
	Node* A = root;
	Node* B = A->left;
	Node* C = B->right;
	B->right = A;
	A->left = C;

	updateHeight(A);
	updateHeight(B);

	return B;

}

void BST::inorderTraversal(Node* root) { 

	if (root == nullptr) {

		return;

	}
	else {

		inorderTraversal(root->left);
		root->value.Print();
		inorderTraversal(root->right);

	}

}

void BST::levelorderTraversal(Node* root) {

	if (root == nullptr) {

		return;

	}
	else {

		queue<Node*> q;
		q.push(root);

		while (!q.empty()) {

			Node* current = q.front();
			current->value.Print();
			q.pop();

			if (current->left != nullptr) {

				q.push(current->left);

			}

			if (current->right != nullptr) {

				q.push(current->right);

			}

		}

	}

}

BST::Node* BST::search(Node* root, string name) {

	//bases cases; stop searching down path when what is searched for is found or it does not exist
	//nullptr returned when the desired key does not exist in the tree
	if (root == nullptr || root->value.name == name) {

		return root;

	}
	else if (name < root->value.name) {

		return search(root->left, name);

	}
	else {

		return search(root->right, name);

	}

}

void BST::find(Node* root, string name, set<Node*>& container) {

	//inorder traversal checks every node in the tree
	if (root == nullptr) {

		return;

	}
	else {

		//if a node contains part of what is being found, add it to the container 
		find(root->left, name, container);
		if (root->value.name.find(name) != string::npos) {

			container.insert(root);

		}
		find(root->right, name, container);

	}

}

BST::Node* BST::searchRandom(Node* root) {

	if (root == nullptr) {

		return nullptr;

	}

	//randomly generates a number between 0 and the height of the tree
	srand(time(0));
	int levels = std::rand() % getHeight(root);
	Node* current = root;
	vector<int> path;

	//fills the vector with 1's and 0's
	for (int i = 0; i < levels; i++) {

		int direction = std::rand() % 2;
		path.push_back(direction);

	}

	//vector represents the path to traverse, with 0 = left and 1 = right
	for (int i = 0; i < levels; i++) {

		Node* temp = current;

		if (path[i] == 0) {

			current = current->left;

		}
		else {

			current = current->right;

		}

		//subtree not always garaunteed to be max height, so stop in case of nullptr
		if (current == nullptr) {

			return temp;

		}

	}

	//return the node retrieved from the path
	return current;

}

BST::Node* BST::getRoot() {

	return root;

}