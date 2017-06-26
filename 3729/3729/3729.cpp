#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

struct pt {
	double x, y;
	pt() : x(0), y(0) {};
	pt(const double &x, const double &y) : x(x), y(y) {};
};

struct line {
	double a, b, c;
	line() : a(0), b(0), c(0) {};
	line(const pt &p1, const pt &p2) {
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = p1.x * p2.y - p2.x * p1.y;
	}
};


int n, K, L;
vector<pt> pts(100);
vector<line> lines(4950);
vector<int> v(100);

bool check(const pt &p, const line &l) {
	return l.b * p.y + l.a * p.x + l.c > 0;
}

double dist(const pt &p, const line &l) {
	return abs(l.b * p.y + l.a * p.x + l.c) / l.b;
}

void find_lines() {
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			lines[L] = line(pts[i], pts[j]);
			// check line
			for (int k = 0; k < n; ++k) {
				if (check(pts[k], lines[L])) {
					goto b;
				}
			}
			L++;
			b:
			continue;
		}
	}
}

double F(vector<int> &v, const int &x) {
	if (x == K) {
		double maxd = -1;
		for (int i = 0; i < n; ++i) {
			double mind = -1;
			for (int l = 0; l < K; ++ l) {
				double d = dist(pts[i], lines[v[l]]);
				mind = mind == -1 ? d : min(mind, d);
			}
			maxd = max(mind, maxd);
		}
		return maxd;
	}
	else {
		double mind = -1;
		int vn = x == 0 ? 0 : v[x - 1] + 1;
		for (int i = vn; i < L; i++) {
			v[x] = i;
			double maxd = F(v, x + 1);
			mind = (mind == -1 || maxd == -1) ? max(mind, maxd) : min(mind, maxd);
		}
		return mind;
	}
}

double solve() {
	return F(v, 0);
}

int main() {
	ios::sync_with_stdio(false);
	while (cin >> n >> K && n != 0) {
		L = 0;
		for (int i = 0; i < n; ++i) {
			cin >> pts[i].x >> pts[i].y;
		}
		find_lines();
		cout << setiosflags(ios::fixed) << setprecision(3) << solve() << "\n";
	}
	return 0;

}