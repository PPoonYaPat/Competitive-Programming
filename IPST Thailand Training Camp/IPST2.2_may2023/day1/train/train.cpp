#include "train.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int n,m,root,p[500001][20],lf[500001],level[500001],mark1[500001],mark2[500001],disc[500001],cnt;
vector<int> adj[500001],group[500001];
bool leaf[500001];

bool comp(int a, int b) {return disc[a]<disc[b];}

void dfs1(int x, int par) {
    disc[x]=++cnt;
    if (adj[x].size()==1) {
        lf[x]=1;
        leaf[x]=true;
    }

    level[x]=level[par]+1;
    p[x][0]=par;
    for (int i=1; i<20; ++i) p[x][i]=p[p[x][i-1]][i-1];

    for (auto s : adj[x]) {
        if (s==par) continue;
        dfs1(s,x);
        lf[x]+=lf[s];
    }
}

int lca(int x, int y) {
    int a=x, b=y;
    if (level[x]<level[y]) swap(x,y);
    int dif=level[x]-level[y];
    for (int i=0; i<20; ++i) {
        if (dif&(1<<i)) x=p[x][i];
    }
    if (x==y) return x;

    for (int i=19; i>=0; --i) {
        if (p[x][i]!=p[y][i]) {
            x=p[x][i];
            y=p[y][i];
        }
    }
    return p[x][0];
}

void dfs2(int x, int par) {
    for (auto s : adj[x]) {
        if (s==par) continue;
        dfs2(s,x);
        mark1[x]+=mark1[s];
        mark2[x]+=mark2[s];
    }
}

int want1[500001],want2[500001],mmin=INT_MAX,ans=-1;

int train(int N, int M, std::vector<int> u, std::vector<int> v, std::vector<int> A, std::vector<int> B) {
    n=N; m=M;
    for (int i=0; i<n-1; ++i) {
        adj[u[i]].push_back(v[i]);
        adj[v[i]].push_back(u[i]);
    }
    for (int i=0; i<20; ++i) p[n][i]=n;
    for (int i=0; i<n; ++i) if (adj[i].size()>1) root=i;
    dfs1(root,n);

    for (int i=0; i<m; ++i) {
        if (leaf[A[i]]) group[A[i]].push_back(B[i]);
        if (leaf[B[i]]) group[B[i]].push_back(A[i]);
    }

    for (int i=0; i<n; ++i) {
        if (!leaf[i]) continue;

        group[i].push_back(i);
        sort(group[i].begin(),group[i].end(),comp);

        int top=group[i][0];
        ++mark2[group[i][0]];
        --mark2[p[group[i][0]][0]];

        for (int j=1; j<group[i].size(); ++j) {
            int LCA=lca(group[i][j],group[i][j-1]);
            if (level[LCA]<level[top]) {

                ++mark2[p[top][0]];
                ++mark2[group[i][j]];
                --mark2[LCA];
                --mark2[p[LCA][0]];

                top=LCA;

            } else {

                ++mark2[group[i][j]];
                --mark2[LCA];

            }
        }

        --mark2[i];
        ++mark2[p[top][0]];

        ++mark1[i];
        --mark1[top];
    }

    dfs2(root,n);

    for (int i=0; i<n; ++i) {
        want1[i]=lf[i]-mark1[i];
        want2[i]=(lf[root]-lf[i])-mark2[i];
    }

    for (int i=0; i<n; ++i) {
        vector<int> temp;
        temp.push_back(want2[i]);
        for (auto s : adj[i]) if (s!=p[i][0]) temp.push_back(want1[s]);

        int sum=0;
        for (auto s : temp) sum+=s;

        int lth=0;
        for (auto s : temp) if (s>sum/2) lth=s;

        if (lth==0) mmin=min(mmin,(sum+1)/2);
        else mmin=min(mmin,lth);
    }

    return mmin;
}
