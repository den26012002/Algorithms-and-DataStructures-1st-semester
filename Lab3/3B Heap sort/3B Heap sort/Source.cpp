#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

ifstream fin("sort.in");
ofstream fout("sort.out");

void print(vector<int> arr) {
	for (int i(0); i < arr.size(); i++) {
		fout << arr[i] << ' ';
	}
}

struct MaxHeap {
public:
	void readArray(int size) {
		heapSize = size;
		arr.resize(heapSize);
		for (int i(0); i < heapSize; i++) {
			fin >> arr[i];
		}
		buildMaxHeap();
	}

	vector<int> getArray() {
		return arr;
	}

	void sort() {
		while (heapSize > 0) {
			swap(arr[0], arr[--heapSize]);
			maxHeapify(0);
		}
	}

private:
	vector<int> arr;
	int heapSize;

	int getLeftChildIndex(int index) {
		return 2 * index + 1;
	}

	int getRightChildIndex(int index) {
		return 2 * index + 2;
	}

	bool correct(int index) {
		return (index < heapSize && index >= 0);
	}

	void maxHeapify(int index) {
		int l = getLeftChildIndex(index);
		int r = getRightChildIndex(index);
		int largest = index;
		if (correct(l) && arr[l] > arr[largest]) {
			largest = l;
		}
		if (correct(r) && arr[r] > arr[largest]) {
			largest = r;
		}
		if (index != largest) {
			swap(arr[index], arr[largest]);
			maxHeapify(largest);
		}
	}

	void buildMaxHeap() {
		for (int i(heapSize / 2 + 1); i >= 0; i--) {
			maxHeapify(i);
		}
	}
};

int main() {
	int n;
	fin >> n;
	MaxHeap heap;
	heap.readArray(n);
	heap.sort();
	print(heap.getArray());



	return 0;
}