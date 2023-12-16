#include "main.h"

static int MAXSIZE = 0;

// Gojo Node store information of a table in Gojo Restaurant
class GojoNode
{
private:
	int customerID;
	int encodedName; // This is RESULT
	GojoNode* left;
	GojoNode* right;
	friend class GojoRestaurant;
public:
	GojoNode(int, int);
};

class GojoRestaurant
{
	class GojoTreeBST
	{
	private:
		int numOfCustomer; // This is NUM (number of customers in a table)
		GojoNode* root;
		queue<int> queueOfCustomer;
		vector<int> customerPostOrder;
		void insertRecursion(GojoNode*&, int, int);
		void removeRecursion(GojoNode*&, int);
		void storePostOrder(GojoNode*&);
		int calculatePermutation(vector<int>);
	public:
		GojoTreeBST();
		void insertOneCustomer(int, int);
		void removeNumOfCustomers(int);
		void printTree(const GojoNode*);
		GojoNode* getRoot();
		vector<int> getPostOrder();
	};
private:
	class GojoTreeBST;
	vector<GojoTreeBST> listOfTable;
public:
	GojoRestaurant();
	void insertCustomer(int, int);
	void printArea(int);
	vector<GojoTreeBST> getListOfTable();
};

// Sukuna Node store information of a table in Sukuna Restaurant
class SukunaNode
{
private:
	int IDArea;
	list<int> listOfCustomer; // first element is the last customer, last element is the first customer
	friend class SukunaRestaurant;
public:
	SukunaNode(int);
	int getSize();
	void addOneCustomer(int);
	void removeCustomer(int);
	void printCustomerLIFO(int);
};

class SukunaRestaurant
{
private:
	vector<SukunaNode> listOfTable;
	list<int> listUpdatedTable;
	void makeActive(int);
	bool comparePriorityReHeap(SukunaNode, SukunaNode);
	bool whichUpdatedFirst(SukunaNode, SukunaNode);
public:
	SukunaRestaurant();
	void reHeapDown(int);
	void reHeapUp(int);
	bool comparePrioritySorting(SukunaNode, SukunaNode);
	void deleteEmptyArea();
	void preOrderTraversalPrint(int, int);
	vector<SukunaNode> getListOfTable();
	void insertCustomer(int);
};

class Customer;
class Command
{
public:
	bool IS_VALID_CUSTOMER(const string&);
	Customer* LAPSE(string, int, GojoRestaurant&, SukunaRestaurant&);
	void KOKUSEN(GojoRestaurant&);
	void KEITEIKEN(int num, SukunaRestaurant&);
	void HAND(Customer*);
	void LIMITLESS(int num, GojoRestaurant&);
	void CLEAVE(int num, SukunaRestaurant&);
};

class IO
{
public:
	static void readInput(const string, string&, string&);
	static void writeOutput();
};

class EncodingNode
{
public:
	char c;
	int freq;
	int priority;
	EncodingNode* left;
	EncodingNode* right;
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
	static void printTree(EncodingNode*&);
};

class Customer
{
private:
	int ID;
	string originalName;
	string encodedNameBinToDec; // This is RESULT
	string encodedNameCaesar;
	vector<pair<char, int>> listOfChar;
	vector<pair<char, int>> generateOriginalName(string name);
	void encodingCaesar(vector<pair<char, int>>&);
	bool compareFreq(const std::pair<char, int> a, const std::pair<char, int> b);
	void encodingHuffmanAVL();
	void chooseRestaurant(GojoRestaurant&, SukunaRestaurant&);
	string generateCaesarName(string name, vector<pair<char, int>>&);
public:
	int getID();
	Customer(string, int, GojoRestaurant&, SukunaRestaurant&);
	string getEncodedNameBinToDec();
	void printHuffmanTree();
	~Customer();
};

struct Comparator
{
	bool operator()(const std::pair<char, int> a, const std::pair<char, int> b);
	bool operator()(const EncodingNode* a, const EncodingNode* b);
};

