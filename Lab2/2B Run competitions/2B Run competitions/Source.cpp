#include<fstream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

ifstream fin("race.in");
ofstream fout("race.out");

struct Sportsman {
	string country;
	string name;
	int id;

	Sportsman(string _country, string _name, int _id) {
		country = _country;
		name = _name;
		id = _id;
	}

	Sportsman() {}

	bool operator<(Sportsman other) {
		if (country == other.country) {
			return id < other.id;
		}
		return country < other.country;
	}

	bool operator>(Sportsman other) {
		if (country == other.country) {
			return id > other.id;
		}
		return country > other.country;
	}

	bool operator<=(Sportsman other) {
		return !(*this > other);
	}

	bool operator>=(Sportsman other) {
		return !(*this < other);
	}
};



void qsort(vector<Sportsman>& array, int left, int right) {
	int l = left;
	int r = right;
	Sportsman x = array[(left + right) / 2];
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
	vector<Sportsman> sportsmans(n);
	for (int i(0); i < n; i++) {
		string country, name;
		fin >> country >> name;
		Sportsman sportsman(country, name, i + 1);
		sportsmans[i] = sportsman;
	}
	qsort(sportsmans, 0, n - 1);
	string countryNow = "";
	for (int i(0); i < n; i++) {
		if (countryNow != sportsmans[i].country) {
			fout << "=== " << sportsmans[i].country << " ===\n";
			countryNow = sportsmans[i].country;
		}
		fout << sportsmans[i].name << '\n';
	}

	return 0;
}