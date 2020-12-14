#include<fstream>
#include<vector>

const int MAX_SIZE = 100;

std::ifstream fin("postfix.in");
std::ofstream fout("postfix.out");

struct PostfixStack {
public:
	void push(int x) {
		stack[++top] = x;
	}

	void pop() {
		top--;
	}

	int front() {
		return stack[top];
	}

	bool empty() {
		return top < 0;
	}

	void makeOperation(char operation) {
		switch (operation) {
		case '+':
			stack[top - 1] += stack[top];
			break;
		case '-':
			stack[top - 1] -= stack[top];
			break;
		case '*':
			stack[top - 1] *= stack[top];
			break;
		default:
			break;
		}
		top--;
	}

	PostfixStack() {
		top = -1;
		stack.resize(MAX_SIZE);
	}

	PostfixStack(int maxSize) {
		top = -1;
		stack.resize(maxSize);
	}

private:
	int top;
	std::vector<int> stack;
};

bool isNumber(char symb) {
	return (symb >= '0' && symb <= '9');
}

int main() {
	char symb;
	PostfixStack stack;
	while (fin >> symb) {
		if (isNumber(symb)) {
			stack.push(symb - '0');
		}
		else {
			stack.makeOperation(symb);
		}
	}
	fout << stack.front();

	return 0;
}