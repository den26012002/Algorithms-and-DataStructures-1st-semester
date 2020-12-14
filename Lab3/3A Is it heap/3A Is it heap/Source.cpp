#include<fstream>
#include<vector>

using namespace std;

ifstream fin("isheap.in");
ofstream fout("isheap.out");

int main() {
	int n;
	fin >> n;
	vector<int> arr(n);
	for (int i(0); i < n; i++) {
		fin >> arr[i];
	}
	bool isHeap = true;
	for (int i(0); i < n; i++) {
		if (2 * i + 1 < n) {
			if (arr[i] > arr[2 * i + 1]) {
				isHeap = false;
				break;
			}
		}
		else if (2 * i + 2 < n) {
			if (arr[i] > arr[2 * i + 2]) {
				isHeap = false;
				break;
			}
		}
		else {
			break;
		}
	}
	fout << (isHeap ? "YES" : "NO");

	return 0;
}