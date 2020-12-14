#include<fstream>
#include<vector>
#include<string>
#include<math.h>

std::ifstream fin("multimap.in");
std::ofstream fout("multimap.out");

const int MAX_HASH = 100007;

class Set {
public:
	void insert(std::string x) {
		if (table[getHash(x)].insert(x)) {
			size++;
		}
	}

	bool exists(std::string x) {
		return table[getHash(x)].exists(x);
	}

	void deleteElement(std::string x) {
		if (table[getHash(x)].deleteElement(x)) {
			size--;
		}
	}

	int getSize() {
		return size;
	}

	bool empty() {
		return (size == 0);
	}

	void print() {
		fout << size << ' ';
		for (int i(0); i < 107; i++) {
			if (!table[i].empty()) {
				table[i].print();
			}
		}
		fout << '\n';
	}

	Set() {
		table.resize(107);
		size = 0;
	}

private:

	struct Node {
		std::string value;
		Node* next;

		Node(std::string _value) {
			value = _value;
			next = nullptr;
		}

		Node() {
			next = nullptr;
		}
	};

	class List {
	public:
		bool insert(std::string x) {
			if (exists(x)) {
				return false;
			}
			if (root == nullptr) {
				root = new Node(x);
				size++;
				return true;
			}
			Node* parent = root;
			while (parent->next != nullptr) {
				parent = parent->next;
			}
			parent->next = new Node(x);
			size++;
			return true;
		}

		bool exists(std::string x) {
			Node* parent = root;
			while (parent != nullptr) {
				if (parent->value == x) {
					return true;
				}
				parent = parent->next;
			}
			return false;
		}

		bool deleteElement(std::string x) {
			if (root == nullptr) {
				return false;
			}
			if (root->value == x) {
				root = root->next;
				size--;
				return true;
			}
			Node* parent = root;
			while (parent->next != nullptr) {
				if (parent->next->value == x) {
					parent->next = parent->next->next;
					size--;
					return true;
				}
				parent = parent->next;
			}
			return false;
		}

		int getSize() {
			return size;
		}

		bool empty() {
			return (size == 0);
		}

		void print(std::string end = "", std::string sep = " ") {
			Node* element = root;
			while (element != nullptr) {
				fout << element->value << sep;
				element = element->next;
			}
			fout << end;
		}

		List() {
			root = nullptr;
			size = 0;
		}
	private:
		Node* root;
		int size;
	};

	std::vector<List> table;
	int size;

	int getHash(std::string key) {
		int hash = 0;
		for (int i(0); i < key.size(); i++) {
			hash = std::abs((((hash * 31) % MAX_HASH) + (key[i] - 'a' + 1)) % 107);
		}
		return hash;
	}

};

class MultiMap {
public:
	void put(std::string key, std::string value) {
		table[getHash(key)].put(key, value);
	}

	Set get(std::string key) {
		return table[getHash(key)].get(key);
	}

	void deleteAllElements(std::string key) {
		table[getHash(key)].deleteAllElements(key);
	}

	void deleteElement(std::string key, std::string value) {
		table[getHash(key)].deleteElement(key, value);
	}

	MultiMap() {
		table.resize(MAX_HASH);
	}

private:
	struct Node {
		std::string key;
		Set values;
		Node* next;

		Node(std::string _key, std::string _value) {
			key = _key;
			values.insert(_value);
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
				root->values.insert(value);
				return;
			}
			Node* parent = root;
			while (parent->next != nullptr) {
				if (parent->next->key == key) {
					parent->next->values.insert(value);
					return;
				}
				parent = parent->next;
			}
			parent->next = new Node(key, value);
		}
		
		Set get(std::string key) {
			Node* parent = root;
			while (parent != nullptr) {
				if (parent->key == key) {
					return parent->values;
				}
				parent = parent->next;
			}
			return Set();
		}

		void deleteAllElements(std::string key) {
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

		void deleteElement(std::string key, std::string value) {
			if (root == nullptr) {
				return;
			}
			if (root->key == key) {
				root->values.deleteElement(value);
				return;
			}
			Node* parent = root;
			while (parent->next != nullptr) {
				if (parent->next->key == key) {
					parent->next->values.deleteElement(value);
					return;
				}
				parent = parent->next;
			}
		}

		List() {
			root = nullptr;
		}
	};

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
	fin.sync_with_stdio(false);
	fout.sync_with_stdio(false);
	fin.tie(0);
	MultiMap map;
	std::string operation;
	while (fin >> operation) {
		if (operation == "put") {
			std::string x, y;
			fin >> x >> y;
			map.put(x, y);
		}
		else if (operation == "delete") {
			std::string x, y;
			fin >> x >> y;
			map.deleteElement(x, y);
		}
		else if (operation == "deleteall") {
			std::string x;
			fin >> x;
			map.deleteAllElements(x);
		}
		else if (operation == "get") {
			std::string x;
			fin >> x;
			map.get(x).print();
		}
	}

	return 0;
}