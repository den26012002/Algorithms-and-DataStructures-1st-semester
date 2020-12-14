#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

std::ifstream fin("avlset.in");
std::ofstream fout("avlset.out");

int size = 0;

struct Node {
	int key;
	int leftInd;
	int rightInd;
	int height;
	int balance;
	bool erased;

	Node(int _key) {
		key = _key;
		leftInd = -1;
		rightInd = -1;
		height = 1;
		balance = 0;
		erased = false;
	}

	Node() {
		leftInd = -1;
		rightInd = -1;
		height = 1;
		balance = 0;
		erased = false;
	}
};

bool existsNumb(std::vector<Node>& node, int nodeNumb) {
	if (nodeNumb == -1 || node[nodeNumb].erased) {
		return false;
	}
	return true;
}

void findBalance(std::vector<Node>& node, int nodeNumb) {
	if (!existsNumb(node, node[nodeNumb].leftInd) && !existsNumb(node, node[nodeNumb].rightInd)) {
		node[nodeNumb].height = 1;
		node[nodeNumb].balance = 0;
	}
	else if (!existsNumb(node, node[nodeNumb].leftInd)) {
		node[nodeNumb].height = node[node[nodeNumb].rightInd].height + 1;
		node[nodeNumb].balance = node[node[nodeNumb].rightInd].height;
	}
	else if (!existsNumb(node, node[nodeNumb].rightInd)) {
		node[nodeNumb].height = node[node[nodeNumb].leftInd].height + 1;
		node[nodeNumb].balance = -node[node[nodeNumb].leftInd].height;
	}
	else {
		node[nodeNumb].height = std::max(node[node[nodeNumb].leftInd].height, node[node[nodeNumb].rightInd].height) + 1;
		node[nodeNumb].balance = node[node[nodeNumb].rightInd].height - node[node[nodeNumb].leftInd].height;
	}
}

void findBalances(std::vector<Node>& node) {
	int n = node.size();
	for (int i(n - 1); i >= 0; --i) {
		findBalance(node, i);
	}
}

void smallLeftRotation(std::vector<Node>& node, int nodeNumb) {
	std::swap(node[nodeNumb].key, node[node[nodeNumb].rightInd].key);
	std::swap(node[nodeNumb].leftInd, node[nodeNumb].rightInd);
	std::swap(node[node[nodeNumb].leftInd].leftInd, node[nodeNumb].rightInd);
	std::swap(node[node[nodeNumb].leftInd].rightInd, node[nodeNumb].rightInd);
	if (existsNumb(node, node[nodeNumb].leftInd)) {
		findBalance(node, node[nodeNumb].leftInd);
	}
	if (existsNumb(node, node[nodeNumb].rightInd)) {
		findBalance(node, node[nodeNumb].rightInd);
	}
	findBalance(node, nodeNumb);
}

void smallRightRotation(std::vector<Node>& node, int nodeNumb) {
	std::swap(node[nodeNumb].key, node[node[nodeNumb].leftInd].key);
	std::swap(node[nodeNumb].leftInd, node[nodeNumb].rightInd);
	std::swap(node[node[nodeNumb].rightInd].rightInd, node[nodeNumb].leftInd);
	std::swap(node[node[nodeNumb].rightInd].leftInd, node[nodeNumb].leftInd);
	if (existsNumb(node, node[nodeNumb].leftInd)) {
		findBalance(node, node[nodeNumb].leftInd);
	}
	if (existsNumb(node, node[nodeNumb].rightInd)) {
		findBalance(node, node[nodeNumb].rightInd);
	}
	findBalance(node, nodeNumb);
}

void bigLeftRotation(std::vector<Node>& node, int nodeNumb) {
	smallRightRotation(node, node[nodeNumb].rightInd);
	smallLeftRotation(node, nodeNumb);
}

void bigRightRotation(std::vector<Node>& node, int nodeNumb) {
	smallLeftRotation(node, node[nodeNumb].leftInd);
	smallRightRotation(node, nodeNumb);
}

void rebalance(std::vector<Node>& node, int nodeNumb) {
	findBalance(node, nodeNumb);
	if (node[nodeNumb].balance > 1) {
		if (node[node[nodeNumb].rightInd].balance == -1) {
			bigLeftRotation(node, nodeNumb);
		}
		else {
			smallLeftRotation(node, nodeNumb);
		}
	}
	else if (node[nodeNumb].balance < -1) {
		if (node[node[nodeNumb].leftInd].balance == 1) {
			bigRightRotation(node, nodeNumb);
		}
		else {
			smallRightRotation(node, nodeNumb);
		}
	}
}

