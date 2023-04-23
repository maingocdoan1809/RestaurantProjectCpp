#include "main.h"

template<typename T>
struct Node {
	T _char;
	int _count;
	int _id;
	int _result;
	Node<T>* _left = nullptr;
	Node<T>* _right = nullptr;

	Node(T c, int cnt = 0, Node<T>* l = nullptr, Node<T>* r = nullptr) {
		this->_char = c; // name
		this->_count = cnt; // frequency or number of orders
		this->_left = l;
		this->_right = r;
	}
	Node(T c, int result, int tableId) {
		this->_char = c;
		this->_result = result;
		this->_left = nullptr;
		this->_right = nullptr;
		this->_id = tableId;
		this->_count = 0;
	}
	Node() {
		_count = 0;
		_left = nullptr;
		_right = nullptr;
	}
	Node(int id) {
		this->_id = id;
	}
	void increaseCount() {
		this->_count++;
	}
};
class HuffmanEncoding {
private:

	Node<char>* _root = nullptr;
	string _message;
	map<char, int> getFrequency(string message) {
		map<char, int> data;
		for (char c : message) {
			data[c]++;
		}
		return data;
	}

	template<typename T>
	class Comparer {
	public:
		bool operator()(Node<T>* below, Node<T>* above)
		{
			if (below->_count > above->_count) {
				return true;
			}
			return false;
		}
	};
	using myqueue = priority_queue<Node<char>*, vector<Node<char>*>, HuffmanEncoding::Comparer<char> >;

	myqueue toList(map<char, int> data) {
		myqueue myqueue;
		for (auto pair : data) {
			myqueue.push(new Node<char>(pair.first, pair.second));
		}

		return myqueue;

	}
	Node<char>* buildTree(myqueue myqueue) {
		Node<char>* root = nullptr;
		while (myqueue.size() >= 2) {
			Node<char>* leastNode = myqueue.top();
			myqueue.pop();
			Node<char>* secondleastNode = myqueue.top();
			myqueue.pop();
			int sum = leastNode->_count + secondleastNode->_count;
			Node<char>* sumNode = new Node<char>('#', sum, leastNode, secondleastNode);
			myqueue.push(sumNode);
		}
		root = myqueue.top();
		return root;
	}

	void travelHelper(Node<char>* node, string code, map<char, string>& codes) {
		if (node->_left == nullptr && node->_right == nullptr) {
			codes[node->_char] = code;
			return;
		}
		// if node is not a left, then it always has left and right node.
		travelHelper(node->_left, code + "0", codes);
		travelHelper(node->_right, code + "1", codes);
	}
public:
	HuffmanEncoding(string message) {
		this->_message = message;
		auto mapChar = getFrequency(message);
		auto queueChar = toList(mapChar);
		_root = buildTree(queueChar);
	}
	~HuffmanEncoding() {
		queue<Node<char>*> nodes;
		nodes.push(this->_root);
		do {
			Node<char>* topNode = nodes.front();
			nodes.pop();
			if (topNode->_left != nullptr) {
				nodes.push(topNode->_left);
			}
			if (topNode->_right != nullptr) {
				nodes.push(topNode->_right);
			}
			delete topNode;
			topNode = nullptr;
		} while (nodes.size());
	}
	map<char, string> encode() {
		map<char, string> encoded;
		travelHelper(this->_root, "", encoded);
		return encoded;
	}
	string encodeToString() {
		auto encodeMap = encode();
		if (encodeMap.size() <= 1) {
			return "0";
		}
		string binaryStr = "";
		for (char c : this->_message) {

			binaryStr += encodeMap[c];
		}
		return binaryStr;
	}
};