struct MathOperation
{
	 vector<vector<long long int>> storeArr;
	 const long long MAXSIZE = 1e9 + 7;
private:
	 int long long solve(vector<int>& postOrder) {
		if (postOrder.size() <= 1) return 1;
		vector<int> l, r;
		for (int i = 1; i < postOrder.size(); ++i) {
			if (postOrder[i] > postOrder[0]) r.push_back(postOrder[i]);
			else l.push_back(postOrder[i]);
		}
		int n = l.size(), m = r.size();
		return solve(l) * solve(r) % MAXSIZE * storeArr[n + m][n] % MAXSIZE;
	}

public:
	 int calculatePermutation(vector<int>& postOrder) {
		storeArr = vector<vector<long long>>(postOrder.size() + 1, vector<long long>(postOrder.size() + 1, 0));
		for (int i = 1; i < postOrder.size() + 1; ++i) {
			storeArr[i][0] = 1;
			storeArr[i][1] = i;
			storeArr[i][i - 1] = i;
			storeArr[i][i] = 1;
		}
		for (int i = 2; i < postOrder.size() + 1; ++i) {
			for (int j = 2; j < postOrder.size() + 1; ++j) {
				if (i >= j) storeArr[i][j] = (storeArr[i - 1][j - 1] % MAXSIZE + storeArr[i - 1][j] % MAXSIZE) % MAXSIZE;
				else break;
			}
		}
		return solve(postOrder);
	}
};

static int indexCustomer = 0;

