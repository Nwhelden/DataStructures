#include <String>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

//nodes in the linked list begin from 1 like the line editor (one-indexed)
template <typename T>
class LinkedList {

private:

	//each node contains a previous and next pointer (linked list is doubly linked)
	//each node contains a string/char* data type representing a line of text
	struct Node {

		T data;
		Node* next;
		Node* prev;

	};

	//pointer to the first node in the list
	Node* head;

	//pointer to the last node in the list
	Node* tail;

	//keeps track of the number of nodes/lines stored in the list
	unsigned int size;

public:

	//constructs a Linked List, where there are initially no nodes
	LinkedList() {

		size = 0;
		head = nullptr;
		tail = nullptr;

	}

	//deletes all nodes dynamically allocated in the Linked List
	~LinkedList() {

		if (size != 0) {

			//traverse through the linked list and delete every node until nullptr is reached
			Node* temp = head;
			while (temp != nullptr) {

				//head reassigjed to the next node in the list
				//delete the current head, then repeat
				head = head->next;
				delete temp;
				temp = head;

			}

		}

	}

	//retrieves the node given its position in the linked list
	Node* GetNode(unsigned int index) {

		//can only get a node from a valid index
		//because the linked list is one-indexed, it consists of indicies from 1 to size
		if (0 < index && index <= size) {

			Node* temp = head;
			for (unsigned int i = 1; i < index; i++) {

				//every time the loop iterates, temp points to the next node in the list starting from head
				temp = temp->next;

			}

			//loop stops before reaching the position of the node that is being retrieved, so temp->next is the desired node
			return temp;

		}

	}

	//inserts a new node at the beginning of the list
	void AddHead(T data) {

		//creates a new node with the data
		Node* node = new Node();
		node->data = data;
		node->prev = nullptr;
		node->next = nullptr;

		//if the list is empty, the new node is both the head and tail
		if (size == 0) {

			head = node;
			tail = node;

		}

		//if the list is not empty, head is already pointing to a pre-existing node
		else {

			//connect the new node in front of the node head currently points at, then reassign head to the new node
			node->next = head;
			head->prev = node;
			head = node;

		}

		size++;

	}

	//inserts a new node at the end of the list
	void AddTail(T data) {

		//creates a new node with the data
		Node* node = new Node();
		node->data = data;
		node->prev = nullptr;
		node->next = nullptr;

		//if the list is empty, the new node is both the head and tail
		if (size == 0) {

			head = node;
			tail = node;

		}

		//if the list is not empty, tail is already pointing to a pre-existing node
		else {

			//connect the node after the node tail currently points at, then reassign tail to the new node
			tail->next = node;
			node->prev = tail;
			tail = node;

		}

		size++;

	}

	//inserts a new node before the specified position 
	void AddBefore(int index, T data) {

		//gets a pointer to the current node at index
		Node* nodeBefore = GetNode(index);

		//connects newNode and nodeBefore, and connects newNode to nodeBefore's previous node
		Node* newNode = new Node();
		nodeBefore->prev->next = newNode;
		newNode->prev = nodeBefore->prev;
		newNode->next = nodeBefore;
		nodeBefore->prev = newNode;

		newNode->data = data;

		size++;


	}

	//inserts a new node at the specified position
	void AddNode(int index, T data) {

		//valid line numbers to add at are from 1 to size + 1
		if (0 < index && index <= size + 1) {

			//want to add a node at the beginning of the list
			if (index == 1) {

				AddHead(data);

			}

			//want to add a node at the end of the list, 
			else if (index == size + 1) {

				AddTail(data);

			}

			//adds a node at the index, then shifts the original node to index + 1
			else {

				//because AddBefore is used, the new node is added at the index and the original node 
				//it was added before, along with the rest of the list, is shifted 1 position
				AddBefore(index, data);

			}

		}

	}

	//deletes the node at the front of the list
	void RemoveHead() {

		//can only remove a head if there are elements present
		if (size != 0) {

			//if size = 1, deletes the only element in the list
			if (size == 1) {

				delete head;
				head = nullptr;
				tail = nullptr;

			}

			//delete the node that head was pointing to and reassign head to the current node at the front of the list
			else {

				Node* temp = head->next;
				delete head;
				head = temp;
				head->prev = nullptr;

			}

			size--;

		}

	}

	//deletes the node at the end of the list
	void RemoveTail() {

		//can only delete a tail if the list is not empty
		if (size != 0) {

			//if size = 1, deletes the only element in the list
			if (size == 1) {

				delete tail;
				head = nullptr;
				tail = nullptr;

			}

			//delete the node that tail was pointing to and reassign tail to the current node at the back of the list
			else {

				Node* temp = tail->prev;
				delete tail;
				tail = temp;
				tail->next = nullptr;

			}

			size--;

		}

	}

