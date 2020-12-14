#include<fstream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

ifstream fin("priorityqueue.in");
ofstream fout("priorityqueue.out");

void print(vector<int> arr) {
	for (int i(0); i < arr.size(); i++) {
		fout << arr[i] << ' ';
	}
}

struct Element {
	int value;
	int lineNumber;

	Element(int _value, int _lineNumber) {
		value = _value;
		lineNumber = _lineNumber;
	}

	Element() {}
};

class MinHeap {
public:
	void push(int x, int line) {
		arr.resize(heapSize + 1);
		arr[heapSize] = { x, line };
		shiftUp(heapSize);
		heapSize++;
	}

	int getMin() {
		return arr[0].value;
	}

	void extractMin() {
		if (heapSize == 0) {
			return;
		}
		swap(arr[0], arr[--heapSize]);
		if (heapSize > 0) {
			shiftDown(0);
		}
	}

	void decreaseKey(int line, int newValue) {
		for (int i(0); i < heapSize; i++) {
			if (arr[i].lineNumber == line) {
				arr[i].value = newValue;
				shiftUp(i);
				break;
			}
		}
	}

	bool empty() {
		return (heapSize == 0);
	}

	MinHeap(vector<Element>& _el, int size) {
		arr = _el;
		heapSize = size;
		buildMinHeap();
	}

	MinHeap() {
		heapSize = 0;
	}

private:
	vector<Element> arr;
	int heapSize;

	bool correct(int index) {
		return (index >= 0 && index < heapSize);
	}

	int getParentIndex(int index) {
		return (index - 1) / 2;
	}

	int getLeftChildIndex(int index) {
		return index * 2 + 1;
	}

	int getRightChildIndex(int index) {
		return index * 2 + 2;
	}

	void shiftDown(int index) {
		int l = getLeftChildIndex(index);
		int r = getRightChildIndex(index);
		int smallest = index;
		if (correct(l) && arr[l].value < arr[smallest].value) {
			smallest = l;
		}
		if (correct(r) && arr[r].value < arr[smallest].value) {
			smallest = r;
		}
		if (smallest != index) {
			swap(arr[smallest], arr[index]);
			shiftDown(smallest);
		}
	}

	void shiftUp(int index) {
		int p = getParentIndex(index);
		while (correct(p) && index > 0 && arr[p].value > arr[index].value) {
			swap(arr[p], arr[index]);
			index = p;
			p = getParentIndex(index);
		}
	}

	void buildMinHeap() {
		for (int i(heapSize / 2 + 1); i >= 0; i--) {
			shiftDown(i);
		}
	}
};

int main() {
	MinHeap heap;
	string str;
	int cntLine = 0;
	while (fin >> str) {
		cntLine++;
		if (str == "push") {
			int x;
			fin >> x;
			heap.push(x, cntLine);
		}
		else if (str == "extract-min") {
			if (heap.empty()) {
				fout << "*\n";
			}
			else {
				fout << heap.getMin() << '\n';
				heap.extractMin();
			}
		}
		else if (str == "decrease-key") {
			int x, y;
			fin >> x >> y;
			heap.decreaseKey(x, y);
		}	
	}


	return 0;
}