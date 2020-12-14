#include<fstream>
#include<vector> 
#include<algorithm>

using namespace std;

std::ifstream fin("height.in");
std::ofstream fout("height.out");

struct Node {
	int value;
	int leftChildIndex;
	int rightChildIndex;
};

int findDepth(const vector<Node>& tree, int startIndex) {
	Node start = tree[startIndex];
	if (start.leftChildIndex == -1 && start.rightChildIndex == -1) {
		return 1;
	}
	else if (start.leftChildIndex == -1) {
		return findDepth(tree, start.rightChildIndex) + 1;
	}
	else if (start.rightChildIndex == -1) {
		return findDepth(tree, start.leftChildIndex) + 1;
	}
	else {
		return std::max(findDepth(tree, start.leftChildIndex), findDepth(tree, start.rightChildIndex)) + 1;
	}
}

int main() {
	int n;
	fin >> n;
	std::vector<Node> binaryTree(n);
	for (int i(0); i < n; i++) {
		fin >> binaryTree[i].value >> binaryTree[i].leftChildIndex >> binaryTree[i].rightChildIndex;
		binaryTree[i].leftChildIndex--;
		binaryTree[i].rightChildIndex--;
	}
	if (n == 0) {
		fout << 0;
	}
	else {
		fout << findDepth(binaryTree, 0);
	}


	return 0;
}