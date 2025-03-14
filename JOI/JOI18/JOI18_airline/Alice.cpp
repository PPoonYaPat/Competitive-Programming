#include "Alicelib.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

void Alice( int n, int m, int A[], int B[] ){
	vector<pii> v;
	for (int i=0; i<=n+11; ++i) if (i!=n && i!=n+1) v.push_back({n,i});
	for (int i=0; i<n; ++i) v.push_back({n+1,i});
	for (int i=n+3; i<=n+11; ++i) v.push_back({i,i-1});
	for (int i=0; i<n; ++i) {
		for (int j=0; j<10; ++j) {
			if (i&(1<<j)) v.push_back({i,n+2+j});
		}
	}
	for (int i=0; i<m; ++i) v.push_back({A[i],B[i]});
	InitG(n+12,v.size());
	for (int i=0; i<v.size(); ++i) MakeG(i,v[i].first,v[i].second);
}

