#include "main.h"

template<typename T>
struct Node {
	T _char;
	int _count;
	int _id;
	int _result;
	Node* _left;
	Node* _right;
	Node(T c, int cnt = 0, Node* l = nullptr, Node* r = nullptr) {
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

	Node<char>* _root;
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
		Node<char>* root;
		while (myqueue.size() >= 1) {
			Node<char>* leastNode = myqueue.top();
			myqueue.pop();
			Node<char>* secondleastNode = myqueue.top();
			cout << "Sum: " << leastNode->_char << " and " << secondleastNode->_char << endl;
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
		string binaryStr = "";
		for (char c : this->_message) {
			binaryStr += encodeMap[c];
		}
		return binaryStr;
	}
};




// implement AVL:
class AVL {
private:
	Node<string>* _root;
	void _balance();
	void _insertHelper(Node<string>* root, int key, string customername);
public:
	void insert(string customerName);
	void print() {
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
		} while (arr.size());
	}
};

// our restaurant

class Restaurant {
private:
public:
	static int getResult(string customerName);
	static bool isEven(size_t number);
	static short decideArea(size_t resultNumber);
	static string encodeCustomerName(string name);
	static size_t convertToDecimal(string binaryStr);
};

// now implement a area:
class Area {
public:
	virtual bool addCustomer(string customerName) = 0;
	virtual bool removeCustomer(string customerName) = 0;
	virtual int getSize() = 0;
};

class EvenArea : public Area {
private:
	map<int, Node<string>*> tables;
	int _size = 0;
public:
	bool addCustomer(string customerName) override;
	int getSize() override;
	bool removeCustomer(string customerName) override;
};
class OddArea : public Area {
private:

public:
	bool addCustomer(string customerName) override;
	bool removeCustomer(string customerName) override;
};

//#######pragma endregion

void AVL::_insertHelper(Node<string>* root, int key, string customerName) {
	if (this->_root == nullptr) {
		this->_root = new Node<string>(customerName, key, key % MAXSIZE);
	}
	else {
		if (root->_id > key) {
			_insertHelper(root->_left, key, customerName);
		}
		else {
			_insertHelper(root->_right, key, customerName);
		}
	}
}

void AVL::insert(string customerName) {
	int result = Restaurant::getResult(customerName);
	_insertHelper(this->_root, result, customerName);
}

void AVL::_balance() {

}
//#################pragma endregion

bool OddArea::addCustomer(string customerName) {

}
bool OddArea::removeCustomer(string customerName) {

}

//#######pragma endregion
bool EvenArea::addCustomer(string customerName) {
	if (_size == MAXSIZE / 2) {
		return false;
	}
	int result = Restaurant::getResult(customerName);
	int hashValue = result % 3;
	Node<string>* newNode = nullptr;
	while (true) {
		try {
			tables.at(hashValue);

			newNode = new Node<string>();
			tables[hashValue] = newNode;
			newNode->_char = customerName;
			newNode->_result = result;
			// determine its id:
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
	HuffmanEncoding encoder { name };
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

void simulate(string filename)
{
	return;
}
int main() {
	return 0;
}