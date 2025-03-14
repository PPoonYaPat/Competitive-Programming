#include "company.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,m,par[100001],p[100001][18],mmin[100001][18],r[100001],level[100001];
vector<pii> adj[100001];

int find(int x) {
    while (x!=par[x]) x=par[x];
    return par[x];
}

void unite(int A, int B, int val) {
    int a=find(A), b=find(B);

    if (a!=b) {
        if (r[a]>r[b]) swap(a,b);
        par[a]=b;
        if (r[a]==r[b]) ++r[b];

        adj[A].push_back(pii(B,val));
        adj[B].push_back(pii(A,val));
    }
}

void dfs(int x, int Par) {
    level[x]=level[Par]+1;

    for (int i=1; i<18; ++i) {
        mmin[x][i]=min(mmin[x][i-1],mmin[p[x][i-1]][i-1]);
        p[x][i]=p[p[x][i-1]][i-1];
    }

    for (auto s : adj[x]) {
        if (s.first==Par) continue;

        mmin[s.first][0]=s.second;
        p[s.first][0]=x;

        dfs(s.first,x);
    }
}

pii lca(int x, int y) { //return (LCA,min edge)
    int mi=INT_MAX;

    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];

    for (int i=0; i<18; ++i) {
        if (dif&(1<<i)) {
            mi=min(mi,mmin[x][i]);
            x=p[x][i];
        }
    }

    if (x==y) return pii(x,mi);

    for (int i=17; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            mi=min({mi,mmin[x][i],mmin[y][i]});
            x=p[x][i];
            y=p[y][i];
        }
    }

    mi=min({mi,mmin[x][0],mmin[y][0]});
    return pii(p[x][0],mi);
}

vector<int> group[100001];
int mmin_of_group[100001], top_of_group[100001];

void init(int N, int M, vector<int> C, vector<vector<int>> Road) {
    n=N; m=M;
    for (int i=0; i<n; ++i) par[i]=i;
    for (int i=m-1; i>=0; --i) unite(Road[i][0],Road[i][1],i);
    dfs(0,0);

    for (int i=0; i<n; ++i) group[C[i]].push_back(i);

    for (int i=0; i<n; ++i) {
        if (group[i].size()==0) continue;
        if (group[i].size()==1) {
            top_of_group[i]=group[i][0];
            mmin_of_group[i]=m;

        } else {
            pii h=lca(group[i][0],group[i][1]);
            top_of_group[i]=h.first;
            mmin_of_group[i]=h.second;

            for (int j=2; j<group[i].size(); ++j) {
                h=lca(top_of_group[i],group[i][j]);
                top_of_group[i]=h.first;
                mmin_of_group[i]=min(mmin_of_group[i],h.second);
            }
        }
    }
}

vector<int> dissolve(vector<vector<int>> Group) {
    vector<int> ans;

    int cnt=0;

    for (int u=0; u<Group.size(); ++u) {
        int mi=INT_MAX;

        if (Group[u].size()==1) ans.push_back(mmin_of_group[Group[u][0]]);
        else {

            vector<int> temp;
            for (auto s : Group[u]) {
                mi=min(mi,mmin_of_group[s]);
                temp.push_back(top_of_group[s]);
            }

            pii h=lca(temp[0],temp[1]);
            int top=h.first;
            mi=min(mi,h.second);

            for (int i=2; i<temp.size(); ++i) {
                h=lca(top,temp[i]);
                top=h.first;
                mi=min(mi,h.second);
            }

            ans.push_back(mi);

        }
    }

    return ans;
}
/*
8 8 7
5 1 2 2 1 3 3 4
1 2
1 5
7 4
5 7
2 3
7 6
4 5
0 1
1 1
1 2
1 3
1 4
2 1 4
3 1 3 4
4 1 2 3 4
*/