// newestNode:
Node<string>* latestNode = nullptr;
// implement AVL:
class AVL {
private:
	Node<string>* _root = nullptr;
	Node<string>* _insertHelper(Node<string>* root, int key, string customername, int idTable);
	int height(Node<string>* t) {
		int h = 0;
		if (t != NULL) {
			int l_height = height(t->_left);
			int r_height = height(t->_right);
			int max_height = max(l_height, r_height);
			h = max_height + 1;
		}
		return h;
	}
	int difference(Node<string>* t) {
		int l_height = height(t->_left);
		int r_height = height(t->_right);
		int b_factor = l_height - r_height;
		return b_factor;
	}
	Node<string>* rightRotate(Node<string>* parent) {
		Node<string>* temp = nullptr;
		temp = parent->_right;
		parent->_right = temp->_left;
		temp->_left = parent;
		return temp;
	}
	Node<string>* leftRotate(Node<string>* parent) {
		Node<string>* temp = nullptr;
		temp = parent->_left;
		parent->_left = temp->_right;
		temp->_right = parent;
		return temp;
	}
	Node<string>* lRight_rotate(Node<string>* parent) {
		Node<string>* t;
		t = parent->_left;
		parent->_left = rightRotate(t);
		return leftRotate(parent);
	}
	Node<string>* rLeft_rotate(Node<string>* parent) {
		Node<string>* t;
		t = parent->_right;
		parent->_right = leftRotate(t);
		return rightRotate(parent);
	}

	Node<string>* balance(Node<string>* t) {
		int bal_factor = difference(t);
		if (bal_factor > 1) {
			if (difference(t->_left) > 0)
				t = leftRotate(t);
			else
				t = lRight_rotate(t);
		}
		else if (bal_factor < -1) {
			if (difference(t->_right) > 0)
				t = rLeft_rotate(t);
			else
				t = rightRotate(t);
		}
		return t;
	}
public:
	~AVL() {
		queue<Node<string>*> arr;
		arr.push(_root);
		do {
			Node<string>* top = arr.front();
			arr.pop();
			if (top->_left != nullptr) {
				arr.push(top->_left);
			}
			if (top->_right != nullptr) {
				arr.push(top->_right);
			}
			delete top;
			top = nullptr;
		} while (arr.size());
	}
	void insert(string customerName, int idTable);
	void print();
};

// our restaurant



// now implement a area:
class Area {
public:
	virtual bool addCustomer(string customerName, int id) = 0;
	virtual bool removeCustomer(string customerName) = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};

class EvenArea : public Area {
private:
	map<int, Node<string>*> tables;
	int _size = 0;
public:
	bool addCustomer(string customerName, int id) override;
	int getSize() override;
	bool removeCustomer(string customerName) override;
	static int hashResult(size_t result);
	void print() override;

};
class OddArea : public Area {
private:
	AVL _avl;
	int _size = 0;
public:
	bool addCustomer(string customerName, int id) override;
	bool removeCustomer(string customerName) override;
	int getSize() override;
	void print() override;
};
class Restaurant {
private:
	Area* evenArea;
	Area* oddArea;
	queue<Node<string>*> fifo;

	// id <=> table
	map<int, Node<string>*> tables;
public:
	Restaurant();
	int decideID(int id);
	void addCustomer(string customername);
	void CLE(int num);
	void PrintHT();
	void printAVL();
	void printMH();

	static int getResult(string customerName);
	static bool isEven(size_t number);
	static short decideArea(size_t resultNumber);
	static string encodeCustomerName(string name);
	static size_t convertToDecimal(string binaryStr);
	static int getIDTable(size_t result);
};


class Heap {
private:
	vector<Node<string>*> _heap;
public:
	void add(Node<string>* newNode) {
		_heap.push_back(newNode);
	}
	void heapify(int parentIndex) {
		int l = 2 * parentIndex + 1;
		int r = 2 * parentIndex + 2;
		int smallest = parentIndex;
		if (l < _heap.size() && _heap[l]->_count < _heap[parentIndex]->_count)
			smallest = l;
		if (r < _heap.size() && _heap[r]->_count < _heap[smallest]->_count)
			smallest = r;
		if (smallest != parentIndex) {
			swap(_heap[parentIndex], _heap[smallest]);
			heapify(smallest);
		}
	}
};
//#######pragma endregion

void AVL::print() {
	queue<Node<string>*> arr;
	arr.push(_root);
	do {
		Node<string>* top = arr.front();
		arr.pop();
		if (top->_left != nullptr) {
			arr.push(top->_left);
		}
		if (top->_right != nullptr) {
			arr.push(top->_right);
		}
		cout << top->_id << "-" << top->_result << endl;
		top = nullptr;
	} while (arr.size());
}
Node<string>* AVL::_insertHelper(Node<string>* r, int key, string name, int idtable) {

	if (r == nullptr) {
		r = new Node<string>(name, key, idtable);
		latestNode = r;
		return r;
	}
	if (key < r->_result) {
		r->_left = _insertHelper(r->_left, key, name, idtable);
		r = balance(r);
	}
	else if (key >= r->_result) {
		r->_right = _insertHelper(r->_right, key, name, idtable);
		r = balance(r);
	} return r;
}

