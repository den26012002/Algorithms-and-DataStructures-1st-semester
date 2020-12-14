#include<fstream>
#include<vector>

using namespace std;

ifstream fin("inversions.in");
ofstream fout("inversions.out");

long long merge(vector<int> &array, int left, int mid, int right) {
	long long res = 0;
	int index1 = left;
	int index2 = mid;
	int indexRes = 0;
	vector<int> result(right - left);
	while (index1 < mid || index2 < right) {
		if (index1 == mid) {
			result[indexRes++] = array[index2++];
		}
		else if (index2 == right) {
			result[indexRes++] = array[index1++];
		}
		else if (array[index1] <= array[index2]) {
			result[indexRes++] = array[index1++];
		}
		else {
			result[indexRes++] = array[index2++];
			res += (mid - index1);
		}
	}
	for (int i(left); i < right; i++) {
		array[i] = result[i - left];
	}
	return res;
}

long long mergeSort(vector<int>& array, int left, int right) {
	static long long cnt = 0;
	if (right - left > 1) {
		int mid = (right + left) / 2;
		mergeSort(array, left, mid);
		mergeSort(array, mid, right);
		cnt += merge(array, left, mid, right);
	}
	return cnt;
}

int main() {
	int n;
	fin >> n;
	vector<int> arr(n);
	for (int i(0); i < n; i++) {
		fin >> arr[i];
	}
	fout << mergeSort(arr, 0, n);
	

	return 0;
}