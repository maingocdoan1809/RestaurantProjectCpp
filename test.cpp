#include <iostream>
#include <queue>
#include <map>
using namespace std;

struct Node {
  char _char;
  int _count;
  Node* _next;
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
      if (below->_count < above->_count) {
        return true;
      }
      return false;
    }
  };
  priority_queue<Node*> toList(map<char, int> data) {
    priority_queue<Node*, vector<Node*>, HuffmanEncoding::Comparer > queue;
  }
  Node* buildTree() {
    Node* root;

  }
public:
  HuffmanEncoding(string message) {

  }

};

int main() {

  return 0;
}