	//deletes the node at a specified index
	void RemoveNode(int index) {

		//if index is in bounds and the list is not empty, a node can be removed
		if ((size != 0) && (0 < index && index <= size)) {

			//if index is 1, remove the first node in the list (what head points to)
			if (index == 1) {

				RemoveHead();

			}

			//if index is size, remove the last node in the list (what tail points to)
			else if (index == size) {

				RemoveTail();

			}

			//otherwise remove a node between two other nodes
			else {

				//retrieve the node that needs to be removed
				//connect the previous and next node together, then delete the specified node
				Node* node = GetNode(index);
				node->next->prev = node->prev;
				node->prev->next = node->next;
				delete node;

				size--;

			}

		}

	}

	//O(1)
	int GetSize() {

		return size;

	}

	Node* GetHead() {

		return head;

	}

};

class LineEditor {

	//list stores the lines
	LinkedList<string> list;

	//vector stores the line numbers where text was split to a new line (used for searching)
	//vector<int> splitLines;

public:

	//each line in the document can only have up to 80 characters
	//when adding a new line with over 80 characters, additional lines are made to store the excess characters 
	void excessInput(int lineNumber, string remainingText) {

		//80 characters in a line, so the the amount of excess characters / 80 gives the number of additional lines needed
		//round up; even if we don't have 80 excess characters, they still need to be in a separate line
		int excessLines = ceil((double)remainingText.length() / 80);

		string storedText;

		//for loop iterates for every additional line needed to store the input
		for (int i = 0; i < excessLines; i++) {

			if (remainingText.length() <= 80) {

				//when there are less than or 80 characters, no longer need to parse the string
				//only happens at the last iteration of the for loop, so there is no need to change remainingText
				storedText = remainingText;

			}
			else {

				//when there are more than 80 characters, only want the first 80 for the current node being created
				storedText = remainingText.substr(0, 80);
				
				//next iteration will only use the characters remaining (remove the characters being stored)
				remainingText = remainingText.substr(80, remainingText.length() - 80);

			}

			//adds new node at the specified lineNumber
			list.AddNode(lineNumber, storedText);

			//lineNumber is the location of the previous line, where text was split from to the current line
			//last line created from the loop should not have split text
			//splitLines.push_back(lineNumber - 1);

			lineNumber++;

		}

	}

	//inserts a line with the given text at the position lineNumber
	void insertLine(int lineNumber, string text) {

		//linked list and editor are one-indexed, so values are 1 to size inclusive
		//if we want to add a new line after the end of the list, the line number and position of the node will be size + 1
		if (0 < lineNumber && lineNumber <= list.GetSize() + 1) {

			//if the text has more than 80 characters, split the excess to a new line
			if (text.length() > 80) {

				//store everything after the first 80 characters in a new string
				string remainingText = text.substr(80, remainingText.length() - 80);

				//can only store up to 80 characters in a line
				text = text.substr(0, 80);

				//inserts the initial 80 characters first, then creates other lines for the remaining text
				list.AddNode(lineNumber, text);
				excessInput(lineNumber + 1, remainingText);

			}

			//if the text is less than or equal to 80 characters, just makes a single line
			else {

				list.AddNode(lineNumber, text);

			}

		}

	}

	//inserts a line at the end of the linked list
	void insertEnd(string text) {

		//line numbers are from 1 to size, so adding a line at the end would be at position size + 1
		insertLine(list.GetSize() + 1, text);

	}

	//replaces the line at position lineNumber with the given text
	void editLine(int lineNumber, string text) {
			
		//need a valid line number to edit
		if (0 < lineNumber && lineNumber <= list.GetSize()) {

			//since a line is constrained to 80 characters of text, if the edited text is greater than 80 characters
			//the remaining text needs a new line
			if (text.length() > 80) {

				//separates the first 80 characters from the rest of the given text
				string remainingText = text.substr(80, remainingText.length() - 80);
				string text = text.substr(0, 80);

				//the other characters exceedng 80 are added to a new line
				excessInput(lineNumber + 1, remainingText);

			}

			//edits the text at the specified line
			list.GetNode(lineNumber)->data = text;

		}
	}

	//deletes the line at the given position
	void deleteLine(int lineNumber) {

		//linked list is one-indexed as well, so position of line = position of node
		list.RemoveNode(lineNumber);

	}

	void printDoc() {

		auto temp = list.GetHead();
		int lineNumber = 1;

		while (temp != nullptr) {

			cout << lineNumber << " " << temp->data << endl;

			//iterates the temp pointer to the next null (stops when next = nullptr)
			temp = temp->next;
			lineNumber++;

		}

	}

	//prints the results of a search
	void printSearch(map<int, string>& textLocations) {

		//iterates through the entire map and prints the key (line number) and value (line)
		for (auto iter = textLocations.begin(); iter != textLocations.end(); ++iter) {

			cout << iter->first << " " << iter->second << endl;

		}

	}

