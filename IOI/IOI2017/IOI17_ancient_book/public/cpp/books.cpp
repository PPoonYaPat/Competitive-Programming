#include "books.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ans=0,cnt[1000005];

ll minimum_walk(vector<int> p, int s) {
	int n=p.size();
	for (int i=0; i<n; ++i) {
		++cnt[min(i,p[i])];
		--cnt[max(i,p[i])];
	}
	for (int i=1; i<n; ++i) cnt[i]+=cnt[i-1];

	int ss=0;
	for (int i=0; i<n-1; ++i) {
		ans+=cnt[i];
		if (cnt[i]==0) ++ss;
		else ans+=2*ss, ss=0;
	}
	return ans;
}
