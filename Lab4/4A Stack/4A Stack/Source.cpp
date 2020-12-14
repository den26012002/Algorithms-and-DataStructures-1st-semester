#include<fstream>
#include<vector>

const int MAX_SIZE = 1e6;


std::ifstream fin("stack.in");
std::ofstream fout("stack.out");

struct Stack {
public:
	void push(int x) {
		arr[++top] = x;
	}

	void pop() {
		top--;
	}

	int front() {
		return arr[top];
	}

	bool empty() {
		return top >= 0;
	}

	Stack() {
		arr.resize(MAX_SIZE);
		top = -1;
	}

	Stack(int maxSize) {
		arr.resize(maxSize);
		top = -1;
	}
private:
	std::vector<int> arr;
	int top;
};

int main() {
	int m;
	fin >> m;
	Stack stack(m);
	for (int i(0); i < m; i++) {
		char symb;
		fin >> symb;
		switch (symb) {
		case '+':
			int n;
			fin >> n;
			stack.push(n);
			break;
		case '-':
			fout << stack.front() << '\n';
			stack.pop();
			break;
		default:
			break;
		}
	}


	return 0;
}