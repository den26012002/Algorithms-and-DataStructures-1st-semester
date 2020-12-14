#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& array, int left, int mid, int right) {
	//left included, right excluded
	int index1 = left;
	int index2 = mid;
	int indexRes = 0;
	vector<int> result(right - left);
	while (index1 < mid || index2 < right) {
		if (index2 == right) {
			result[indexRes++] = array[index1++];
		}
		else if (index1 == mid) {
			result[indexRes++] = array[index2++];
		}
		else if (array[index1] < array[index2]) {
			result[indexRes++] = array[index1++];
		}
		else {
			result[indexRes++] = array[index2++];
		}
	}
	indexRes = 0;
	for (int i(left); i < right; i++) {
		array[i] = result[indexRes++];
	}
}

void mergeSort(vector<int> &array, int left, int right) {
	//left included, right excluded
	if (right - left > 1) {
		int mid = (right + left) / 2;
		mergeSort(array, left, mid);
		mergeSort(array, mid, right);
		merge(array, left, mid, right);
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> array(n);
	for (int i(0); i < n; i++) {
		cin >> array[i];
	}
	mergeSort(array, 0, n);
	for (int i(0); i < n; i++) {
		cout << array[i] << ' ';
	}

	return 0;
}