#include<fstream>
#include<algorithm>

using namespace std;

ifstream fin("turtle.in");
ofstream fout("turtle.out");

const int MAX_H = 1005;
const int MAX_W = 1005;

int main() {
	int field[MAX_H][MAX_W];
	int h, w;
	fin >> h >> w;
	for (int i(0); i < h; i++) {
		for (int j(0); j < w; j++) {
			fin >> field[i][j];
		}
	}
	int maxReward[MAX_H][MAX_W];
	for (int i(h - 1); i >= 0; i--) {
		for (int j(0); j < w; j++) {
			if (i + 1 >= h && j - 1 < 0) {
				maxReward[i][j] = 0;
			}
			else if (i + 1 >= h) {
				maxReward[i][j] = maxReward[i][j - 1];
			}
			else if (j - 1 < 0) {
				maxReward[i][j] = maxReward[i + 1][j];
			}
			else {
				maxReward[i][j] = max(maxReward[i + 1][j], maxReward[i][j - 1]);
			}
			maxReward[i][j] += field[i][j];
		}
	}
	fout << maxReward[0][w - 1];

	return 0;
}