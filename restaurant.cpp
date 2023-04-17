#include "main.h"


struct Node {
	char _char;
	int _count;
	Node* _left;
	Node* _right;
	Node(char c, int cnt, Node* l, Node* r) {
		this->_char = c;
		this->_count = cnt;
		this->_left = l;
		this->_right = r;
	}
};
class HuffmanEncoding {
private:

	Node* _root;
	string _message;
	map<char, int> getFrequency(string message) {
		map<char, int> data;
		for (char c : message) {
			data[c]++;
		}
		return data;
	}
	class Comparer {
	public:
		bool operator()(Node* below, Node* above)
		{
			if (below->_count > above->_count) {
				return true;
			}
			return false;
		}
	};
	using myqueue = priority_queue<Node*, vector<Node*>, HuffmanEncoding::Comparer >;

	myqueue toList(map<char, int> data) {
		myqueue myqueue;
		for (auto pair : data) {
			myqueue.push(new Node(pair.first, pair.second, nullptr, nullptr));
		}

		return myqueue;

	}
	Node* buildTree(myqueue myqueue) {
		Node* root;
		while (myqueue.size() >= 1) {
			Node* leastNode = myqueue.top();
			myqueue.pop();
			Node* secondleastNode = myqueue.top();
			cout << "Sum: " << leastNode->_char << " and " << secondleastNode->_char << endl;
			myqueue.pop();
			int sum = leastNode->_count + secondleastNode->_count;
			Node* sumNode = new Node('#', sum, leastNode, secondleastNode);
			myqueue.push(sumNode);
		}
		root = myqueue.top();
		return root;
	}

	void travelHelper(Node* node, string code, map<char, string>& codes) {
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
		queue<Node*> nodes;
		nodes.push(this->_root);
		do {
			Node* topNode = nodes.front();
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

string encodeCustomerName(string name) {
	HuffmanEncoding encoder { name };
	string encodedString = encoder.encodeToString();
	size_t length = encodedString.length();
	if (length > 15) {
		encodedString = encodedString.substr(length - 16, length);
	}
	return encodedString;
}

size_t convertToDecimal(string binaryStr) {
	size_t decimalResult = 0;
	size_t length = binaryStr.length();
	for (int i = length - 1; i >= 0; i--) {
		decimalResult += ( binaryStr[i] - 48 ) * pow(2, length - 1 - i);
	}
	return decimalResult;
}
bool isEven(size_t number) {
	return number % 2 == 0;
}
short decideArea(size_t resultNumber) {
	return isEven(resultNumber) ? 2 : 1;
}
struct Table {
	string customerName;
	int serveCount;
	Table(string customerName, int serveCount) {
		this->customerName = customerName;
		this->serveCount = serveCount;
	}
	Table() {
		Table("", 0);
	}
	void resetTable() {
		this->customerName = "";
		this->serveCount = 0;
	}
};
// now implement a area:
class Area {

public:
	static map<string, Table*> currentTables;

	virtual void addCustomer(string customerName) = 0;
	virtual void getCustomer(string customerName) = 0;
	virtual void removeCustomer(string customerName) = 0;
};
map<string, Table*> Area::currentTables{};

class EvenArea : public Area {
private:
	vector<Table*> tables;
public:
	EvenArea() {
		fill(tables.begin(), tables.end(), new Table());
	}
	void addCustomer(string customerName) override {

	}
	void getCustomer(string customerName) override {

	}
	void removeCustomer(string customerName) override {

	}
};
class OddArea : public Area {
	void addCustomer(string customerName) override {

	}
	void getCustomer(string customerName) override {

	}
	void removeCustomer(string customerName) override {

	}
};

void simulate(string filename)
{
	return;
}
int main() {
	cout << convertToDecimal("1010");
	return 0;
}