	//line by line search for text if text is less than or equal to 80 characters
	void lineSearch(string text, map<int, string>& textLocations) {

		auto temp = list.GetHead();

		//start at 1 and end at size to keep track of line numbers (one-indexed)
		for (unsigned int i = 1; i <= list.GetSize(); i++) {

			if (temp->data.find(text) != string::npos) {

				textLocations.emplace(i, temp->data);

			}

			//every time the loop iterates, temp points to the next node in the list starting from head
			temp = temp->next;

		}

	}

	//merges lines then searches for text if text is greater than 80 characters
	void mergeSearch(string text, map<int, string>& textLocations, int searchLines) {

		auto temp = list.GetHead();

		//REFACTOR: simplify list.GetSize() - searchLines + 1
		//loop gets every combination of "searchLines" lines 
		//outer loop stops "searchLine" lines before the last line to prevent the inner loop from going out of bounds
		for (int i = 1; i <= list.GetSize() - searchLines + 1; i++) { //O(n) n = number of lines

			int k = i;
			auto temp2 = temp;
			string mergeText;
			vector<string> lines;

			//for loop goes through a combination of "searchLines" consecutive lines
			//loop iterates searchLines times and combines the lines at index k
			for (int j = 0; j < searchLines; j++) { //O(q) q = searchLines

				mergeText += temp2->data;

				//vector used to store each line's data to prevent traversing through the list again
				lines.push_back(temp2->data);

				//need a separate Node* to keep track of the 
				temp2 = temp2->next;
				k++;

			}

			//if the combination of consecutive lines contains the text being searched for, store the line numbers 
			//and lines that contain the text
			if (mergeText.find(text) != string::npos) { //O(m) m = size of string

				//every line between i and k - 1 inclusive contains the searched text
				int rangeMin = i;
				int rangeMax = k;

				for (rangeMin; rangeMin < rangeMax; rangeMin++) { //O(q) 

					//map used to store the lines that contain the searched text, with line number as the key
					//use rangeMin - i to access line values corresponding to line number rangeMin, because line numbers start at
					//rangeMIn = i while line values are stored starting from a 0-index
					textLocations.emplace(rangeMin, lines[rangeMin - i]);

				}

			}

			//loop iterates, so temp points to the next node
			temp = temp->next;

		}

	}

	//prints the line numbers and lines that contain the given text
	void searchText(string text) {

		//number of lines needed (at a minimum) to store what is being searched
		int searchLines = ceil((double)text.length() / 80);

		//map stores the lines and line numbers where the searched text is located
		//map used instead of a vector to prevent duplicate lines from being stored when using mergeSearch
		map<int, string> textLocations;

		//can only search if elements are present and if the searched text doesn't exceed what can possibly be stored
		if (0 < list.GetSize() && searchLines <= list.GetSize()) {

			//if the text being searched fits into 1 line, do a line by line search
			if (searchLines == 1) {

				lineSearch(text, textLocations);

			}

			//if the text being searched fits into multiple lines, merge nodes then search
			else {

				mergeSearch(text, textLocations, searchLines);

			}

			//print the contents of textLocations
			//if no contents exist, then what was searched was not found
			if (textLocations.size() != 0) {

				printSearch(textLocations);

			}
			else {

				cout << "not found" << endl;

			}


		}
		else {

			cout << "not found" << endl;

		}

	}

};

int main() {

	bool endProgram = false;
	int commandChar;
	string command;
	int lineNumber;
	string text;

	//creates a line editor
	LineEditor editor;

	while (!endProgram) {

		//input is in the form of: command line# "text"
		//cin only extracts until the space, so the first string stored is the command
		cin >> command;

		//based on the command, invoke the line editor
		if (command == "insertEnd") {

			//insertEnd command is in the form of: command "text"
			//getline retrieves the rest of the input until the newline character
			//substring removes the space fro mthe first character and the quotations from the second and last character of the text
			getline(cin, text);
			text = text.substr(2, text.size() - 3); //?? change?

			editor.insertEnd(text);

		}

		else if (command == "insert") {

			//insert command is in the form of: command line# "text"
			cin >> lineNumber;
			getline(cin, text);
			text = text.substr(2, text.size() - 3);

			editor.insertLine(lineNumber, text);
		}

		else if (command == "delete") {

			//delete command is in the form of: command line#
			cin >> lineNumber;

			editor.deleteLine(lineNumber);

		}
		
		else if (command == "edit") {

			//edit command is in the form of: command line# "text"
			cin >> lineNumber;
			getline(cin, text);
			text = text.substr(2, text.size() - 3);

			editor.editLine(lineNumber, text);

		}

		else if (command == "print") {

			editor.printDoc();

		}

		else if (command == "search") {

			//search command is in the form of: command "text"
			getline(cin, text);
			text = text.substr(2, text.size() - 3);

			editor.searchText(text);

		}

		else if (command == "quit") {

			endProgram = true;

		}

	}

	return 0;

}