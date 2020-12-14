#include<fstream>
#include<vector>
#include<string>

using namespace std;

ifstream fin("radixsort.in");
ofstream fout("radixsort.out");

const int MAX_N = 256;

void print(vector<string> arr) {
	for (int i(0); i < arr.size(); i++) {
		fout << arr[i] << '\n';
	}
}

void countingSort(vector<string>& arr, int phase) {
	phase = arr[0].size() - phase;
	vector<int> cnt(MAX_N);
	for (int i(0); i < MAX_N; i++) {
		cnt[i] = 0;
	}
	for (int i(0); i < arr.size(); i++) {
		cnt[arr[i][phase] - 'a']++;
	}
	for (int i(1); i < MAX_N; i++) {
		cnt[i] += cnt[i - 1];
	}
	vector<string> result(arr.size());
	for (int i(arr.size() - 1); i >= 0; i--) {
		result[--cnt[arr[i][phase] - 'a']] = arr[i];
	}
	arr = result;
}

void radixSort(vector<string>& arr, int phase) {
	for (int i(1); i <= phase; i++) {
		countingSort(arr, i);
	}
}

int main() {
	int n, m, k;
	fin >> n >> m >> k;
	vector<string> arr(n);
	for (int i(0); i < n; i++) {
		fin >> arr[i];
	}
	radixSort(arr, k);
	print(arr);

	return 0;
}