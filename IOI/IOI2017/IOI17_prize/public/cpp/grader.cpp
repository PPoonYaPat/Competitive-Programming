#include "prize.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static const int max_q = 10000;
static int N;
static int query_count = 0;
static vector<int> g;
static vector<vector<int> > rank_count;

vector<int> ask(int i) {
	query_count++;
	if(query_count > max_q) {
		cerr << "Query limit exceeded" << endl;
		exit(0);
	}

	if(i < 0 || i >= N) {
		cerr << "Bad index: " << i << endl;
		exit(0);
	}

	vector<int> res(2);
	res[0] = rank_count[g[i] - 1][i + 1];
	res[1] = rank_count[g[i] - 1][N] - res[0];
	return res;
}

int main() {
	freopen("test.txt","r",stdin);
	cin >> N;

	g.resize(N);
	for(int i = 0; i < N; i++) {
		cin >> g[i];
		if(g[i] < 1) {
			cerr << "Invalid rank " << g[i] << " at index " << i << endl;
			exit(0);
		}
	}

	int max_rank = *max_element(g.begin(), g.end());

	rank_count.resize(max_rank + 1, vector<int>(N + 1, 0));
	for(int r = 0; r <= max_rank; r++) {
		for(int i = 1; i <= N; i++) {
			rank_count[r][i] = rank_count[r][i - 1];
			if(g[i - 1] == r)
			  rank_count[r][i]++;
		}
	}

	for(int i = 0; i <= N; i++)
		for(int r = 1; r <= max_rank; r++)
			rank_count[r][i] += rank_count[r - 1][i];

	int res = find_best(N);
	cout << res << endl << "Query count: " << query_count << endl;

	return 0;
}
