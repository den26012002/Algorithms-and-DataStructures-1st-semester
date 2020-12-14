/*#include<fstream>
#include<vector>
#include<string>
#include<math.h>

std::ifstream fin("linkedmap.in");
std::ofstream fout("linkedmap.out");

const int MAX_HASH = 100003;
struct Node {
	std::string key;
	std::string value;
	Node* next;
	Node* nextElement;
	Node* prevElement;

	Node(std::string _key, std::string _value) {
		key = _key;
		value = _value;
		next = nullptr;
		nextElement = nullptr;
		prevElement = nullptr;
	}

	Node() {
		next = nullptr;
		prevElement = nullptr;
		nextElement = nullptr;
	}
};

Node* tailElement;

struct List {
	Node* root;

	void put(std::string key, std::string value) {
		if (root == nullptr) {
			root = new Node(key, value);
			tailElement = root;
			return;
		}
		if (root->key == key) {
			root->value = value;
			return;
		}
		Node* parent = root;
		while (parent->next != nullptr) {
			if (parent->next->key == key) {
				parent->next->value = value;
				return;
			}
			parent = parent->next;
		}
		parent->next = new Node(key, value);
		parent->next->prevElement = tailElement;
		if (tailElement != nullptr) {
			parent->next->prevElement->nextElement = parent->next;
		}
		tailElement = parent->next;
	}

	std::string get(std::string key) {
		Node* parent = root;
		while (parent != nullptr) {
			if (parent->key == key) {
				return parent->value;
			}
			parent = parent->next;
		}
		return "none";
	}

	std::string next(std::string key) {
		Node* parent = root;
		while (parent != nullptr) {
			if (parent->key == key && parent->nextElement != nullptr) {
				return parent->nextElement->value;
			}
			parent = parent->next;
		}
		return "none";
	}

	std::string prev(std::string key) {
		Node* parent = root;
		while (parent != nullptr) {
			if (parent->key == key && parent->prevElement != nullptr) {
				return parent->prevElement->value;
			}
			parent = parent->next;
		}
		return "none";
	}

	void deleteElement(std::string key) {
		if (root == nullptr) {
			return;
		}
		if (root->key == key) {
			root = root->next;
			return;
		}
		Node* parent = root;
		while (parent->next != nullptr) {
			if (parent->next->key == key) {
				if (parent->next == tailElement) {
					tailElement = parent->next->prevElement;
				}
				if (parent->nextElement != nullptr) {
					parent->next->nextElement->prevElement = parent->next->prevElement;
				}
				if (parent->prevElement != nullptr) {
					parent->next->prevElement->nextElement = parent->next->nextElement;
				}
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

struct LinkedMap {
public:
	void put(std::string key, std::string value) {
		table[getHash(key)].put(key, value);
	}

	std::string get(std::string key) {
		return table[getHash(key)].get(key);
	}

	void deleteElement(std::string key) {
		return table[getHash(key)].deleteElement(key);
	}

	std::string prev(std::string key) {
		return table[getHash(key)].prev(key);
	}

	std::string next(std::string key) {
		return table[getHash(key)].next(key);
	}

	LinkedMap() {
		table.resize(MAX_HASH);
		tailElement = nullptr;
	}

private:
	std::vector<List> table;

	int getHash(std::string key) {
		int hash = 0;
		for (int i(0); i < key.size(); i++) {
			hash = std::abs((((hash * 101) % MAX_HASH) + (key[i] - 'a' + 1)) % MAX_HASH);
		}
		return hash;
	}
};

int main() {
	LinkedMap map;
	std::string operation;
	while (fin >> operation) {
		if (operation == "put") {
			std::string x, y;
			fin >> x >> y;
			map.put(x, y);
		}
		else if (operation == "delete") {
			std::string x;
			fin >> x;
			map.deleteElement(x);
		}
		else if (operation == "get") {
			std::string x;
			fin >> x;
			fout << map.get(x) << '\n';
		}
		else if (operation == "prev") {
			std::string x;
			fin >> x;
			fout << map.prev(x) << '\n';
		}
		else if (operation == "next") {
			std::string x;
			fin >> x;
			fout << map.next(x) << '\n';
		}
	}

	return 0;
}*/
#include<fstream>
#include<vector>
#include<string>
#include<math.h>

std::ifstream fin("linkedmap.in");
std::ofstream fout("linkedmap.out");

const int MAX_HASH = 100003;

struct Node {
	std::string key;
	std::string value;
	Node* next;
	Node* nextElement;
	Node* prevElement;

	Node(std::string _key, std::string _value) {
		key = _key;
		value = _value;
		next = nullptr;
		nextElement = nullptr;
		prevElement = nullptr;
	}

