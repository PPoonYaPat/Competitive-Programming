#include "prize.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int mmax=0,st,n,non_lol;
vector<int> val[200005];
vector<int> none;

void find_nxt() { //find the next non-lollipop
	int l=st+1,r=n-1;
	if (none.size()==non_lol) return;
	while (l<r) {
		int mid=(l+r)/2;
		val[mid]=ask(mid);
		if (val[mid][0]+val[mid][1]!=mmax) r=mid;
		else if (val[mid][0]!=val[st][0]) r=mid;
		else l=mid+1;
	}
	none.push_back(l);

	for (int i=l+1; i<n; ++i) {
		val[i]=ask(i);
		if (val[i][0]+val[i][1]!=mmax) none.push_back(i);
		else {
			st=i;
			find_nxt();
			break;
		}
	}
}

int find_best(int N) {
	n=N;
	for (int i=0; i<min(500,n); ++i) {
		val[i]=ask(i);
		mmax=max(mmax,val[i][0]+val[i][1]);
	}

	non_lol=n-mmax-1;
	for (int i=0; i<min(500,n); ++i) {
		if (val[i][0]+val[i][1]==mmax) {
			st=i;
			find_nxt();
			break;
		} else none.push_back(i);
	}

	for (auto s : none) {
		val[s]=ask(s);
		if (val[s][0]+val[s][1]==0) return s;
	}
}
