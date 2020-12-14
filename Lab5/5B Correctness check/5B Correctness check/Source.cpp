#include<fstream>
#include<vector> 
#include<algorithm>

using namespace std;

std::ifstream fin("check.in");
std::ofstream fout("check.out");

const int INF = 1e9 + 5;

struct Node {
	int value;
	int leftChildIndex;
	int rightChildIndex;
};

/*bool correct(std::vector<Node>& tree, int position = 0) {
	if (position == -1) {
		return true;
	}
	Node parent = tree[position];
	if (correct(tree, parent.leftChildIndex) && correct(tree, parent.rightChildIndex)) {
		if (parent.leftChildIndex == -1 && parent.rightChildIndex == -1) {
			return true;
		}
		else if (parent.leftChildIndex == -1) {
			Node rightChild = tree[parent.rightChildIndex];
			if (correct(tree, parent.rightChildIndex)) {
				if (parent.value < rightChild.value) {
					
				}
			}
		}
	}
}*/

bool correct(std::vector<Node>& tree, int position = 0, int min = -INF, int max = INF) {
	if (tree.size() == 0) {
		return true;
	}
	if (position == -1) {
		return true;
	}
	Node parent = tree[position];
	if (parent.value <= min || parent.value >= max) {
		return false;
	}
	if (parent.leftChildIndex != -1 && parent.rightChildIndex != -1) {
		Node leftChild = tree[parent.leftChildIndex];
		Node rightChild = tree[parent.rightChildIndex];
		if (parent.value > leftChild.value && parent.value < rightChild.value) {
			return (correct(tree, parent.leftChildIndex, min, parent.value) && correct(tree, parent.rightChildIndex, parent.value, max));
		}
		else {
			return false;
		}
	}
	else if (parent.rightChildIndex != -1) {
		Node rightChild = tree[parent.rightChildIndex];
		if (parent.value < rightChild.value) {
			return correct(tree, parent.rightChildIndex, parent.value, max);
		}
		else {
			return false;
		}
	}
	else if (parent.leftChildIndex != -1) {
		Node leftChild = tree[parent.leftChildIndex];
		if (parent.value > leftChild.value) {
			return correct(tree, parent.leftChildIndex, min, parent.value);
		}
		else {
			return false;
		}
	}
	else {
		return true;
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
	/*for (int i(0); i < n; i++) {
		Node parent = binaryTree[i];
		if (parent.leftChildIndex != -1) {
			Node leftChild = binaryTree[parent.leftChildIndex];
			if (parent.value <= leftChild.value) {
				fout << "NO";
				return 0;
			}
		}
		if (parent.rightChildIndex != -1) {
			Node rightChild = binaryTree[parent.rightChildIndex];
			if (parent.value >= rightChild.value) {
				fout << "NO";
				return 0;
			}
		}
	}
	fout << "YES";*/
	fout << (correct(binaryTree) ? "YES" : "NO");


	return 0;
}