#include<fstream>
#include<vector>

const int MAX_SIZE = 1e6;

std::ifstream fin("queue.in");
std::ofstream fout("queue.out");

struct Queue {
public:
	void push(int x) {
		inc(top);
		cntElems++;
		arr[top] = x;
	}
	
	void pop() {
		bottom++;
		cntElems--;
	}

	int back() {
		return arr[bottom];
	}

	bool empty() {
		return !cntElems;
	}

	Queue() {
		top = -1;
		bottom = 0;
		cntElems = 0;
		arr.resize(MAX_SIZE);
	}

	Queue(int maxSize) {
		top = -1;
		bottom = 0;
		cntElems = 0;
		arr.resize(maxSize);
	}
private:
	int top;
	int bottom;
	int cntElems;
	std::vector<int> arr;

	void inc(int& param) {
		param = (param + 1) % arr.size();
	}
};

int main() {
	int m;
	fin >> m;
	Queue q(m);
	for (int i(0); i < m; i++) {
		char symb;
		fin >> symb;
		switch (symb) {
		case '+':
			int n;
			fin >> n;
			q.push(n);
			break;
		case '-':
			fout << q.back() << '\n';
			q.pop();
			break;
		default:
			break;
		}
	}


	return 0;
}