#include <bits/stdc++.h>
#include <utility>
//#include "grader.cpp"
using namespace std;
typedef tuple<int,int,int> tu;

int n,city,dis[100001],group[100001];
vector<int> adj[100001];
bool vis[100001];

void bfs(int start, int x) {
    queue<int> q;
    dis[start]=0;
    q.push(start);

    while (!q.empty()) {
        int node=q.front();
        q.pop();

        if (vis[node]) continue;
        vis[node]=true;
        group[node]=x;

        for (auto s : adj[node]) {
            if (s<=city) continue;
            if (dis[s]>dis[node]+1) {
                dis[s]=dis[node]+1;
                q.push(s);
            }
        }
    }
}

int s[1<<18][11],sl[1<<18][11],sr[1<<18][11];
multiset<int, greater<int>> m[100001][11],ml[100001][11],mr[100001][11];

void update(int l, int r, int idx, int x, int val, int level) {
    if (x<l || x>r) return;
    if (l==r) {
        s[idx][level]=val;
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val,level);
        update(mid+1,r,2*idx+1,x,val,level);
        s[idx][level]=max(s[2*idx][level],s[2*idx+1][level]);
    }
}

void updatel(int l, int r, int idx, int x, int val, int level) {
    if (x<l || x>r) return;
    if (l==r) {
        sl[idx][level]=val;
    } else {
        int mid=(l+r)/2;
        updatel(l,mid,2*idx,x,val,level);
        updatel(mid+1,r,2*idx+1,x,val,level);
        sl[idx][level]=max(sl[2*idx][level],sl[2*idx+1][level]);
    }
}

void updater(int l, int r, int idx, int x, int val, int level) {
    if (x<l || x>r) return;
    if (l==r) {
        sr[idx][level]=val;
    } else {
        int mid=(l+r)/2;
        updater(l,mid,2*idx,x,val,level);
        updater(mid+1,r,2*idx+1,x,val,level);
        sr[idx][level]=max(sr[2*idx][level],sr[2*idx+1][level]);
    }
}

int query(int l, int r, int idx, int x, int y, int level) {
    if (x>r || y<l) return -INT_MAX;
    if (x<=l && r<=y) return s[idx][level];

    int mid=(l+r)/2;
    return max(query(l,mid,2*idx,x,y,level),query(mid+1,r,2*idx+1,x,y,level));
}

int queryl(int l, int r, int idx, int x, int y, int level) {
    if (x>r || y<l) return -INT_MAX;
    if (x<=l && r<=y) return sl[idx][level];

    int mid=(l+r)/2;
    return max(queryl(l,mid,2*idx,x,y,level),queryl(mid+1,r,2*idx+1,x,y,level));
}

int queryr(int l, int r, int idx, int x, int y, int level) {
    if (x>r || y<l) return -INT_MAX;
    if (x<=l && r<=y) return sr[idx][level];

    int mid=(l+r)/2;
    return max(queryr(l,mid,2*idx,x,y,level),queryr(mid+1,r,2*idx+1,x,y,level));
}

void initialize(int N, int M, int S, vector<vector<int>>R) {
    n=N, city=S;
    memset(dis,0x3f,sizeof(dis));
    for (int i=0; i<1<<18; ++i) for (int j=1; j<=10; ++j) s[i][j]=sl[i][j]=sr[i][j]=-INT_MAX;

    for (int i=0; i<M; ++i) {
        adj[R[i][0]].push_back(R[i][1]);
        adj[R[i][1]].push_back(R[i][0]);
    }
    for (int i=0; i<=city; ++i) bfs(i,i);
}

void panda_spawn(int P, int L, int X) {
    m[group[X]][L].insert(P-dis[X]*L);
    mr[group[X]][L].insert(P-group[X]*L-dis[X]*L);
    ml[group[X]][L].insert(P-(city-group[X])*L-dis[X]*L);

    update(0,city,1,group[X],*(m[group[X]][L].begin()),L);
    updater(0,city,1,group[X],*(mr[group[X]][L].begin()),L);
    updatel(0,city,1,group[X],*(ml[group[X]][L].begin()),L);
}

void panda_evac(int P,int L,int X) {
    m[group[X]][L].erase(m[group[X]][L].find(P-dis[X]*L));
    mr[group[X]][L].erase(mr[group[X]][L].find(P-group[X]*L-dis[X]*L));
    ml[group[X]][L].erase(ml[group[X]][L].find(P-(city-group[X])*L-dis[X]*L));

    if (m[group[X]][L].size()) update(0,city,1,group[X],*(m[group[X]][L].begin()),L);
    else update(0,city,1,group[X],-INT_MAX,L);

    if (mr[group[X]][L].size()) updater(0,city,1,group[X],*(mr[group[X]][L].begin()),L);
    else updater(0,city,1,group[X],-INT_MAX,L);

    if (ml[group[X]][L].size())updatel(0,city,1,group[X],*(ml[group[X]][L].begin()),L);
    else updatel(0,city,1,group[X],-INT_MAX,L);
}

int travel(int A,int B) {
    if (A>B) swap(A,B);
    int mmax=-INT_MAX;

    for (int i=1; i<=10; ++i) {
        mmax=max(mmax,query(0,city,1,A,B,i));
        if (B+1<=city) mmax=max(mmax,queryr(0,city,1,B+1,city,i)+i*B);
        if (A-1>=0) mmax=max(mmax,queryl(0,city,1,0,A-1,i)+i*(city-A));
    }

    return mmax;
}
/*
9 8 5 10
0 1
1 2
2 3
3 4
4 5
0 6
2 7
5 8
1 1 1 7
1 1 1 6
1 5 2 8
2 1 1 7
3 0 0
3 1 1
3 2 2
3 3 3
3 4 4
3 5 5

9 8 5 7
0 1
1 2
2 3
3 4
4 5
0 6
2 7
5 8
1 1 1 7
1 1 1 6
1 5 2 8
3 2 2
2 1 1 7
3 2 2
3 4 2

2 1 1 7
3 2 2
3 4 2
*/
