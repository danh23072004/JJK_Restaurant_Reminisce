#include "main.h"

class Command
{
public:
	void LAPSE(string name);
	void KOKUSEN();
	void KEITEIKEN(int num);
	void HAND();
	void LIMITLESS(int num);
	void CLEAVE(int num);
};

class IO
{
public:
	static void readInput(const string, string&, string&);
	static void writeOutput();
};

void IO::readInput(const string inputStr, string& command, string& argument)
{
	stringstream ss(inputStr);
	ss >> command >> argument;
	cout << command << ' ' << argument << endl;
}

void IO::writeOutput()
{
}

// this function will process one command at a time
void process(string command, string argument)
{
	Command* cmd = new Command();
	if (command == "MAXSIZE")
	{

	}
	if (command == "LAPSE")
	{
		cmd->LAPSE(argument);
	}
	else if (command == "KOKUSEN")
	{
		cmd->KOKUSEN();
	}
	else if (command == "KEITEIKEN")
	{
		cmd->KEITEIKEN(stoi(argument));
	}
	else if (command == "HAND")
	{
		cmd->HAND();
	}
	else if (command == "LIMITLESS")
	{
		cmd->LIMITLESS(stoi(argument));
	}
	else if (command == "CLEAVE")
	{
		cmd->CLEAVE(stoi(argument));
	}
}

void simulate(string filename)
{
	ifstream file(filename);
	string inputStr = "", command, argument;
	if (file.is_open())
	{
		while (getline(file, inputStr))
		{
			IO::readInput(inputStr, command, argument);
			process(command, argument);
		}
	}
	return;
}

class EncodingNode
{
public:
	char c;
	int freq;
	int priority;
	EncodingNode* left;
	EncodingNode* right;
	bool containChar;
	EncodingNode(char, int, int);
	EncodingNode(char, int, int, EncodingNode*, EncodingNode*, bool);
	int calculateBalanceFactor(EncodingNode*);
	friend class Huffman_AVL_Tree;
};

class Huffman_AVL_Tree
{
private:
	void rotateLeft(EncodingNode*&);
	void rotateRight(EncodingNode*&);
	void leftBalance(EncodingNode*&);
	void rightBalance(EncodingNode*&);
	EncodingNode* findUnbalancedNode(EncodingNode*);
public:
	void balanceTree(EncodingNode*);
};

class Customer
{
private:
	int ID;
	string originalName;
	string encodedName;
	vector<pair<char, int>> listOfChar;
	vector<pair<char, int>> generateOriginalName(string name);
	vector<pair<char, int>> generateCaesarName(const vector<pair<char, int>>&);
	void encodingCaesar(vector<pair<char, int>>&);
	bool compareFreq(const std::pair<char, int> a, const std::pair<char, int> b);
	bool compareEncodingNode(const EncodingNode* a, const EncodingNode* b);
	void encodingHuffmanAVL();
public:
	int getID();
	Customer(string);
	string getEncodedName();
	
};

struct Comparator
{
	bool operator()(const std::pair<char, int> a, const std::pair<char, int> b);
	bool operator()(const EncodingNode* a, const EncodingNode* b);
};

class GojoRestaurant
{
private:
	int MAXSIZE;
public:
	GojoRestaurant(int);
};

class SukunaRestaurant
{
private:
	int MAXSIZE;
public:
	SukunaRestaurant(int);
};

/* COMMAND */

void Command::LAPSE(string name)
{
	Customer* customer = new Customer(name);

}

void Command::KOKUSEN()
{
}

void Command::KEITEIKEN(int num)
{
}

void Command::HAND()
{
}

void Command::LIMITLESS(int num)
{
}

void Command::CLEAVE(int num)
{
}

/* CUSTOMER */

// used in sortListOfChar for sorting
bool Customer::compareFreq(const pair<char, int> a, const pair<char, int> b)
{
	if (a.second < b.second)
		return true;
	else if (a.second == b.second)
	{
		if (('a' <= a.first && a.first  <= 'z') && ('A' <= b.first && b.first <= 'Z'))
			return true;
		else if (('a' <= b.first && b.first <= 'z') && ('A' <= a.first && a.first <= 'Z'))
			return false;
		else
			return a.first < b.first;
	}
	return false;
}

bool Customer::compareEncodingNode(const EncodingNode* a, const EncodingNode* b)
{
	if (a->freq < b->freq)
		return true;
}

void Customer::encodingHuffmanAVL()
{
	// create a vector of EncodingNode* to store the list of character using for initialize the priority queue
	vector<EncodingNode*> listNode;
	priority_queue<EncodingNode*, vector<EncodingNode*>, Comparator> pq(listNode.begin(), listNode.end());
	for (int i = 0; i < listOfChar.size(); i++)
	{
		EncodingNode* node = new EncodingNode(listOfChar[i].first, listOfChar[i].second, i);
		pq.push(node);
	}
	int countNewNode = 0;
	Huffman_AVL_Tree checkTree;

	while (pq.size() > 1)
	{
		EncodingNode* node1 = pq.top();
		pq.pop();
		EncodingNode* node2 = pq.top();
		pq.pop();
		EncodingNode* newNode = new EncodingNode('0', node1->freq + node2->freq, listOfChar.size() + countNewNode++, node1, node2, false);
		checkTree.balanceTree(newNode);
		// Then balance the tree of newNode (This part will be implemented later)
		pq.push(newNode);
	}
}

vector<pair<char, int>> Customer::generateOriginalName(string name)
{
	// create a vector listchar contains frequency of each character in originalName
	vector<pair<char, int>> listchar;
	sort(name.begin(), name.end());
	while (name != "")
	{
		char c = name[0];
		int freq = count(name.begin(), name.end(), c);
		name.erase(remove(name.begin(), name.end(), c), name.end());
		listchar.push_back(make_pair(c, freq));
	}

	return listchar;
}

