#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

std::ifstream fin("deletion.in");
std::ofstream fout("deletion.out");

int size;

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
}

void smallRightRotation(std::vector<Node>& node, int nodeNumb) {
	std::swap(node[nodeNumb].key, node[node[nodeNumb].leftInd].key);
	std::swap(node[nodeNumb].leftInd, node[nodeNumb].rightInd);
	std::swap(node[node[nodeNumb].rightInd].rightInd, node[nodeNumb].leftInd);
	std::swap(node[node[nodeNumb].rightInd].leftInd, node[nodeNumb].leftInd);
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
	findBalances(node);
}

void rebuildTree(std::vector<Node>& node) {
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
	}
	if (key < node[nodeNumb].key) {
		if (existsNumb(node, node[nodeNumb].leftInd)) {
			insert(node, key, node[nodeNumb].leftInd);
		}
		else {
			node[nodeNumb].leftInd = node.size();
			node.push_back(Node(key));
		}
	}
	else if (key > node[nodeNumb].key) {
		if (existsNumb(node, node[nodeNumb].rightInd)) {
			insert(node, key, node[nodeNumb].rightInd);
		}
		else {
			node[nodeNumb].rightInd = node.size();
			node.push_back(Node(key));
		}
	}
	findBalance(node, nodeNumb);
	rebalance(node, nodeNumb);
	findBalance(node, nodeNumb);
}

void erase(std::vector<Node>& node, int key, int nodeNumb = 0) {
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

int main() {
	int n;
	fin >> n;
	std::vector<Node> node(n);
	for (int i(0); i < n; ++i) {
		int k, l, r;
		fin >> k >> l >> r;
		node[i].key = k;
		node[i].leftInd = l - 1;
		node[i].rightInd = r - 1;
		size++;
	}
	findBalances(node);
	int x;
	fin >> x;
	erase(node, x);
	rebuildTree(node);
	fout << node.size() << '\n';
	for (int i(0); i < node.size(); ++i) {
		fout << node[i].key << ' ' << node[i].leftInd + 1 << ' ' << node[i].rightInd + 1 << '\n';
	}


	return 0;
}