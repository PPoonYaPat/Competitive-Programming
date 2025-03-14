#include "simurgh.h"
#include <bits/stdc++.h>
using namespace std;
#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

static int MAXQ = 30000;

static int N, M, q = 0;
static vector<int> u, v;
static vector<bool> goal;

static void wrong_answer() {
	printf("NO\n");
	exit(0);
}

static bool is_valid(const vector<int>& r) {
	if(int(r.size()) != N - 1)
		return false;

	for(int i = 0; i < N - 1; i++)
		if (r[i] < 0 || r[i] >= M)
			return false;

	return true;
}

static int _count_common_roads_internal(const vector<int>& r) {
	if(!is_valid(r))
		wrong_answer();

	int common = 0;
	for(int i = 0; i < N - 1; i++) {
		bool is_common = goal[r[i]];
		if (is_common)
			common++;
	}

	return common;	
}

int count_common_roads(const vector<int>& r) {
	q++;
	if(q > MAXQ)
		wrong_answer();

	return _count_common_roads_internal(r);
}

int main() {
	freopen("test.txt","r",stdin);
	assert(2 == scanf("%d %d", &N, &M));

	u.resize(M);
	v.resize(M);

	for(int i = 0; i < M; i++)
		assert(2 == scanf("%d %d", &u[i], &v[i]));

	goal.resize(M, false);

	for(int i = 0; i < N - 1; i++) {
		int id;
		assert(1 == scanf("%d", &id));
		goal[id] = true;
	}

	vector<int> res = find_roads(N, u, v);

	if(_count_common_roads_internal(res) != N - 1)
		wrong_answer();

	printf("YES\n");

	return 0;
}