	Node() {
		next = nullptr;
		nextElement = nullptr;
		prevElement = nullptr;
	}
};

struct List {
	Node* root;

	void put(std::string key, std::string value, Node* &tailElement) {
		if (root == nullptr) {
			root = new Node(key, value);
			if (tailElement != nullptr) {
				tailElement->nextElement = root;
			}
			root->prevElement = tailElement;
			tailElement = root;
			return;
		}
		if (root->key == key) {
			root->value = value;
			return;
		}
		Node* parent = root;
		while (parent->next != nullptr) {
			if (parent->next->key == key) {
				parent->next->value = value;
				return;
			}
			parent = parent->next;
		}
		parent->next = new Node(key, value);
		if (tailElement != nullptr) {
			tailElement->nextElement = parent->next;
		}
		parent->next->prevElement = tailElement;
		tailElement = parent->next;
	}

	std::string get(std::string key) {
		Node* parent = root;
		while (parent != nullptr) {
			if (parent->key == key) {
				return parent->value;
			}
			parent = parent->next;
		}
		return "";
	}

	void deleteElement(std::string key, Node* &tailElement) {
		if (root == nullptr) {
			return;
		}
		if (root->key == key) {
			if (root == tailElement) {
				tailElement = tailElement->prevElement;
			}
			if (root->prevElement != nullptr) {
				root->prevElement->nextElement = root->nextElement;
			}
			if (root->nextElement != nullptr) {
				root->nextElement->prevElement = root->prevElement;
			}
			root = root->next;
			return;
		}
		Node* parent = root;
		while (parent->next != nullptr) {
			if (parent->next->key == key) {
				if (parent->next == tailElement && tailElement != nullptr) {
					tailElement = tailElement->prevElement;
				}
				if (parent->next->prevElement != nullptr) {
					parent->next->prevElement->nextElement = parent->next->nextElement;
				}
				if (parent->next->nextElement != nullptr) {
					parent->next->nextElement->prevElement = parent->next->prevElement;
				}
				parent->next = parent->next->next;
				return;
			}
			parent = parent->next;
		}
	}

	std::string next(std::string key) {
		Node* parent = root;
		while (parent != nullptr) {
			if (parent->key == key) {
				if (parent->nextElement == nullptr) {
					return "";
				}
				return parent->nextElement->value;
			}
			parent = parent->next;
		}
		return "";
	}

	std::string prev(std::string key) {
		Node* parent = root;
		while (parent != nullptr) {
			if (parent->key == key) {
				if (parent->prevElement == nullptr) {
					return "";
				}
				return parent->prevElement->value;
			}
			parent = parent->next;
		}
		return "";
	}

	List() {
		root = nullptr;
	}
};

struct Map {
public:
	void put(std::string key, std::string value) {
		table[getHash(key)].put(key, value, tailElement);
	}

	std::string get(std::string key) {
		return table[getHash(key)].get(key);
	}

	void deleteElement(std::string key) {
		table[getHash(key)].deleteElement(key, tailElement);
	}

	std::string next(std::string key) {
		return table[getHash(key)].next(key);
	}

	std::string prev(std::string key) {
		return table[getHash(key)].prev(key);
	}

	Map() {
		table.resize(MAX_HASH);
		tailElement = nullptr;
	}

private:
	Node* tailElement;
	std::vector<List> table;


	int getHash(std::string key) {
		int hash = 0;
		for (int i(0); i < key.size(); i++) {
			hash = std::abs((((hash * 101) % MAX_HASH) + (key[i] - 'a' + 1)) % MAX_HASH);
		}
		return hash;
	}
};

int main() {
	Map map;
	std::string operation;
	while (fin >> operation) {
		if (operation == "put") {
			std::string x, y;
			fin >> x >> y;
			map.put(x, y);
		}
		else if (operation == "delete") {
			std::string x;
			fin >> x;
			map.deleteElement(x);
		}
		else if (operation == "get") {
			std::string x;
			fin >> x;
			std::string ans = map.get(x);
			if (ans == "") {
				fout << "none\n";
			}
			else {
				fout << ans << '\n';
			}
		}
		else if (operation == "prev") {
			std::string x;
			fin >> x;
			std::string ans = map.prev(x);
			if (ans == "") {
				fout << "none\n";
			}
			else {
				fout << ans << '\n';
			}
		}
		else if (operation == "next") {
			std::string x;
			fin >> x;
			std::string ans = map.next(x);
			if (ans == "") {
				fout << "none\n";
			}
			else {
				fout << ans << '\n';
			}
		}
	}

	return 0;
}