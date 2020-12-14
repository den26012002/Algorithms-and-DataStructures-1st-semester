#include <fstream>
#include <algorithm>
#include <vector>

std::ifstream fin("balance.in");
std::ofstream fout("balance.out");

struct Node {
	int key;
	int leftInd;
	int rightInd;
	int height;
	int balance;
};

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
	for (int i(0); i < n; i++) {
		fout << node[i].balance << '\n';
	}

	return 0;
}