#include "reach.h"
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, q;
	assert(2 == scanf("%d %d", &n, &q));

	initialize(n);

	vector<int> ans;

	for(int i = 0; i< q; i++)
	{
		int cmd;
		assert(1 == scanf("%d", &cmd));

		if(cmd == 1)
		{
			int u, v;
			assert(2 == scanf("%d %d", &u, &v));

			add_arc(u, v);
		}
		else if(cmd == 2)
		{
			int u, v, t;
			assert(3 == scanf("%d %d %d", &u, &v, &t));

			bool result = is_reachable(u, v, t);

			if(result) ans.push_back(1);
			else ans.push_back(0);
		}
		else
		{
			fprintf(stderr, "Wrong input: command not 1 or 2\n");
			exit(1);
		}
	}
	for (auto s : ans) cout<<s<<" ";
}