// this function will process one command for each line of test file
void process(string command, string argument)
{
	Command* cmd = new Command();
	GojoRestaurant G;
	SukunaRestaurant S;
	Customer* customer = nullptr;

	if (command == "MAXSIZE")
	{
		MAXSIZE = stoi(argument);
	}
	if (command == "LAPSE")
	{
		if (customer != nullptr)
		{
			delete customer;
			customer = nullptr;
		}
		customer = cmd->LAPSE(argument, indexCustomer, G, S);
		indexCustomer++;
	}
	else if (command == "KOKUSEN")
	{
		cmd->KOKUSEN(G);
	}
	else if (command == "KEITEIKEN")
	{
		cmd->KEITEIKEN(stoi(argument), S);
	}
	else if (command == "HAND")
	{
		cmd->HAND(customer);
	}
	else if (command == "LIMITLESS")
	{
		cmd->LIMITLESS(stoi(argument), G);
	}
	else if (command == "CLEAVE")
	{
		cmd->CLEAVE(stoi(argument), S);
	}
	indexCustomer++;
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

/* COMMAND */

bool Command::IS_VALID_CUSTOMER(const string& name)
{
	int char_count[256] = { 0 };  // Initialize an array to count occurrences of each character
	for (char c : name) {
		char_count[c]++;
	}
	int distinct_chars = 0;
	for (int count : char_count) {
		if (count > 0) {
			distinct_chars++;
		}
	}
	return distinct_chars >= 3;
}

Customer* Command::LAPSE(string name, int ID, GojoRestaurant& G, SukunaRestaurant& S)
{
	// check if the name contains at least 3 distinct characters
	if (this->IS_VALID_CUSTOMER(name) == false)
	{
		return nullptr;
	}
	Customer* customer = new Customer(name, ID, G, S);
	return customer;
}

void Command::KOKUSEN(GojoRestaurant& G)
{
	int deleteNum = 0;
	if (G.getListOfTable().size() == 0 && G.getListOfTable().size() == 1)
	{
		return;
	}
	for (int i = 0; i < MAXSIZE; i++)
	{
		// calculate deleteNum here (will be implemented later)

		vector<int> postOrder = G.getListOfTable()[i].getPostOrder();
		MathOperation math;
		deleteNum = math.calculatePermutation(postOrder);
		if (deleteNum > MAXSIZE)
		{
			deleteNum = MAXSIZE;
		}
		G.getListOfTable()[i].removeNumOfCustomers(deleteNum);
	}
}

void Command::KEITEIKEN(int num, SukunaRestaurant& S)
{
	// print the area num
	vector<SukunaNode> sortedTable = S.getListOfTable();
	function <bool(SukunaNode, SukunaNode)> compare = [&](SukunaNode a, SukunaNode b) { return S.comparePrioritySorting(a, b); };
	sort(sortedTable.begin(), sortedTable.end(), compare);
	// num means the number of area to delete customers
	for (int i = 0; i < num; i++)
	{
		sortedTable[i].removeCustomer(num);
		if (sortedTable[i].getSize() == 0)
		{
			S.deleteEmptyArea();
		}
		else
		{
			S.reHeapDown(i);
		}
	}
}

void Command::HAND(Customer* customer)
{

}

void Command::LIMITLESS(int num, GojoRestaurant& G)
{
	// print the area num
	G.printArea(num);
}

void Command::CLEAVE(int num, SukunaRestaurant& S)
{
	S.preOrderTraversalPrint(0, num);
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
	// create a vector of EncodingNode* to storeArr the list of character using for initialize the priority queue
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

void Customer::chooseRestaurant(GojoRestaurant& G, SukunaRestaurant& S)
{
	// choose restaurant
	int num = stoi(encodedNameBinToDec);
	if (num % 2 == 0)
	{
		// Restaurant Gojo
		G.insertCustomer(ID, num);
	}
	else
	{
		// Restaurant Sukuna
		S.insertCustomer(num);
	}
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

Customer::Customer(string name, int ID, GojoRestaurant& G, SukunaRestaurant& S) : originalName(name), ID(ID)
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
	// Choose restaurant for customer
	chooseRestaurant(G, S);
}

string Customer::getEncodedNameBinToDec()
{
	return encodedNameBinToDec;
}

void Customer::printHuffmanTree()
{

}

Customer::~Customer()
{
	//delete this;
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

/* GOJO RESTAURANT - TREE BST*/

GojoRestaurant::GojoRestaurant() : listOfTable(MAXSIZE + 1)
{

}

GojoRestaurant::GojoTreeBST::GojoTreeBST() : root(nullptr), numOfCustomer(0)
{
}

void GojoRestaurant::GojoTreeBST::insertRecursion(GojoNode*& root, int ID, int encodedName)
{
	// the value to be compared is encodedName
	if (root == nullptr)
	{
		root = new GojoNode(ID, encodedName);
		this->queueOfCustomer.push(ID);
	}
	else if (encodedName < root->encodedName)
	{
		insertRecursion(root->left, ID, encodedName);
	}
	else if (encodedName >= root->encodedName)
	{
		insertRecursion(root->right, ID, encodedName);
	}
	else
	{
		return;
	}
}

void GojoRestaurant::GojoTreeBST::removeNumOfCustomers(int numOfCustomers)
{
	for (int i = 0; i < numOfCustomers && queueOfCustomer.empty() == false ; i++)
	{
		removeRecursion(root, queueOfCustomer.front());
		queueOfCustomer.pop();
	}
}

void GojoRestaurant::GojoTreeBST::printTree(const GojoNode*)
{
	// print in-order
	if (root == nullptr)
	{
		return;
	}
	else
	{
		printTree(root->left);
		cout << root->encodedName << ' ';
		printTree(root->right);
	}
	// Có thể thêm vào đây để debug
}

GojoNode* GojoRestaurant::GojoTreeBST::getRoot()
{
	return root;
}

vector<int> GojoRestaurant::GojoTreeBST::getPostOrder()
{
	// storeArr post-order traversal of tree in vector result
	customerPostOrder.clear();
	storePostOrder(root);
	return customerPostOrder;
}

void GojoRestaurant::GojoTreeBST::removeRecursion(GojoNode*&, int ID)
{
	if (root == nullptr)
	{
		return;
	}
	else if (ID < root->customerID)
	{
		removeRecursion(root->left, ID);
	}
	else if (ID > root->customerID)
	{
		removeRecursion(root->right, ID);
	}
	else
	{
		if (root->left == nullptr && root->right == nullptr)
		{
			delete root;
			root = nullptr;
		}
		else if (root->left == nullptr)
		{
			GojoNode* temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == nullptr)
		{
			GojoNode* temp = root;
			root = root->left;
			delete temp;
		}
		else
		{
			GojoNode* temp = root->right;
			// find the smallest node in the right subtree
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}
			root->customerID = temp->customerID;
			root->encodedName = temp->encodedName;
			removeRecursion(root->right, temp->customerID);
		}
	}
}

void GojoRestaurant::GojoTreeBST::storePostOrder(GojoNode*& root)
{
	// storeArr post-order traversal of tree in vector result
	if (root == nullptr)
	{
		return;
	}
	else
	{
		storePostOrder(root->left);
		storePostOrder(root->right);
		customerPostOrder.push_back(root->encodedName);
	}
}

int GojoRestaurant::GojoTreeBST::calculatePermutation(vector<int> postOrder)
{
	return 0;
}

void GojoRestaurant::GojoTreeBST::insertOneCustomer(int ID, int encodedName)
{
	insertRecursion(root, ID, encodedName);
}

/* GOJO RESTAURANT - GENERAL */

void GojoRestaurant::insertCustomer(int customerID, int encodedName)
{
	// num is the encodedNameBinToDec from Customer converted to int
	//int num = stoi(encodedName);
	int ID = encodedName % MAXSIZE + 1;
	listOfTable[ID].insertOneCustomer(customerID, encodedName);
}

void GojoRestaurant::printArea(int area)
{
	if (this->getListOfTable().size() == 0)
	{
		return;
	}
	GojoNode* root = this->listOfTable[area].getRoot();
	this->listOfTable[area].printTree(root);
}

vector<GojoRestaurant::GojoTreeBST> GojoRestaurant::getListOfTable()
{
	return this->listOfTable;
}

/* GOJO NODE */

GojoNode::GojoNode(int ID, int encodedName) : customerID(ID), encodedName(encodedName)
{
	left = nullptr;
	right = nullptr;
}

/* SUKUNA RESTAURANT - GENERAL */

void SukunaRestaurant::reHeapDown(int tablePosition)
{
	// re-heap down
	int leftChildPosition = 2 * tablePosition + 1;
	int rightChildPosition = 2 * tablePosition + 2;
	int minChildPosition = tablePosition;
	if (leftChildPosition < listOfTable.size() && comparePriorityReHeap(listOfTable[leftChildPosition], listOfTable[minChildPosition]))
	{
		minChildPosition = leftChildPosition;
	}
	if (rightChildPosition < listOfTable.size() && comparePriorityReHeap(listOfTable[rightChildPosition], listOfTable[minChildPosition]))
	{
		minChildPosition = rightChildPosition;
	}
	if (minChildPosition != tablePosition)
	{
		swap(listOfTable[tablePosition], listOfTable[minChildPosition]);
		reHeapDown(minChildPosition);
	}
}

void SukunaRestaurant::reHeapUp(int tablePosition)
{
	// re-heap up
	int parentPosition = (tablePosition - 1) / 2;
	while (parentPosition >= 0 && comparePriorityReHeap(listOfTable[tablePosition], listOfTable[parentPosition]))
	{
		swap(listOfTable[tablePosition], listOfTable[parentPosition]);
		tablePosition = parentPosition;
		parentPosition = (tablePosition - 1) / 2;
	}
}

void SukunaRestaurant::makeActive(int ID)
{
	list<int>::iterator it = find(listUpdatedTable.begin(), listUpdatedTable.end(), ID);
	if (it != listUpdatedTable.end())
	{
		listUpdatedTable.erase(it);
		listUpdatedTable.push_front(ID);
	}
}

// true means a has higher priority than b
// false means b has higher priority than a
bool SukunaRestaurant::comparePriorityReHeap(SukunaNode a, SukunaNode b)
{
	if (a.getSize() < b.getSize())
		return true;
	else if (a.getSize() == b.getSize())
	{
		if (whichUpdatedFirst(a, b))
			return true;
	}
	return false;
}

bool SukunaRestaurant::comparePrioritySorting(SukunaNode a, SukunaNode b)
{
	if (a.getSize() < b.getSize())
		return true;
	else if (a.getSize() == b.getSize())
	{
		if (!whichUpdatedFirst(a, b))
			return true; // this means a is updated later than b
	}
	return false;
}

void SukunaRestaurant::deleteEmptyArea()
{
	// delete in listUpdatedTable
	auto it = find(listUpdatedTable.begin(), listUpdatedTable.end(), 0);
	if (it != listUpdatedTable.end())
	{
		listUpdatedTable.erase(it);
	}
	// delete in listOfTable
	for (int i = 0; i < listOfTable.size(); i++)
	{
		if (listOfTable[i].getSize() == 0)
		{
			swap(listOfTable[i], listOfTable[listOfTable.size() - 1]);
			listOfTable.pop_back();
			reHeapDown(i);
			break;
		}
	}
}

void SukunaRestaurant::preOrderTraversalPrint(int position, int numOfCustomer)
{
	if (position >= listOfTable.size())
	{
		return;
	}
	listOfTable[position].printCustomerLIFO(numOfCustomer);
	preOrderTraversalPrint(position * 2 + 1, numOfCustomer);
	preOrderTraversalPrint(position * 2 + 2, numOfCustomer);
}

bool SukunaRestaurant::whichUpdatedFirst(SukunaNode a, SukunaNode b)
{
	 //true means a is updated first
	 //false means b is updated first
	for (auto it = listUpdatedTable.begin(); it != listUpdatedTable.end(); it++)
	{
		if (*it == a.IDArea)
		{
			return true;
		}
		else if (*it == b.IDArea)
		{
			return false;
		}
	}
}

SukunaRestaurant::SukunaRestaurant()
{

}

vector<SukunaNode> SukunaRestaurant::getListOfTable()
{
	return this->listOfTable;
}

void SukunaRestaurant::insertCustomer(int encodedName)
{
	int ID = encodedName % MAXSIZE + 1;
	int tablePosition = 0;
	bool found = false;
	for (int i = 0; i < listOfTable.size(); i++)
	{
		if (listOfTable[i].IDArea == ID)
		{
			found = true;
			tablePosition = i;
			break;
		}
	}
	if (found == true)
	{
		// The above condition is true if the ID is not in the list of table
		listOfTable.push_back(SukunaNode(ID));
		makeActive(ID);
		tablePosition = listOfTable.size() - 1;
		listOfTable[tablePosition].addOneCustomer(encodedName);
		reHeapUp(tablePosition);
	}
	else
	{
		// The above condition is true if the ID is in the list of table
		listOfTable[tablePosition].addOneCustomer(encodedName);
		makeActive(ID);
		reHeapDown(tablePosition);
	}
}

/* SUKUNA NODE */

SukunaNode::SukunaNode(int ID) : IDArea(ID)
{
}

int SukunaNode::getSize()
{
	return listOfCustomer.size();
}

void SukunaNode::addOneCustomer(int encodedName)
{
	listOfCustomer.push_front(encodedName);
}

void SukunaNode::removeCustomer(int deleteNum)
{
	if (deleteNum > listOfCustomer.size())
	{
		deleteNum = listOfCustomer.size();
	}
	for (int i = 0; i < deleteNum; i++)
	{
		cout << listOfCustomer.back() << '-' << IDArea << '\n';
		listOfCustomer.pop_back();
	}
}

void SukunaNode::printCustomerLIFO(int numOfCustomers)
{
	list<int>::iterator it = listOfCustomer.begin();
	while (it != listOfCustomer.end() && numOfCustomers > 0)
	{
		cout << this->IDArea << '-' << *it << '\n';
		it++;
		numOfCustomers--;
	}
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

void Huffman_AVL_Tree::printTree(EncodingNode*& root)
{
	// print in-order
	if (root == nullptr)
	{
		return;
	}
	else
	{
		printTree(root->left);
		if (root->c == '0')
		{
			cout << root->freq << ' ' << '\n';
		}
		else
		{
			cout << root->c << ' ' << '\n';
		}
		printTree(root->right);
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
}

EncodingNode::EncodingNode(char character, int freq, int prior, EncodingNode* l, EncodingNode* r, bool isContain) :
	c(character), freq(freq), priority(prior), left(l), right(r)
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

/* IO */

void IO::readInput(const string inputStr, string& command, string& argument)
{
	stringstream ss(inputStr);
	ss >> command >> argument;
	cout << command << ' ' << argument << endl;
}

void IO::writeOutput()
{
}

