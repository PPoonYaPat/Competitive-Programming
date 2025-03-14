#include <bits/stdc++.h>
#include <utility>
#include "grader.cpp"
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

multiset<int, greater<int>> s[11][1<<18];

void add(int l, int r, int idx, int x, int val, int L) { //val is P-distance to near
    if (x>r || x<l) return;
    s[L][idx].insert(val);
    if (l!=r) {
        int mid=(l+r)/2;
        add(l,mid,2*idx,x,val,L);
        add(mid+1,r,2*idx+1,x,val,L);
    }
}

void del(int l, int r, int idx, int x, int val, int L) {
    if (x>r || x<l) return;
    s[L][idx].erase(s[L][idx].find(val));
    if (l!=r) {
        int mid=(l+r)/2;
        del(l,mid,2*idx,x,val,L);
        del(mid+1,r,2*idx+1,x,val,L);
    }
}

int query(int l, int r, int idx, int x, int y, int L) {
    if (x>r || y<l) return -INT_MAX;
    if (x<=l && r<=y) {
        if (s[L][idx].size()) return *(s[L][idx].begin());
        else return -INT_MAX;
    }

    int mid=(l+r)/2;
    return max(query(l,mid,2*idx,x,y,L),query(mid+1,r,2*idx+1,x,y,L));
}

multiset<int, greater<int>> sr[11][1<<18];

void add_right(int l, int r, int idx, int x, int val, int L) { //val is P-distance to near
    if (x>r || x<l) return;
    sr[L][idx].insert(val);
    if (l!=r) {
        int mid=(l+r)/2;
        add_right(l,mid,2*idx,x,val,L);
        add_right(mid+1,r,2*idx+1,x,val,L);
    }
}

void del_right(int l, int r, int idx, int x, int val, int L) {
    if (x>r || x<l) return;
    sr[L][idx].erase(sr[L][idx].find(val));
    if (l!=r) {
        int mid=(l+r)/2;
        del_right(l,mid,2*idx,x,val,L);
        del_right(mid+1,r,2*idx+1,x,val,L);
    }
}

int query_right(int l, int r, int idx, int x, int y, int L) {
    if (x>r || y<l) return -INT_MAX;
    if (x<=l && r<=y) {
        if (sr[L][idx].size()) return *(sr[L][idx].begin());
        else return -INT_MAX;
    }

    int mid=(l+r)/2;
    return max(query_right(l,mid,2*idx,x,y,L),query_right(mid+1,r,2*idx+1,x,y,L));
}

multiset<int, greater<int>> sl[11][1<<18];

void add_left(int l, int r, int idx, int x, int val, int L) { //val is P-distance to near
    if (x>r || x<l) return;
    sl[L][idx].insert(val);
    if (l!=r) {
        int mid=(l+r)/2;
        add_left(l,mid,2*idx,x,val,L);
        add_left(mid+1,r,2*idx+1,x,val,L);
    }
}

void del_left(int l, int r, int idx, int x, int val, int L) {
    if (x>r || x<l) return;
    sl[L][idx].erase(sl[L][idx].find(val));
    if (l!=r) {
        int mid=(l+r)/2;
        del_left(l,mid,2*idx,x,val,L);
        del_left(mid+1,r,2*idx+1,x,val,L);
    }
}

int query_left(int l, int r, int idx, int x, int y, int L) {
    if (x>r || y<l) return -INT_MAX;
    if (x<=l && r<=y) {
        if (sl[L][idx].size()) return *(sl[L][idx].begin());
        else return -INT_MAX;
    }

    int mid=(l+r)/2;
    return max(query_left(l,mid,2*idx,x,y,L),query_left(mid+1,r,2*idx+1,x,y,L));
}

void initialize(int N, int M, int S, vector<vector<int>>R) {
    n=N, city=S;
    memset(dis,0x3f,sizeof(dis));
    for (int i=0; i<M; ++i) {
        adj[R[i][0]].push_back(R[i][1]);
        adj[R[i][1]].push_back(R[i][0]);
    }
    for (int i=0; i<=city; ++i) bfs(i,i);
}

void panda_spawn(int P, int L, int X) {
    add(0,city,1,group[X],P-L*dis[X],L);
    add_right(0,city,1,group[X],P-group[X]*L-dis[X]*L,L);
    add_left(0,city,1,group[X],P-(city-group[X])*L-dis[X]*L,L);
}

void panda_evac(int P,int L,int X) {
    del(0,city,1,group[X],P-L*dis[X],L);
    del_right(0,city,1,group[X],P-group[X]*L-dis[X]*L,L);
    del_left(0,city,1,group[X],P-(city-group[X])*L-dis[X]*L,L);
}

int travel(int A,int B) {
    if (A>B) swap(A,B);
    int mmax=-INT_MAX;
    for (int i=1; i<=10; ++i) {
        mmax=max(mmax,query(0,city,1,A,B,i));
        if (B+1<=city) mmax=max(mmax,query_right(0,city,1,B+1,city,i)+i*B);
        if (A-1>=0) mmax=max(mmax,query_left(0,city,1,0,A-1,i)+i*(city-A));
    }
    return mmax;
}
/*
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
*/
