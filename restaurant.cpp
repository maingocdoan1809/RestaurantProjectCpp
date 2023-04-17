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
		auto mapChar = getFrequency(message);
		auto queueChar = toList(mapChar);
		_root = buildTree(queueChar);
	}
	map<char, string> encode() {
		map<char, string> encoded;
		travelHelper(this->_root, "", encoded);
		return encoded;
	}
};



void simulate(string filename)
{
	return;
}