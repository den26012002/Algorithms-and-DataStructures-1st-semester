#include<fstream>
#include<vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

void print(vector<int>& array) {
	for (int i(0); i < array.size(); i++) {
		fout << array[i] << ' ';
	}
	fout << endl;
}

void qsort(vector<int>& array, int left, int right) {
	int l = left;
	int r = right;
	int x = array[(left + right) / 2];
	while (l < r) {
		while (array[l] < x) {
			l++;
		}
		while (array[r] > x) {
			r--;
		}
		if (r >= l) {
			swap(array[l], array[r]);
			l++;
			r--;
		}
	}
	print(array);
	if (left < r) {
		qsort(array, left, r);
	}
	if (l < right) {
		qsort(array, l, right);
	}
}

int main() {
	int n;
	fin >> n;
	vector<int> arr(n);
	for (int i(0); i < n; i++) {
		fin >> arr[i];
	}
	qsort(arr, 0, n - 1);

	return 0;
}