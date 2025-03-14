#include "lonelytown.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

struct NN {
    int mmin,cnt;
} s[1<<18];

int lz[1<<18],n;

void push(int l, int r, int idx) {
    s[idx].mmin+=lz[idx];
    if (l!=r) {
        lz[2*idx]+=lz[idx];
        lz[2*idx+1]+=lz[idx];
    }
    lz[idx]=0;
}

NN merge(NN a, NN b) {
    NN res;
    if (a.mmin<b.mmin) res.mmin=a.mmin, res.cnt=a.cnt;
    else if (a.mmin>b.mmin) res.mmin=b.mmin, res.cnt=b.cnt;
    else res.mmin=a.mmin, res.cnt=a.cnt+b.cnt;
    return res;
}

void build(int l, int r, int idx) {
    if (l==r) s[idx]={0,1};
    else {
        int mid=(l+r)/2;
        build(l,mid,2*idx);
        build(mid+1,r,2*idx+1);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

void update(int l, int r, int idx, int x, int y, int val) {
    push(l,r,idx);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        lz[idx]+=val;
        push(l,r,idx);
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,y,val);
        update(mid+1,r,2*idx+1,x,y,val);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

int query(int l, int r, int idx, int x, int y, int val) {
    push(l,r,idx);
    if (x>r || y<l) return 0;
    if (x<=l && r<=y) {
        if (s[idx].mmin==val) return s[idx].cnt;
        return 0;
    } else {
        int mid=(l+r)/2;
        return query(l,mid,2*idx,x,y,val)+query(mid+1,r,2*idx+1,x,y,val);
    }
}

pii seg[1<<18]; //mmin,mmax
multiset<int> mi[100001];
multiset<int, greater<int>> ma[100001];

pii merge2(pii a, pii b) {
    pii res;
    res.first=min(a.first,b.first);
    res.second=max(a.second,b.second);
    return res;
}

void update2(int l, int r, int idx, int x) {
    if (x>r || x<l) return;
    if (l==r) {

        if (mi[x].size()) seg[idx].first=*(mi[x].begin());
        else seg[idx].first=n;

        if (ma[x].size()) seg[idx].second=*(ma[x].begin());
        else seg[idx].second=-1;

    } else {
        int mid=(l+r)/2;
        update2(l,mid,2*idx,x);
        update2(mid+1,r,2*idx+1,x);
        seg[idx]=merge2(seg[2*idx],seg[2*idx+1]);
    }
}

int fen[100010];

int find(int x) {
    int sum=0;
    ++x;
    while (x) {
        sum+=fen[x];
        x-=x&-x;
    }
    return sum;
}

void upd(int x, int val) {
    ++x;
    while (x<=n+5) {
        fen[x]+=val;
        x+=x&-x;
    }
}

pii query2(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return pii(n,-1);
    if (x<=l && r<=y) return seg[idx];
    int mid=(l+r)/2;
    return merge2(query2(l,mid,2*idx,x,y),query2(mid+1,r,2*idx+1,x,y));
}

void add(int a, int b) {
    if (a>b) swap(a,b);
    update(0,n-1,1,a,b,1);
    upd(a,1);
    upd(b,-1);

    ma[a].insert(b);
    update2(0,n-1,1,a);

    mi[b].insert(a);
    update2(0,n-1,1,b);
}

void del(int a, int b) {
    if (a>b) swap(a,b);
    update(0,n-1,1,a,b,-1);
    upd(a,-1);
    upd(b,1);

    ma[a].erase(ma[a].find(b));
    update2(0,n-1,1,a);

    mi[b].erase(mi[b].find(a));
    update2(0,n-1,1,b);
}

void init_town(int N, int Q, vector<int> u, vector<int> v) {
    n=N;
    build(0,n-1,1);
    for (int i=0; i<(1<<18); ++i) seg[i]=pii(n,-1);
    for (int i=0; i<n-1; ++i) add(u[i],v[i]);
}

void change_edge(int x, int y, int z) {
    add(x,z);
    del(x,y);
}

int lonelytown_query() {
    return query(0,n-1,1,0,n-1,0);
}

int simulate_query(int e) {
    int a=e,b=e+1;

    if (find(e)==0) return query(0,n-1,1,0,n-1,0);
    else {
        int l=0, r=a+1;
        while (l<r) {
            int mid=(l+r)/2;
            if (query2(0,n-1,1,mid,a).second>a) l=mid+1;
            else r=mid;
        }
        int st=l;

        l=b-1; r=n-1;
        while (l<r) {
            int mid=(l+r+1)/2;
            if (query2(0,n-1,1,b,mid).first<b) r=mid-1;
            else l=mid;
        }
        int ed=l;

        if (find(e)==1) {
            del(st-1,ed+1);
            int ans=query(0,n-1,1,0,n-1,0);
            add(st-1,ed+1);
            return ans;
        } else {
            return query(0,n-1,1,0,st-1,0)+query(0,n-1,1,st,ed,find(e))+query(0,n-1,1,ed+1,n-1,0);
        }
    }
}
/*
6 10
0 1
2 0
0 5
3 5
5 4
2
1 0 2 1
2
1 5 0 4
2
1 1 0 5
1 1 0 5
2
3 1
2

0
0
1
1
2
1
*/
