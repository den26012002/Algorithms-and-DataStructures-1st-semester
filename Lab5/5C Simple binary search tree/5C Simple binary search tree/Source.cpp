#include<fstream>
#include<algorithm>
#include<string>

const int ERR_VALUE = 1e9 + 5;

std::ifstream fin("bstsimple.in");
std::ofstream fout("bstsimple.out");

struct Node {
	Node* parent;
	int value;
	Node* leftChild;
	Node* rightChild;

	Node(int _value) {
		parent = nullptr;
		value = _value;
		leftChild = nullptr;
		rightChild = nullptr;
	}

	Node() {
		parent = nullptr;
		value = ERR_VALUE;
		leftChild = nullptr;
		rightChild = nullptr;
	}
};

class BinaryTree {
public:
	void insert(int value) {
		insert(new Node(value));
	}

	bool exists(int value) {
		return find(new Node(value));
	}

	int next(int value) {
		Node* ans = next(new Node(value));
		if (!ans) {
			return ERR_VALUE;
		}
		else {
			return ans->value;
		}
	}

	int prev(int value) {
		Node* ans = prev(new Node(value));
		if (!ans) {
			return ERR_VALUE;
		}
		else {
			return ans->value;
		}
	}

	void deleteValue(int value) {
		deleteNode(new Node(value));
	}

	BinaryTree(int rootValue) {
		root = new Node(rootValue);
	}

	BinaryTree() {
		root = nullptr;
	}
private:
	Node* root;

	void insert(Node* addedNode) {
		if (!root) {
			root = addedNode;
			return;
		}
		Node* parent = root;
		while (true) {
			if (addedNode->value > parent->value) {
				if (parent->rightChild) {
					parent = parent->rightChild;
				}
				else {
					addedNode->parent = parent;
					parent->rightChild = addedNode;
					break;
				}
			}
			else if (addedNode->value < parent->value) {
				if (parent->leftChild) {
					parent = parent->leftChild;
				}
				else {
					addedNode->parent = parent;
					parent->leftChild = addedNode;
					break;
				}
			}
			else {
				break;
			}
		}
	}

	Node* find(Node* node) {
		if (!root) {
			return nullptr;
		}
		Node* parent = root;
		while (true) {
			if (node->value > parent->value) {
				if (!parent->rightChild) {
					return nullptr;
				}
				else {
					parent = parent->rightChild;
				}
			}
			else if (node->value < parent->value) {
				if (!parent->leftChild) {
					return nullptr;
				}
				else {
					parent = parent->leftChild;
				}
			}
			else {
				return parent;
			}
		}
	}

	Node* next(Node* node) {
		if (!root) {
			return nullptr;
		}
		Node* parent = root;
		Node* ans = nullptr;
		while (true) {
			if (parent->value > node->value) {
				if (!ans || ans->value > parent->value) {
					ans = new Node(parent->value);
				}
				if (parent->leftChild) {
					parent = parent->leftChild;
				}
				else {
					break;
				}
			}
			else {
				if (parent->rightChild) {
					parent = parent->rightChild;
				}
				else {
					break;
				}
			}
		}
		return ans;
	}

	Node* prev(Node* node) {
		if (!root) {
			return nullptr;
		}
		Node* parent = root;
		Node* ans = nullptr;
		while (true) {
			if (parent->value < node->value) {
				if (!ans || ans->value < parent->value) {
					ans = new Node(parent->value);
				}
				if (parent->rightChild) {
					parent = parent->rightChild;
				}
				else {
					break;
				}
			}
			else {
				if (parent->leftChild) {
					parent = parent->leftChild;
				}
				else {
					break;
				}
			}
		}
		return ans;
	}

	void deleteNode(Node* node) {
		node = find(node);
		if (!node) {
			return;
		}
		if (!node->leftChild && !node->rightChild) {
			if (node == root) {
				root = nullptr;
			}
			else {
				if (node == node->parent->leftChild) {
					node->parent->leftChild = nullptr;
				}
				else if (node == node->parent->rightChild) {
					node->parent->rightChild = nullptr;
				}
				node->parent = nullptr;
			}
		}
		else if (!node->leftChild || !node->rightChild) {
			if (node->leftChild) {
				node->leftChild->parent = node->parent;
				if (node == node->parent->leftChild) {
					node->parent->leftChild = node->leftChild;
				}
				else if (node == node->parent->rightChild) {
					node->parent->rightChild = node->leftChild;
				}
			}
			else if (node->rightChild) {
				node->rightChild->parent = node->parent;
				if (node == node->parent->leftChild) {
					node->parent->leftChild = node->rightChild;
				}
				else if (node == node->parent->rightChild) {
					node->parent->rightChild = node->rightChild;
				}
			}
		}
		else {
			Node* nextNode = next(node, node);
			int newValue = nextNode->value;
			deleteNode(nextNode);
			node->value = newValue;
		}
	}

	Node* next(Node* start, Node* node) {
		if (!start) {
			return nullptr;
		}
		Node* parent = start;
		Node* ans = nullptr;
		while (true) {
			if (parent->value > node->value) {
				if (!ans || ans->value > parent->value) {
					ans = new Node(parent->value);
				}
				if (parent->leftChild) {
					parent = parent->leftChild;
				}
				else {
					break;
				}
			}
			else {
				if (parent->rightChild) {
					parent = parent->rightChild;
				}
				else {
					break;
				}
			}
		}
		return ans;
	}
};

int main() {
	BinaryTree tree(ERR_VALUE);
	std::string operation;
	while (fin >> operation) {
		if (operation == "insert") {
			int x;
			fin >> x;
			tree.insert(x);
		}
		else if (operation == "exists") {
			int x;
			fin >> x;
			fout << (tree.exists(x) ? "true\n" : "false\n");
		}
		else if (operation == "next") {
			int x;
			fin >> x;
			int ans = tree.next(x);
			if (ans == ERR_VALUE) {
				fout << "none\n";
			}
			else {
				fout << ans << '\n';
			}
		}
		else if (operation == "prev") {
			int x;
			fin >> x;
			int ans = tree.prev(x);
			if (ans == ERR_VALUE) {
				fout << "none\n";
			}
			else {
				fout << ans << '\n';
			}
		}
		else if (operation == "delete") {
			int x;
			fin >> x;
			tree.deleteValue(x);
		}
	}

	return 0;
}