#include "main.h"

class Command
{
public:
	void LAPSE(string name, int);
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
	int indexCustomer = 0;
	if (command == "MAXSIZE")
	{

	}
	if (command == "LAPSE")
	{
		cmd->LAPSE(argument, indexCustomer);
		indexCustomer++;
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
	int calculateHeight(EncodingNode*);
	friend class Huffman_AVL_Tree;
};

class Huffman_AVL_Tree
{
private:
	vector<string> mapChar;
	static void rotateLeft(EncodingNode*&);
	static void rotateRight(EncodingNode*&);
	static void leftBalance(EncodingNode*&, int&);
	static void rightBalance(EncodingNode*&, int&);
	static string binToDec(string);
	static vector<string> createMapChar(EncodingNode*&);
	static void encodeAllChar(EncodingNode*&, vector<char>&, vector<string>&);
public:
	static void balanceTree(EncodingNode*&, int&);
	static string encode(EncodingNode*&, string);
};

class Customer
{
private:
	int ID;
	string originalName;
	string encodedNameBinToDec;
	string encodedNameCaesar;
	vector<pair<char, int>> listOfChar;
	vector<pair<char, int>> generateOriginalName(string name);
	void encodingCaesar(vector<pair<char, int>>&);
	bool compareFreq(const std::pair<char, int> a, const std::pair<char, int> b);
	void encodingHuffmanAVL();
	string generateCaesarName(string name, vector<pair<char, int>>&);
public:
	int getID();
	Customer(string, int);
	string getEncodedBinaryName();
	
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

void Command::LAPSE(string name, int ID)
{
	if (name.size() >= 3)
	{
		Customer* customer = new Customer(name, ID);
	}
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
	int countRotation;

	while (pq.size() > 1)
	{
		countRotation = 0;
		EncodingNode* node1 = pq.top();
		pq.pop();
		EncodingNode* node2 = pq.top();
		pq.pop();
		EncodingNode* newNode = new EncodingNode('0', node1->freq + node2->freq, listOfChar.size() + countNewNode++, node1, node2, false);
		Huffman_AVL_Tree::balanceTree(newNode, countRotation);
		pq.push(newNode);
	}
	EncodingNode* rootHuffmanAVL = pq.top(); // this is a tree
	encodedNameBinToDec = Huffman_AVL_Tree::encode(rootHuffmanAVL, this->encodedNameCaesar);
}
string Customer::generateCaesarName(string name, vector<pair<char, int>>&)
{
	string caesarName = "";
	int shift = 0;
	for (int i = 0; i < name.length(); i++)
	{
		for (pair<char, int> p : listOfChar)
		{
			if (p.first == name[i])
			{
				shift = p.second % 26;
				break;
			}
		}
		if (('a' <= name[i] && name[i] <= 'z') && (name[i] + shift > 'z'))
		{
			caesarName += 'a' + (name[i] + shift - 'z' - 1);
		}
		else if (('A' <= name[i] && name[i] <= 'Z') && (name[i] + shift > 'Z'))
		{
			caesarName += 'a' + (name[i] + shift - 'Z' - 1);
		}
		else
		{
			caesarName += name[i] + shift;
		}
	}
	return caesarName;
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

int Customer::getID()
{
	return ID;
}

Customer::Customer(string name, int ID) : originalName(name), ID(ID)
{
	// Create a vector listchar contains frequency of each character in originalName
	listOfChar = generateOriginalName(originalName);
	// Encoding the name using Caesar Cipher
	encodedNameCaesar = generateCaesarName(originalName, listOfChar);
	// Create a vector listchar contains frequency of each character in encodedName
	encodingCaesar(listOfChar);
	// Sort the list of character by frequency
	function <bool(pair<char, int>, pair<char, int>)> compare = [&](pair<char, int> a, pair<char, int> b) { return compareFreq(a, b); };
	sort(listOfChar.begin(), listOfChar.end(), compare);
	// Encoding the name using Huffman AVL Tree
	encodingHuffmanAVL();
}

string Customer::getEncodedBinaryName()
{
	return encodedNameBinToDec;
}

void Customer::encodingCaesar(vector<pair<char, int>>& listchar)
{
	// encoding
	vector<pair<char,int>> newCustomerName;
	char newChar;
	int shift = 0;
	bool isContain = false;
	for (int i = 0; i < listchar.size(); i++)
	{
		shift = listchar[i].second % 26;
		if (('a' <= listchar[i].first && listchar[i].first <= 'z') && (listchar[i].first + listchar[i].second > 'z'))
		{
			newChar = 'a' + (listchar[i].first + shift - 'z' - 1);
		}
		else if (('A' <= listchar[i].first && listchar[i].first <= 'Z') && (listchar[i].first + listchar[i].second > 'Z'))
		{
			newChar = 'a' + (listchar[i].first + shift - 'Z' - 1);
		}
		else
		{
			newChar = listchar[i].first + shift;
		}
		// check if newChar is already in newCustomerName and add the frequency
		for (pair<char, int> p : newCustomerName)
		{
			if (p.first == newChar)
			{
				p.second += listchar[i].second;
				isContain = true;
				break;
			}
		}
		if (!isContain)
		{
			newCustomerName.push_back(make_pair(newChar, listchar[i].second));
		}
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

void Huffman_AVL_Tree::balanceTree(EncodingNode*& root, int& countRotation)
{
	// check if the tree is balanced
	if (countRotation > 3)
	{
		return;
	}
	int leftHeight = root->calculateHeight(root->left);
	int rightHeight = root->calculateHeight(root->right);
	int balanceFactor = leftHeight - rightHeight;
	if (leftHeight == 0 && rightHeight == 0) // if the node is leaf
	{
		return;
	}
	if (balanceFactor >= -1 && balanceFactor <= 1)
	{
		if (leftHeight > 0)
			balanceTree(root->left, countRotation);
		if (rightHeight > 0)
			balanceTree(root->right, countRotation);
	}
	else if (balanceFactor > 1)
	{
		rightBalance(root, countRotation);
	}
	else if (balanceFactor < -1)
	{
		leftBalance(root, countRotation);
	}
}

string Huffman_AVL_Tree::encode(EncodingNode*& root, string encodeName)
{
	string result = "";
	vector<string> mapChar(52, "");
	mapChar = createMapChar(root);
	for (char c : encodeName)
	{
		if (c >= 'a' && c <= 'z')
		{
			result += mapChar[c - 'a'];
		}
		else if (c >= 'A' && c <= 'Z')
		{
			result += mapChar[c - 'A' + 26];
		}
	}
	result = result.substr(0, 9);
	result = binToDec(result);
	return result;
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

void Huffman_AVL_Tree::leftBalance(EncodingNode*& root, int& countRotation)
{
	int balanceFactor = root->calculateBalanceFactor(root->right);
	if (balanceFactor <= 0)
	{
		rotateLeft(root);
	}	
	else
	{
		rotateRight(root->right);
		rotateLeft(root);
	}
	countRotation++;
}

void Huffman_AVL_Tree::rightBalance(EncodingNode*& root, int& countRotation)
{
	int balanceFactor = root->calculateBalanceFactor(root->left);
	if (balanceFactor >= 0)
	{
		rotateRight(root);
	}
	else
	{
		rotateLeft(root->left);
		rotateRight(root);
	}
	countRotation++;
}

/* ENCODING NODE */

string Huffman_AVL_Tree::binToDec(string input)
{
	string output = "";
	int dec = 0;
	for (int i = 0; i < input.length(); i++)
	{
		dec += (input[i] - '0') * pow(2, input.length() - i - 1);
	}
	output = to_string(dec);
	return output;
}

vector<string> Huffman_AVL_Tree::createMapChar(EncodingNode*& root)
{
	vector<string> myMap(52, "");
	vector<char> path;
	encodeAllChar(root, path, myMap);
	return myMap;
}

void Huffman_AVL_Tree::encodeAllChar(EncodingNode*& root, vector<char>&path, vector<string> &map)
{
	if (root->left == nullptr && root->right == nullptr)
	{
		string decodePath(path.begin(), path.end());
		if (root->c >= 'a' && root->c <= 'z')
		{
			map[root->c - 'a'] = decodePath;
		}
		else if (root->c >= 'A' && root->c <= 'Z')
		{
			map[root->c - 'A' + 26] = decodePath;
		}
	}
	if (root->left != nullptr)
	{
		path.push_back('0');
		encodeAllChar(root->left, path, map);
		path.pop_back();
	}
	if (root->right != nullptr)
	{
		path.push_back('1');
		encodeAllChar(root->right, path, map);
		path.pop_back();
	}
}

int EncodingNode::calculateBalanceFactor(EncodingNode* node)
{
	int leftHeight = calculateHeight(node->left);
	int rightHeight = calculateHeight(node->right);
	return leftHeight - rightHeight;
	// < 0 -> right heavy
	// > 0 -> left heavy
}

int EncodingNode::calculateHeight(EncodingNode* node)
{
	if (node == nullptr)
		return 0;
	else
		return max(calculateHeight(node->left), calculateHeight(node->right)) + 1;
}

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
