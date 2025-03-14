#include "colorful.h"
//#include "grader.cpp";
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int k;
bool notPrime[3000];
vector<int> adj[50001],prime;


int dfs(int x, int col, int dis) {
    int nxt,mmin=INT_MAX;

    if (dis==0) return x;

    for (auto s : adj[x]) {
        if (s%prime[col]<mmin) {
            mmin=s%prime[col];
            nxt=s;
        } else if (s%prime[col]==mmin && s<nxt) nxt=s;
    }

    return dfs(nxt,(col+1)%k,dis-1);
}

void init_machine(int N, int M, int K, int Q, vector<int> x, vector<int> y) {
    k=K;
    for (int i=0; i<M; ++i) {
        adj[x[i]].push_back(y[i]);
        adj[y[i]].push_back(x[i]);
    }

    for (int i=2; i<3000; ++i) {
        if (!notPrime[i]) {
            prime.push_back(i);
            if (prime.size()==K) break;
            for (int j=2; j<3000/i; ++j) notPrime[i*j]=true;
        }
    }
}

int send_ball(int c, int s, ll t){
    return dfs(s,c,t);
}
/*
4 3 2 3
4 3
1 2
2 3
1 2 3
0 1 3
1 4 2
*/