void rebuildTree(std::vector<Node>& node) {
	if (size == 0) {
		return;
	}
	std::vector<Node> ans(size);
	std::queue<Node> q;
	q.push(node[0]);
	int cnt = 1;
	for (int i(0); i < ans.size(); i++) {
		Node nodeNow = q.front();
		q.pop();
		ans[i] = nodeNow;
		if (existsNumb(node, ans[i].leftInd)) {
			ans[i].leftInd = cnt++;
		}
		else {
			ans[i].leftInd = -1;
		}
		if (existsNumb(node, ans[i].rightInd)) {
			ans[i].rightInd = cnt++;
		}
		else {
			ans[i].rightInd = -1;
		}
		if (existsNumb(node, nodeNow.leftInd)) {
			q.push(node[nodeNow.leftInd]);
		}
		if (existsNumb(node, nodeNow.rightInd)) {
			q.push(node[nodeNow.rightInd]);
		}
	}
	node = ans;
}

void insert(std::vector<Node>& node, int key, int nodeNumb = 0) {
	if (node.size() == 0) {
		node.push_back(Node(key));
		size++;
		findBalance(node, 0);
		rebalance(node, 0);
		findBalance(node, 0);
		return;
	}
	if (key < node[nodeNumb].key) {
		if (existsNumb(node, node[nodeNumb].leftInd)) {
			insert(node, key, node[nodeNumb].leftInd);
		}
		else {
			node[nodeNumb].leftInd = node.size();
			node.push_back(Node(key));
			size++;
		}
	}
	else if (key > node[nodeNumb].key) {
		if (existsNumb(node, node[nodeNumb].rightInd)) {
			insert(node, key, node[nodeNumb].rightInd);
		}
		else {
			node[nodeNumb].rightInd = node.size();
			node.push_back(Node(key));
			size++;
		}
	}
	findBalance(node, nodeNumb);
	rebalance(node, nodeNumb);
	findBalance(node, nodeNumb);
}

void erase(std::vector<Node>& node, int key, int nodeNumb = 0) {
	/*if (!existsNumb(node, nodeNumb)) {
		return;
	}*/
	if (size == 0) {
		return;
	}
	if (size == 1) {
		rebuildTree(node);
		if (node[0].key == key) {
			node.pop_back();
			size--;
		}
		return;
	}
	if (key < node[nodeNumb].key) {
		if (existsNumb(node, node[nodeNumb].leftInd)) {
			erase(node, key, node[nodeNumb].leftInd);
		}
	}
	else if (key > node[nodeNumb].key) {
		if (existsNumb(node, node[nodeNumb].rightInd)) {
			erase(node, key, node[nodeNumb].rightInd);
		}
	}
	else {
		if (!existsNumb(node, node[nodeNumb].leftInd) && !existsNumb(node, node[nodeNumb].rightInd)) {
			node[nodeNumb].erased = true;
			size--;
		}
		else if (!existsNumb(node, node[nodeNumb].leftInd)) {
			std::swap(node[node[nodeNumb].rightInd].key, node[nodeNumb].key);
			erase(node, key, node[nodeNumb].rightInd);
		}
		else {
			int helpNodeNumb = node[nodeNumb].leftInd;
			while (existsNumb(node, node[helpNodeNumb].rightInd)) {
				helpNodeNumb = node[helpNodeNumb].rightInd;
			}
			std::swap(node[helpNodeNumb].key, node[nodeNumb].key);
			erase(node, key, node[nodeNumb].leftInd);
		}
	}
	findBalance(node, nodeNumb);
	rebalance(node, nodeNumb);
	findBalance(node, nodeNumb);
}

bool exists(std::vector<Node>& node, int key, int nodeNumb = 0) {
	if (size == 0) {
		return false;
	}
	if (key < node[nodeNumb].key) {
		if (existsNumb(node, node[nodeNumb].leftInd)) {
			return exists(node, key, node[nodeNumb].leftInd);
		}
		return false;
	}
	else if (key > node[nodeNumb].key) {
		if (existsNumb(node, node[nodeNumb].rightInd)) {
			return exists(node, key, node[nodeNumb].rightInd);
		}
		return false;
	}
	else {
		return true;
	}
}

int main() {
	int n;
	fin >> n;
	std::vector<Node> node;
	for (int i(0); i < n; ++i) {
		char operation;
		int x;
		fin >> operation >> x;
		findBalances(node);
		switch (operation) {
		case 'A':
			insert(node, x);
			fout << node[0].balance << '\n';
			break;
		case 'D':
			erase(node, x);
			rebuildTree(node);
			if (size == 0) {
				fout << -1 << '\n';
			}
			else {
				fout << node[0].balance << '\n';
			}
			break;
		case 'C':
			fout << (exists(node, x) ? 'Y' : 'N') << '\n';
		}
	}

	return 0;
}