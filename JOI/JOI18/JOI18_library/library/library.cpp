#include <bits/stdc++.h>
#include "library.h"
#include "grader.cpp"
using namespace std;

map<vector<int> ,int> have;

int query(vector<int> x) {
    bool check=false;
    for (int i=0; i<x.size(); ++i) if (x[i]) check=true;
    if (!check) return -1;
    else {
        if (!have[x]) have[x]=Query(x);
        return have[x];
    }
}

void Solve(int n) {
	int now=-1,pre=-1,ed;
	vector<int> test,ans;
	if (n==1) {
        ans.push_back(1);
        Answer(ans);
        return ;
	}
	for (int i=0; i<n; ++i) test.push_back(1);
	for (int i=0; i<n; ++i) {
        test[i]=0;
        if (query(test)==1) {
            if (now==-1) now=i;
            else ed=i;
        }
        test[i]=1;
	}
	ans.push_back(now+1);
	for (int i=0; i<n-1; ++i) {
        int l=0, r=n-1;
        while (l<r) {
            int mid=(l+r)/2;
            for (int i=0; i<n; ++i) {
                if (i==pre) test[i]=0;
                else if (i>=mid+1 && i<=r) test[i]=1;
                else test[i]=0;
            }
            int k1=query(test);
            test[now]=1-test[now];
            int k2=query(test);

            if (k1==k2) l=mid+1;
            else r=mid;
        }
        ans.push_back(r+1);
        pre=now; now=r;
	}
	Answer(ans);
}
