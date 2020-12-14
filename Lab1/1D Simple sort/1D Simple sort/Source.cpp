#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

ifstream fin("smallsort.in");
ofstream fout("smallsort.out");

int main() {
	int n;
	fin >> n;
	vector<int> numbs(n);
	for (int i(0); i < n; i++) {
		fin >> numbs[i];
	}
	for (int i(0); i < n; i++) {
		for (int j(0); j < n - 1; j++) {
			if (numbs[j] > numbs[j + 1]) {
				swap(numbs[j], numbs[j + 1]);
			}
		}
	}
	for (int i(0); i < n; i++) {
		fout << numbs[i] << ' ';
	}

	return 0;
}