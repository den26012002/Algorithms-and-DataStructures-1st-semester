#include<fstream>
#include<vector>

std::ifstream fin("binsearch.in");
std::ofstream fout("binsearch.out");

class binSearchArray {
public:
	std::pair<int, int> binSearch(int x) {
		int lowAns = lowerBound(x);
		int upAns = upperBound(x);
		std::pair<int, int> ans = { lowAns, upAns };
		if (!correctLeft(lowAns)) {
			makeSearchNoAnswer(ans);
		}
		else if (!correctRight(upAns)) {
			makeSearchNoAnswer(ans);
		}
		else if (arr[lowAns] != x) {
			makeSearchNoAnswer(ans);
		}
		return ans;
	}

	void updateArray(std::vector<int>& _arr) {
		arr = _arr;
		size = _arr.size();
	}

	binSearchArray(std::vector<int>& _arr) {
		arr = _arr;
		size = _arr.size();
	}

	binSearchArray() {
		size = 0;
	}
private:
	std::vector<int> arr;
	int size;

	int lowerBound(int x) {
		int l = -1;
		int r = size;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (arr[mid] < x) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		return r;
	}

	int upperBound(int x) {
		int l = -1;
		int r = size;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (arr[mid] <= x) {
				l = mid;
			}
			else {
				r = mid;
			}
		}
		return r;
	}

	bool correctLeft(int index) {
		return (index < size);
	}

	bool correctRight(int index) {
		return (index > 0);
	}

	void makeSearchNoAnswer(std::pair<int, int>& couple) {
		couple.first = -2;
		couple.second = -1;
	}
};

int main() {
	int n;
	fin >> n;
	std::vector<int> arr(n);
	for (int i(0); i < arr.size(); i++) {
		fin >> arr[i];
	}
	binSearchArray searchArr(arr);
	int m;
	fin >> m;
	for (int i(0); i < m; i++) {
		int x;
		fin >> x;
		std::pair<int, int> ans = searchArr.binSearch(x);
		fout << ans.first + 1 << ' ' << ans.second << '\n';
	}

	return 0;
}