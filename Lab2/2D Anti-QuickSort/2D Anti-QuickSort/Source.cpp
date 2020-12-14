#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

ifstream fin("antiqs.in");
ofstream fout("antiqs.out");

/*void antiQuickSort(vector<int>& ans, int left, int right) {
	static int cnt = right - left + 1;
	if (right < left) {
		return;
	}
	int mid = (left + right) / 2;
	ans[mid] = cnt--;
	antiQuickSort(ans, mid + 1, right);
	antiQuickSort(ans, left, mid - 1);
}*/

void antiQuickSort(vector<int>& ans) {
	for (int i(0); i < ans.size(); i++) {
		ans[i] = i + 1;
	}
	for (int i(0); i < ans.size(); i++) {
		swap(ans[i], ans[i / 2]);
	}
}

int main() {
	int n;
	fin >> n;
	vector<int> ans(n);
	antiQuickSort(ans);
	for (int i(0); i < n; i++) {
		fout << ans[i] << ' ';
	}

	return 0;
}