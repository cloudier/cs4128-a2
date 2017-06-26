#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <functional>
#include <iostream>

using namespace std;

const int MAXN = 11;

vector<vector<int> > g(MAXN, vector<int>(MAXN));
vector<bool> visited(MAXN * 2048);

int N;

void floyd() {
	for (int i = 0; i < N + 1; i++)
		for (int u = 0; u < N + 1; u++)
			for (int v = 0; v < N + 1; v++)
				g[u][v] = min(g[u][v], g[u][i] + g[i][v]);
}

long long solve() {
	priority_queue < pair<long long, pair<int, int> >, vector <pair<long long, pair<int, int> > >, greater < pair<long long, pair<int, int > > > >  pq;
	for (pq.push(make_pair(0, make_pair(0, 0))); !pq.empty(); pq.pop()) {
		long long d = pq.top().first;
		int u = pq.top().second.first;
		int vm = pq.top().second.second;
		if (vm == (1 << N + 1) - 1 && u == 0) return d;
		if (visited[u * 2048 + vm]) continue;
		visited[u * 2048 +vm] = true;
		for (int i = 0; i <= N; ++i) {
			if (i == u || (1 << i) & vm) continue;
			pq.push(make_pair(d + g[u][i], make_pair( i, vm | (1 << i) )));
		}
	}
	return -1;
}

int main() {
	while (scanf("%d", &N) && N) {
		for (int i = 0; i < N + 1; ++i) {
			for (int j = 0; j < N + 1; ++j) {
				scanf("%d", &g[i][j]);
			}
		}
		fill(visited.begin(), visited.end(), false);
		floyd();
		printf("%lld\n", solve());
	}
	return 0;
}