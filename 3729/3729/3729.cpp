#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, w, b;

bool check(vector<int> & box, const vector<int> & p) {
	int i;
	for (i = box.size() - p.size(); i >= 0; --i) {
		for (int j = 0; j < p.size(); ++j) {
			if (box[i + j] & p[p.size() - 1 - j]) goto finish;
		}
	}
finish:
	if (i++ == box.size() - p.size()) {
		return false;
	}
	for (int j = 0; j < p.size(); ++j) {
		box[i + j] = p[p.size() - 1 - j];
	}
	return true;
}

int height(const vector<int> box) {
	int res = 0;
	for (auto x : box) {
		if (x) res++;
	}
	return res;
}

int main() {
	while (cin >> n >> w >> b && n != 0) {
		vector<int> result;
		vector<int> box(b, 0);
		for (int i = 0; i < n; ++i) {
			int h;
			cin >> h;
			vector<int> curr(h);
			for (int j = 0; j < h; ++j) {
				for (int k = 0; k < w; ++k) {
					char c;
					cin >> c;
					if (c == 'X') curr[j] |= 1 << k;
				}
			}
			if (!check(box, curr)) {
				cout << height(box) << " ";
				fill(box.begin(), box.end(), 0);
				check(box, curr);
			}
		}
		cout << height(box) << "\n";
	}


	return 0;
}