void AVL::insert(string customerName, int idTable) {
	int result = Restaurant::getResult(customerName);
	this->_root = _insertHelper(this->_root, result, customerName, idTable);
}

//#################pragma endregion

bool OddArea::addCustomer(string customerName, int id) {
	if (this->_size >= MAXSIZE / 2) {
		return false;
	}
	this->_avl.insert(customerName, id);
	return true;
}
bool OddArea::removeCustomer(string customerName) {

	return false;
}
int OddArea::getSize() {
	return this->_size;
}
void OddArea::print() {
	this->_avl.print();
}

//#######pragma endregion
int EvenArea::hashResult(size_t result) {
	return result % ( MAXSIZE / 2 );
}
bool EvenArea::addCustomer(string customerName, int id) {
	if (_size == MAXSIZE / 2) {
		return false;
	}
	int result = Restaurant::getResult(customerName);
	int hashValue = EvenArea::hashResult(result);
	Node<string>* newNode = nullptr;
	while (true) {
		try {
			tables.at(hashValue);
			newNode = new Node<string>();
			tables[hashValue] = newNode;
			newNode->_char = customerName;
			newNode->_result = result;
			// determine its id:
			newNode->_id = id;
			break;
		}
		catch (exception e) {
			hashValue++;
		}
	}

	_size++;
	return true;
}

int EvenArea::getSize() {
	return this->_size;
}
bool EvenArea::removeCustomer(string customerName) {

}
void EvenArea::print() {
	for (auto& table : this->tables) {
		cout << table.second->_id << "-" << table.second->_result << endl;
	}
}
Restaurant::Restaurant() {
	this->evenArea = new EvenArea();
	this->oddArea = new OddArea();
}

int Restaurant::getResult(string customerName) {
	string encodedStr = encodeCustomerName(customerName);

	return convertToDecimal(encodedStr);
}
bool Restaurant::isEven(size_t number) {
	return number % 2 == 0;
}
short Restaurant::decideArea(size_t resultNumber) {
	return isEven(resultNumber) ? 2 : 1;
}
string Restaurant::encodeCustomerName(string name) {

	HuffmanEncoding encoder(name);

	string encodedString = encoder.encodeToString();
	size_t length = encodedString.length();
	if (length > 15) {
		encodedString = encodedString.substr(length - 16, length);
	}
	return encodedString;
}
size_t Restaurant::convertToDecimal(string binaryStr) {
	size_t decimalResult = 0;
	size_t length = binaryStr.length();
	for (int i = length - 1; i >= 0; i--) {
		decimalResult += ( binaryStr[i] - 48 ) * pow(2, length - 1 - i);
	}
	return decimalResult;
}
int Restaurant::getIDTable(size_t result) {
	return result % MAXSIZE + 1;
}
int Restaurant::decideID(int id) {
	if (id > MAXSIZE) {
		id = 1;
	}
	try {
		this->tables.at(id);
		return id;
	}
	catch (exception e) {
		return decideID(id + 1);
	}
	return id;
}

void Restaurant::CLE(int num) {

}
void Restaurant::PrintHT() {
	this->evenArea->print();
}
void Restaurant::printAVL() {
	this->oddArea->print();
}
void Restaurant::printMH() {

}


void Restaurant::addCustomer(string customername) {
	if (this->tables.size() == MAXSIZE) {
		return;
	}
	int result = getResult(customername);
	int id = decideID(getIDTable(result));
	int area = decideArea(result);

	if (area == 1) {
		if (!this->oddArea->addCustomer(customername, id)) {
			this->evenArea->addCustomer(customername, id);
		}
	}
	else {
		if (!this->evenArea->addCustomer(customername, id)) {
			this->oddArea->addCustomer(customername, id);
		}
	}
	tables[id] = latestNode;
	this->fifo.push(latestNode);

}



void simulate(string filename)
{
	return;
}
int main() {

	return 0;
}