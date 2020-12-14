#include<fstream>
#include<vector>

#define double long double

std::ifstream fin("garland.in");
std::ofstream fout("garland.out");

struct Garland {
public:
	double getAnswer() {
		double ans = first;
		double l = 0;
		double r = first;
		while (r - l > eps) {
			double mid = (r + l) / 2;
			double _correct = correct(mid);
			if (_correct) {
				r = mid;
				ans = _correct;
			}
			else {
				l = mid;
			}
		}
		return ans;
	}

	Garland(double _first, int _size, double _eps = 0.00001) {
		garland.resize(_size);
		size = _size;
		first = _first;
		garland[0] = _first;
		eps = _eps;
	}

	Garland() {}
private:
	std::vector<double> garland;
	int size;
	double first;
	double eps;

	double correct(double second) {
		garland[1] = second;
		for (int i(2); i < size; i++) {
			garland[i] = 2 * garland[i - 1] - garland[i - 2] + 2;
			if (garland[i] < 0) {
				return 0;
			}
		}
		return garland[size - 1];
	}
};

double myRound(double x) {
	return (double)((long long)(x * 100ll)) / 100;
}

int main() {
	int n;
	double a;
	fin >> n >> a;
	Garland garland(a, n);
	fout.precision(2);
	fout << std::fixed << myRound(garland.getAnswer());


	return 0;
}