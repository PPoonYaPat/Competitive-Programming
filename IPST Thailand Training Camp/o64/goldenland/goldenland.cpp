#include <bits/stdc++.h>
#include "grader.cpp";
using namespace std;
typedef long long ll;

int n,m;
vector<int> prime,group_x[1000001],group_y[1000001];
int pos_x[60001],pos_y[60001];
bool notPrime[1001];

void init_land(int N, int M, int P, vector<int> A,  vector<int> B){
    n=N; m=M;
    for (int i=2; i<=1000; ++i) {
        if (!notPrime[i]) {
            prime.push_back(i);
            for (int j=2; j<=1000/i; ++j) notPrime[i*j]=true;
        }
    }

    for (int i=0; i<n; ++i) {
        for (int j=0; j<prime.size(); ++j) {
            while (A[i]%(prime[j]*prime[j])==0) A[i]/=(prime[j]*prime[j]);
        }
        pos_x[i]=A[i];
        group_x[A[i]].push_back(i);
    }

    for (int i=0; i<m; ++i) {
        for (int j=0; j<prime.size(); ++j) {
            while (B[i]%(prime[j]*prime[j])==0) B[i]/=(prime[j]*prime[j]);
        }
        pos_y[i]=B[i];
        group_y[B[i]].push_back(i);
    }
}

long long answer_query(int r1, int c1, int r2, int c2){
    ll ans=0;
	if (r2-r1>=c2-c1) {
        for (int i=c1; i<=c2; ++i) {
            ans+=(upper_bound(group_x[pos_y[i]].begin(),group_x[pos_y[i]].end(),r2)
                  -upper_bound(group_x[pos_y[i]].begin(),group_x[pos_y[i]].end(),r1-1));
        }
	} else {
        for (int i=r1; i<=r2; ++i) {
            ans+=(upper_bound(group_y[pos_x[i]].begin(),group_y[pos_x[i]].end(),c2)
                  -upper_bound(group_y[pos_x[i]].begin(),group_y[pos_x[i]].end(),c1-1));
        }
	}
	return ans;
}
/*
8 8 10
5 4 1 2 8 9 3 7
2 1 4 3 8 6 5 2
0 1 1 3
0 4 3 4
0 7 0 7
1 6 1 7
2 6 4 7
6 6 7 7
7 0 7 4
4 2 5 4
4 0 5 0
2 0 3 2
*/
