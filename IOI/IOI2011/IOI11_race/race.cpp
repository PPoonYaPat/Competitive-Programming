#include "race.h"
#include "grader.cpp"

#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int ans=INT_MAX,sz[200001],k;
int dis[1000001]; //dis[x] : the least highway count that have distance of x
int now[1000001];
vector<pii> adj[200001];
vector<int> temp,temp2;
bool mark[200001];

int find_sz(int x, int par) {
    sz[x]=1;
    for (auto s : adj[x]) {
        if (s.first==par || mark[s.first]) continue;
        sz[x]+=find_sz(s.first,x);
    }
    return sz[x];
}

int cen(int x, int par, int n) {
    for (auto s : adj[x]) {
        if (s.first!=par && !mark[s.first] && sz[s.first]>n/2) return cen(s.first,x,n);
    }
    return x;
}

void dfs(int x, int par, int d, int cnt) { // d=distance
    for (auto s : adj[x]) {
        if (mark[s.first] || s.first==par) continue;

        if (d+s.second<k) {
            now[d+s.second]=min({dis[d+s.second],cnt+1,now[d+s.second]});

            temp2.push_back(d+s.second); //change now
            temp.push_back(d+s.second); //change dis

            if (dis[k-d-s.second]!=INT_MAX) ans=min(ans,cnt+1+dis[k-d-s.second]);

            dfs(s.first,x,d+s.second,cnt+1);
        } else if (d+s.second==k) ans=min(ans,cnt+1);
    }
}

void sol(int x) {
    int centroid=cen(x,x,find_sz(x,x));
    mark[centroid]=true;

    for (auto s : adj[centroid]) {
        if (mark[s.first]) continue;

        if (s.second<k) {
            now[s.second]=1;

            temp2.push_back(s.second); //change now
            temp.push_back(s.second); //change dis

            if (dis[k-s.second]!=INT_MAX) ans=min(ans,1+dis[k-s.second]);

            dfs(s.first,x,s.second,1);
        } else if (s.second==k) ans=1;

        for (auto s : temp2) dis[s]=now[s];
        temp2.clear();
    }

    for (auto s : temp) dis[s]=INT_MAX,now[s]=INT_MAX;
    temp.clear();

    for (auto s : adj[centroid]) if (!mark[s.first]) sol(s.first);
}

int best_path(int n, int K, int H[][2], int L[]) {
    k=K;
    for (int i=1; i<=K; ++i) dis[i]=INT_MAX,now[i]=INT_MAX;
    for (int i=0; i<n-1; ++i) {
        adj[H[i][0]].push_back(pii(H[i][1],L[i]));
        adj[H[i][1]].push_back(pii(H[i][0],L[i]));
    }
    sol(1);
    if (ans==INT_MAX) return -1;
    return ans;
}
/*
4 0
0 1 1
1 2 2
1 3 4
2

3 3
0 1 1
1 2 1
-1

11 12
0 1 3
0 2 4
2 3 5
3 4 4
4 5 6
0 6 3
6 7 2
6 8 5
8 9 6
8 10 7
2
*/