vector<pair<char, int>> Customer::generateCaesarName(const vector<pair<char, int>>&)
{
	vector<pair<char, int>> newCustomerName;

	return vector<pair<char, int>>();
}

int Customer::getID()
{
	return ID;
}

Customer::Customer(string name) : originalName(name)
{
	encodedName = "";
	// Create a vector listchar contains frequency of each character in originalName
	listOfChar = generateOriginalName(originalName);
	// Encoding the name using Caesar Cipher
	//vector<pair<char, int>> encodeCaesar = encodingCaesar(listOfChar);
	// Create a vector listchar contains frequency of each character in encodedName
	encodingCaesar(listOfChar);
	// Sort the list of character by frequency
	function <bool(pair<char, int>, pair<char, int>)> compare = [&](pair<char, int> a, pair<char, int> b) { return compareFreq(a, b); };
	sort(listOfChar.begin(), listOfChar.end(), compare);
	// Encoding the name using Huffman AVL Tree
	encodingHuffmanAVL();
}

string Customer::getEncodedName()
{
	return encodedName;
}

void Customer::encodingCaesar(vector<pair<char, int>>& listchar)
{
	// encoding
	vector<pair<char,int>> newCustomerName;
	char newChar;
	int shift = 0;
	for (int i = 0; i < listchar.size(); i++)
	{
		shift = listchar[i].second % 26;
		if (('a' <= listchar[i].first && listchar[i].first <= 'z') && (listchar[i].first + listchar[i].second > 'z'))
		{
			newChar = 'a' + (listchar[i].first + listchar[i].second - 'z' - 1);
		}
		else if (('A' <= listchar[i].first && listchar[i].first <= 'Z') && (listchar[i].first + listchar[i].second > 'Z'))
		{
			newChar = 'a' + (listchar[i].first + listchar[i].second - 'Z' - 1);
		}
		else
		{
			newChar = listchar[i].first + listchar[i].second;
		}
		// check if newChar is already in newCustomerName and add the frequency
		for (pair<char, int> p : newCustomerName)
		{
			if (p.first == newChar)
			{
				p.second += listchar[i].second;
				break;
			}
		}
		newCustomerName.push_back(make_pair(newChar, listchar[i].second));
	}
	listchar = newCustomerName;
}

/* GOJO RESTAURANT */

GojoRestaurant::GojoRestaurant(int size) : MAXSIZE(size)
{

}

/* SUKUNA RESTAURANT */

SukunaRestaurant::SukunaRestaurant(int size) : MAXSIZE(size)
{

}

/* HUFFMAN AVL TREE */

void Huffman_AVL_Tree::balanceTree(EncodingNode* root)
{
	// check if the tree is balanced
	int balanceFactor = root->calculateBalanceFactor(root);
	int countRotation = 0;
	while (balanceFactor != 0 && countRotation < 3)
	{
		if (balanceFactor > 1)
		{
			leftBalance(root);
		}
		else if (balanceFactor < -1)
		{
			rightBalance(root);
		}
		countRotation++;
	}
}

void Huffman_AVL_Tree::rotateLeft(EncodingNode*& root)
{
	EncodingNode* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	root = newRoot;
}

void Huffman_AVL_Tree::rotateRight(EncodingNode*& root)
{
	EncodingNode* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	root = newRoot;
}

void Huffman_AVL_Tree::leftBalance(EncodingNode*& root)
{
	if (root->calculateBalanceFactor(root->left) > 0)
	{
		rotateLeft(root);
	}
	else
	{
		rotateRight(root->left);
		rotateLeft(root);
	}
}

void Huffman_AVL_Tree::rightBalance(EncodingNode*& root)
{
	if (root->calculateBalanceFactor(root->right) < 0)
	{
		rotateRight(root);
	}
	else
	{
		rotateLeft(root->right);
		rotateRight(root);
	}
}

EncodingNode* Huffman_AVL_Tree::findUnbalancedNode(EncodingNode*)
{
	return nullptr;
}

/* ENCODING NODE */

EncodingNode::EncodingNode(char character, int freq, int prior) : c(character), freq(freq), priority(prior)
{
	left = nullptr;
	right = nullptr;
	containChar = true;
}

EncodingNode::EncodingNode(char character, int freq, int prior, EncodingNode* l, EncodingNode* r, bool isContain) :
	c(character), freq(freq), priority(prior), left(l), right(r), containChar(isContain)
{
}

int EncodingNode::calculateBalanceFactor(EncodingNode* node)
{
	if (node == nullptr)
		return 0;
	return calculateBalanceFactor(node->left) - calculateBalanceFactor(node->right);
	// left high -> positive
	// right high -> negative
	// balanced -> 0
}

/* COMPARATOR */

bool Comparator::operator()(const std::pair<char, int> a, const std::pair<char, int> b)
{
	if (a.second < b.second)
		return true;
	else if (a.second == b.second)
	{
		if (('a' <= a.first && a.first <= 'z') && ('A' <= b.first && b.first <= 'Z'))
			return true;
		else if (('a' <= b.first && b.first <= 'z') && ('A' <= a.first && a.first <= 'Z'))
			return false;
		else
			return a.first < b.first;
	}
	return false;
}

bool Comparator::operator()(const EncodingNode* a, const EncodingNode* b)
{
	// logic for comparing two EncodingNode*
	if (a->freq > b->freq)
		return true;
	else if (a->freq == b->freq)
	{
		if (a->priority > b->priority)
			return true;
	}
	return false;
}
