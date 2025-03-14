#include "prize.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
 
int mmax=0,n;
vector<int> val[200005],none;
 
void Ask(int x) {
    if (!val[x].size()) val[x]=ask(x);
}

void solve(int l, int r) { //l and r must be lolli_pop
    Ask(l);
    Ask(r);
    if (val[r][0]==val[l][0]) return;
    if (val[r][0]-val[l][0]==r-l-1) {
        for (int i=l+1; i<r; ++i) none.push_back(i);
    } else {
        int mid=(l+r)/2;
        Ask(mid);
 
        if (val[mid][0]+val[mid][1]!=mmax) {
            none.push_back(mid);
            
            for (int i=mid-1; i>l; --i) {
                Ask(i);
                if (val[i][0]+val[i][1]!=mmax) none.push_back(i);
                else {
                    solve(l,i);
                    break;
                }
            }
 
            for (int i=mid+1; i<r; ++i) {
                Ask(i);
                if (val[i][0]+val[i][1]!=mmax) none.push_back(i);
                else {
                    solve(i,r);
                    break;
                }
            }
 
        } else {
            solve(l,mid);
            solve(mid,r);
        }
    }
 
}

int find_best(int N) {
	n=N;
	for (int i=0; i<min(475,n); ++i) {
		Ask(i);
		mmax=max(mmax,val[i][0]+val[i][1]);
	}
    int st,ed;
    for (int i=0; i<n; ++i) {
        Ask(i);
        if (val[i][0]+val[i][1]!=mmax) none.push_back(i);
        else {
            st=i;
            break;
        }
    }
 
    for (int i=n-1; i>=0; --i) {
        Ask(i);
        if (val[i][0]+val[i][1]!=mmax) none.push_back(i);
        else {
            ed=i;
            break;
        }
    }
 
    solve(st,ed);
 
	for (auto s : none) {
		Ask(s);
		if (val[s][0]+val[s][1]==0) return s;
	}
}