#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

ifstream fin("sortland.in");
ofstream fout("sortland.out");

struct Person {
	int id;
	double money;
};

int main() {
	int n;
	fin >> n;
	vector<Person> persons(n);
	for (int i(0); i < n; i++) {
		double money;
		fin >> money;
		persons[i].id = i + 1;
		persons[i].money = money;
	}
	for (int i(0); i < n; i++) {
		for (int j(0); j < n - 1; j++) {
			if (persons[j].money > persons[j + 1].money) {
				swap(persons[j], persons[j + 1]);
			}
		}
	}
	fout << persons[0].id << ' ';
	fout << persons[n / 2].id << ' ';
	fout << persons[n - 1].id << ' ';

	return 0;
}