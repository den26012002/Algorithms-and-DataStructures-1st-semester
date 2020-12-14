#include<iostream>
#include<fstream>
#include<vector>

//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

using namespace std;

ifstream fin("kth.in");
ofstream fout("kth.out");

/*int partition(vector<int>& arr, int left, int right) {
	int l = left;
	int r = right;
	int pivotPos = rand() % (right - left + 1) + left;
	int x = arr[pivotPos];
	while (l <= r) {
		while (l <= right && arr[l] <= x) {
			l++;
		}
		while (left <= r && arr[r] >= x) {
			r--;
		}
		if (l <= r) {
			/*if (pivotPos == l) {
				pivotPos = r;
			}
			if (pivotPos == r) {
				pivotPos = l;
			}//
			swap(arr[l], arr[r]);
			l++;
			r--;
		}
	}
	//swap(arr[r], arr[pivotPos]);
	return r;
}*/

/*pair<int, int> partition(vector<int>& arr, int left, int right) {
	int l = left;
	int r = right;
	int x = arr[rand() % (right - left + 1) + left];
	while (l < r) {
		while (l < right && arr[l] < x) {
			l++;
			if (l == r) break;
		}
		while (left < r && arr[r] > x) {
			r--;
			if (l == r) break;
		}
		if (l <= r) {
			swap(arr[l], arr[r]);
			if (l == r) {
				while (l + 1 <= right && arr[l + 1] == arr[l]) l++;
				while (r - 1 >= left && arr[r - 1] == arr[r]) r--;
				break;
			}
		}
	}
	return make_pair(r, l);
}

int kqsort(vector<int>& arr, int left, int right, int k) {
	int l = left;
	int r = right;
	while (true) {
		pair<int, int> mid = partition(arr, l, r);
		if (mid.first <= k && mid.second >= k) {
			return arr[mid.first];
		}
		if (mid.first > k) {
			r = mid.first - 1;
		}
		else {
			l = mid.second + 1;
		}
	}
}*/

void kqsort(vector<int>& arr, int left, int right, int k) {
	if (left > k || right < k) {
		return;
	}
	int l = left;
	int r = right;
	int x = arr[rand() % (right - left + 1) + left];
	while (l <= r) {
		while (arr[l] < x) {
			l++;
		}
		while (arr[r] > x) {
			r--;
		}
		if (l <= r) {
			swap(arr[l], arr[r]);
			l++;
			r--;
		}
	}
	if (r >= left) {
		kqsort(arr, left, r, k);
	}
	if (l <= right) {
		kqsort(arr, l, right, k);
	}
}

int main() {
	int n, k;
	fin >> n >> k;
	vector<int> arr(n);
	int a, b, c;
	fin >> a >> b >> c >> arr[0] >> arr[1];
	for (int i(2); i < n; i++) {
		arr[i] = a * arr[i - 2] + b * arr[i - 1] + c;
	}
	kqsort(arr, 0, n - 1, k - 1);
	fout << arr[k - 1];

	return 0;
}