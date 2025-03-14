#include "lingling.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

struct A {
    int mmax,mmin,bef;
} ss[1<<20];

struct Vertex {
    ll val,lz;
    Vertex *L, *R;

    Vertex(ll val) : L(NULL), R(NULL), val(val), lz(0) {}
    Vertex(Vertex *l, Vertex *r, ll val, ll lz) : L(l), R(r), val(val), lz(lz) {}
    Vertex(Vertex *l, Vertex *r) : L(l), R(r), val(0), lz(0) {
        if (l) val+=l->val;
        if (r) val+=r->val;
    }
};

vector<Vertex*> arr;
ll ans,qs[200010];
int bef[200010],n,have[200010],c[200010],f[200010],ls[200010];

A merge(A L, A R) {
    A ans;
    ans.mmax=max(L.mmax,R.mmax);
    ans.mmin=min(L.mmin,R.mmin);
    ans.bef=max(L.bef,R.bef);
    return ans;
}

void build_period(int l, int r, int idx) {
    if (l==r) {
        ss[idx]={c[l],c[l],bef[l]};
    } else {
        int mid=(l+r)/2;
        build_period(l,mid,2*idx);
        build_period(mid+1,r,2*idx+1);
        ss[idx]=merge(ss[2*idx],ss[2*idx+1]);
    }
}

A query_period(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {-INT_MAX,INT_MAX,-INT_MAX};
    if (x<=l && r<=y) return ss[idx];
    int mid=(l+r)/2;
    return merge(query_period(l,mid,2*idx,x,y),query_period(mid+1,r,2*idx+1,x,y));
}

//persistent segment tree with lazy propagation
Vertex* build(int l, int r) {
    if (l==r) return new Vertex(0);
    int mid=(l+r)/2;
    return new Vertex(build(l,mid),build(mid+1,r),0,0);
}

Vertex* update(Vertex *v, int l, int r, int x, int y, int cnt) {
    if (x>r || y<l) return new Vertex(v->L,v->R,v->val+(r-l+1)*cnt,v->lz+cnt);
    if (x<=l && r<=y) return new Vertex(v->L,v->R,v->val+(r-l+1)*(cnt+1),v->lz+cnt+1);
    int mid=(l+r)/2;
    return new Vertex(update(v->L,l,mid,x,y,v->lz+cnt),update(v->R,mid+1,r,x,y,v->lz+cnt));
}

ll query(Vertex *v, int l , int r, int x, int y, int cnt) {
    if (x>r || y<l) return 0;
    if (x<=l && r<=y) return v->val+(r-l+1)*cnt;
    int mid=(l+r)/2;
    return query(v->L,l,mid,x,y,cnt+v->lz)+query(v->R,mid+1,r,x,y,cnt+v->lz);
}


void upd(int x) {
    ++x;
    while (x<=n+5) {
        ++f[x];
        x+=(x&-x);
    }
}

int find(int x) {
    ++x;
    int sum=0;
    while (x) {
        sum+=f[x];
        x-=(x&-x);
    }
    return sum;
}

void init_monkeys(vector<int> P, int Q){
    n=P.size();
    memset(have,-1,sizeof(have));
    for (int i=0; i<(1<<20); ++i) ss[i]={-INT_MAX,INT_MAX,-INT_MAX};

    //find period
    for (int i=0; i<n; ++i) {
        c[i]=P[i];
        bef[i]=have[P[i]];
        have[P[i]]=i;
    }
    build_period(0,n-1,1);

    for (int i=0; i<n; ++i) {
        ls[i]=i-find(P[i]);
        upd(P[i]);
    }

    qs[0]=ls[0];
    for (int i=1; i<n; ++i) qs[i]=qs[i-1]+ls[i];
    arr.push_back(build(0,n-1));
    for (int i=1; i<=n; ++i) arr.push_back(update(arr[i-1],0,n-1,0,P[i-1]-1,0));
/*
    for (int i=n-1; i>=0; --i) {
        for (int j=1; j<n; ++j) cout<<query(arr[j],0,n-1,0,i,0)<<" ";
        cout<<"\n";
    } */

}

ll minimum_branches(int L, int R){
    A h=query_period(0,n-1,1,L,R);
    if (h.mmax>R || h.mmin<L || h.bef>=L) return -1;

    if (L==0) return qs[R];
    else return qs[R]-qs[L-1]-query(arr[L],0,n-1,L,R,0);
}

/*
7
3 4 0 5 2 1 6
0
*/

