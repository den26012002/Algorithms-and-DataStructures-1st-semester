#include<fstream>
#include<vector>
#include<string>
#include<math.h>

std::ifstream fin("map.in");
std::ofstream fout("map.out");

const int MAX_HASH = 100003;

struct Node {
	std::string key;
	std::string value;
	Node* next;

	Node(std::string _key, std::string _value) {
		key = _key;
		value = _value;
		next = nullptr;
	}

	Node() {
		next = nullptr;
	}
};

struct List {
	Node* root;

	void put(std::string key, std::string value) {
		if (root == nullptr) {
			root = new Node(key, value);
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

struct Map {
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

	Map() {
		table.resize(MAX_HASH);
	}

private:
	std::vector<List> table;

	int getHash(std::string key) {
		int hash = 0;
		for (int i(0); i < key.size(); i++) {
			hash = std::abs( (((hash * 101) % MAX_HASH) + (key[i] - 'a' + 1)) % MAX_HASH);
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
	}

	return 0;
}