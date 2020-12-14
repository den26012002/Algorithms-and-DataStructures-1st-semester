#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

std::ifstream fin("rotation.in");
std::ofstream fout("rotation.out");

struct Node {
	int key;
	int leftInd;
	int rightInd;
	int height;
	int balance;
};

void findBalances(std::vector<Node>& node) {
	int n = node.size();
	for (int i(n - 1); i >= 0; --i) {
		if (node[i].leftInd == -1 && node[i].rightInd == -1) {
			node[i].height = 1;
			node[i].balance = 0;
		}
		else if (node[i].leftInd == -1) {
			node[i].height = node[node[i].rightInd].height + 1;
			node[i].balance = node[node[i].rightInd].height;
		}
		else if (node[i].rightInd == -1) {
			node[i].height = node[node[i].leftInd].height + 1;
			node[i].balance = -node[node[i].leftInd].height;
		}
		else {
			node[i].height = std::max(node[node[i].leftInd].height, node[node[i].rightInd].height) + 1;
			node[i].balance = node[node[i].rightInd].height - node[node[i].leftInd].height;
		}
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

void rebuildTree(std::vector<Node>& node) {
	std::vector<Node> ans(node.size());
	std::queue<Node> q;
	q.push(node[0]);
	int cnt = 1;
	for (int i(0); i < ans.size(); i++) {
		Node nodeNow = q.front();
		q.pop();
		ans[i] = nodeNow;
		if (ans[i].leftInd != -1) {
			ans[i].leftInd = cnt++;
		}
		if (ans[i].rightInd != -1) {
			ans[i].rightInd = cnt++;
		}
		if (nodeNow.leftInd != -1) {
			q.push(node[nodeNow.leftInd]);
		}
		if (nodeNow.rightInd != -1) {
			q.push(node[nodeNow.rightInd]);
		}
	}
	node = ans;
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
	}
	findBalances(node);
	if (node[node[0].rightInd].balance == -1) {
		bigLeftRotation(node, 0);
	}
	else {
		smallLeftRotation(node, 0);
	}
	rebuildTree(node);
	fout << n << '\n';
	for (int i(0); i < n; ++i) {
		fout << node[i].key << ' ' << node[i].leftInd + 1 << ' ' << node[i].rightInd + 1 << '\n';
	}


	return 0;
}