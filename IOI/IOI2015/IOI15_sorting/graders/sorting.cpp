#include "sorting.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
 
int n,m,b[200005],x[200005],y[200005],p[200005];
vector<pii> ans;
int a[200005],pos[200005],val[200005],c[200005];
 
bool check(int h, bool mode) {
	for (int i=0; i<n; ++i) a[i]=i, val[i]=i, c[i]=b[i], p[i]=i;
	for (int i=h; i>=0; --i) swap(a[x[i]],a[y[i]]);
 
	vector<pii> v;
	for (int i=0; i<n; ++i) pos[c[i]]=i;
	for (int i=0; i<n; ++i) {
		if (c[i]!=a[i]) {
			v.push_back(pii(i,pos[a[i]]));
			swap(pos[a[i]],pos[c[i]]);
			swap(c[pos[c[i]]],c[i]);
		}
	}
	reverse(v.begin(),v.end());
 
	if (mode) {
		for (int i=0; i<=h; ++i) {
			swap(val[p[x[i]]],val[p[y[i]]]);
			swap(p[x[i]],p[y[i]]);
 
			if (v.size()) {
				ans.push_back(pii(val[v.back().first],val[v.back().second]));
				v.pop_back();
			} else ans.push_back(pii(0,0));
		}
	}
 
	if (v.size()<=h+1) return true;
	else return false;
}
 
int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
	n=N; m=M;
	for (int i=0; i<n; ++i) b[i]=S[i], x[i]=X[i], y[i]=Y[i];

	bool ah=true;
	for (int i=0; i<n; ++i) if (b[i]!=i) ah=false;
	if (ah) return 0;
 
	int l=0, r=m-1;
	while (l<r) {
		int mid=(l+r)/2;
		if (check(mid,0)) r=mid;
		else l=mid+1;
	}
	check(l,1);
 
	for (int i=0; i<ans.size(); ++i) P[i]=ans[i].first, Q[i]=ans[i].second;
	return ans.size();
}