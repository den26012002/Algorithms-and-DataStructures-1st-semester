#include<fstream>
#include<vector>
#include<string>

const int MAX_SIZE = 1e4;

std::ifstream fin("brackets.in");
std::ofstream fout("brackets.out");

struct Stack {
public:
	void push(int x) {
		stack[++top] = x;
	}

	void pop() {
		top--;
	}

	char front() {
		return stack[top];
	}

	bool empty() {
		return top < 0;
	}

	Stack() {
		top = -1;
		stack.resize(MAX_SIZE);
	}

	Stack(int maxSize) {
		top = -1;
		stack.resize(maxSize);
	}
private:
	int top;
	std::vector<char> stack;
};

bool correctBrackets(std::string brackets) {
	Stack stack(brackets.size());
	for (int i(0); i < brackets.size(); i++) {
		switch (brackets[i]) {
		case '(':
		case '[':
			stack.push(brackets[i]);
			break;
		case ')':
			if (stack.empty()) {
				return false;
			}
			if (stack.front() == '[') {
				return false;
			}
			stack.pop();
			break;
		case ']':
			if (stack.empty()) {
				return false;
			}
			if (stack.front() == '(') {
				return false;
			}
			stack.pop();
			break;
		default:
			break;
		}
	}
	return stack.empty();
}

int main() {
	std::string str;
	while (fin >> str) {
		fout << (correctBrackets(str) ? "YES\n" : "NO\n");
	}
}