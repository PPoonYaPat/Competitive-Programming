#include <bits/stdc++.h>
#include "grader.cpp"
#include "meeting.h"
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

int n,level[100001],p[100001][18];
ll dis[100001];
vector<pii> adj[100001];

void dfs(int x, int par) {
    level[x]=level[par]+1;
    p[x][0]=par;
    for (int i=1; i<18; ++i) p[x][i]=p[p[x][i-1]][i-1];

    for (auto s : adj[x]) {
        if (s.first==par) continue;
        dis[s.first]=dis[x]+s.second;
        dfs(s.first,x);
    }
}

int lca(int x, int y) {
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];
    for (int i=0; i<18; ++i) {
        if (dif&(1<<i)) x=p[x][i];
    }

    if (x==y) return x;

    for (int i=17; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            x=p[x][i];
            y=p[y][i];
        }
    }
    return p[x][0];
}

vector<int> ans;

bool check(ll disA, ll disB, ll disC, ll x) {
    int cnt=0;
    if (disA>x) ++cnt;
    if (disB>x) ++cnt;
    if (disC>x) ++cnt;
    if (cnt>1) return false;
    else return true;
}

bool solve(ll x, int k1, int k2, int a, int b, int c) {
    ll disA=dis[a]+dis[k1]-2*dis[k2];
    ll disB=dis[b]-dis[k1];
    ll disC=dis[c]-dis[k1];

    if (!check(disA,disB,disC,x)) return false;
    if (disA<=x && disB<=x && disC<=x) return true;

    if (disB>x || disC>x) {
        if (disB>x) swap(b,c), swap(disB,disC);
        ll D=dis[c];

        for (int i=17; i>=0; --i) {
            if (D-dis[p[c][i]]<=x) c=p[c][i];
        }

        if (disA+dis[c]-dis[k1]<=x && disB+dis[c]-dis[k1]<=x) return true;
        else return false;

    } else {

        if (dis[a]-dis[k2]<x) {

            ll D=dis[k1];
            int h=k1;

            for (int i=17; i>=0; --i) {
                if (dis[b]-dis[p[h][i]]<=x && dis[c]-dis[p[h][i]]<=x) h=p[h][i];
            }

            if (dis[a]+dis[h]-2*dis[k2]<=x) return true;
            else return false;


        } else {
            ll D=dis[a];

            for (int i=17; i>=0; --i) {
                if (D-dis[p[a][i]]<=x) a=p[a][i];
            }
            //cout<<disC<<" "<<dis[a]<<" "<<dis[k1]<<"\n";

            if (disB+dis[a]+dis[k1]-2*dis[k2]<=x && disC+dis[a]+dis[k1]-2*dis[k2]<=x) return true;
            else return false;

        }

    }
}



vector<int> best_meeting(int N, int Q, vector<vector<int>>& roads, vector<int>& lengths, vector<int>& A, vector<int>& B, vector<int>& C) {
    n=N;
    for (int i=0; i<n-1; ++i) {
        adj[roads[i][0]].push_back(pii(roads[i][1],lengths[i]));
        adj[roads[i][1]].push_back(pii(roads[i][0],lengths[i]));
    }

    dfs(0,0);

    //cout<<solve(12,13,0,9,10,14)<<"\n";

    for (int i=0; i<Q; ++i) {
        int a=A[i], b=B[i], c=C[i];
        int k1=lca(a,b),k2=lca(b,c),k3=lca(a,c);

        if (level[k1]>=level[k2] && level[k1]>=level[k3]) swap(a,c);
        else if (level[k3]>=level[k2] && level[k3]>=level[k1]) swap(a,b), swap(k3,k1);
        else swap(k2,k1);

        //cout<<a<<" "<<b<<" "<<c<<" "<<k1<<" "<<k2<<"\n";

        ll l=0,r=2000000000;
        while (l<r) {
            ll mid=(l+r)/2;
            if (solve(mid,k1,k2,a,b,c)) r=mid;
            else l=mid+1;
        }
        ans.push_back(l);
    }
    return ans;
}
/*
15 10
0 1 1
1 2 2
3 2 3
2 4 2
7 6 5
4 6 4
4 5 6
5 8 4
5 9 3
0 11 2
11 12 6
11 13 2
13 14 8
13 10 3
10 9 14
14 1 12
6 5 5
13 0 12
9 4 10
6 3 7
0 1 8
12 5 14
10 1 11
2 2 2
*/
