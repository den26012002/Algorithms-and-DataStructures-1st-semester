#include<fstream>
#include<vector>
#include<string>
#include<math.h>

std::ifstream fin("set.in");
std::ofstream fout("set.out");

struct Node {
	int value;
	Node* next;

	Node(int _value) {
		value = _value;
		next = nullptr;
	}

	Node() {
		next = nullptr;
	}
};

struct List {
	Node* root;

	void insert(int x) {
		if (exists(x)) {
			return;
		}
		if (root == nullptr) {
			root = new Node(x);
			return;
		}
		Node* parent = root;
		while (parent->next != nullptr) {
			parent = parent->next;
		}
		parent->next = new Node(x);
	}

	bool exists(int x) {
		Node* parent = root;
		while (parent != nullptr) {
			if (parent->value == x) {
				return true;
			}
			parent = parent->next;
		}
		return false;
	}

	void deleteElement(int x) {
		if (root == nullptr) {
			return;
		}
		if (root->value == x) {
			root = root->next;
			return;
		}
		Node* parent = root;
		while (parent->next != nullptr) {
			if (parent->next->value == x) {
				parent->next = parent->next->next;
				return;
			}
			parent = parent->next;
		}
	}
	
	List() {
		root = nullptr;
	}
};

struct Set {
public:
	void insert(int x) {
		table[getHash(x)].insert(x);
	}

	bool exists(int x) {
		return table[getHash(x)].exists(x);
	}

	void deleteElement(int x) {
		return table[getHash(x)].deleteElement(x);
	}

	Set() {
		table.resize(100003);
	}

private:
	std::vector<List> table;

	int getHash(int x) {
		return std::abs(x % 100003);
	}
};

int main() {
	Set set;
	std::string operation;
	while (fin >> operation) {
		int x;
		fin >> x;
		if (operation == "insert") {
			set.insert(x);
		}
		else if (operation == "exists") {
			fout << (set.exists(x) ? "true\n" : "false\n");
		}
		else if (operation == "delete") {
			set.deleteElement(x);
		}
	}

	return 0;
}