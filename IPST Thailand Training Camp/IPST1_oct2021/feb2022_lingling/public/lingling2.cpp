#include "lingling.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int cnt;

struct A {
    int mmax,mmin,bef;
} ss[1<<20];

struct node {
    ll val;
    node *L, *R;

    node() {
        val=0;
        L=NULL;
        R=NULL;
        ++cnt;
        assert(cnt<=15000000);
    }

    void create_L() {
        if (L==NULL) L= new node();
    }
    void create_R() {
        if (R==NULL) R= new node();
    }
    void create() {
        if (L==NULL) L=new node();
        if (R==NULL) R=new node();
    }

    ~node() {
        delete L;
        delete R;
        L=NULL;
        R=NULL;
    }

} s[200010],lz[200010];

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

void push_lz(int l, int r, node *current_seg, node *current_lz) {
    if (current_lz->val==0) return;

    current_seg->val += (current_lz->val * (r-l+1));
    if (l!=r) {
        current_lz->create();
        current_lz->L->val+=current_lz->val;
        current_lz->R->val+=current_lz->val;
    }
    current_lz->val=0;
}

void update(int l, int r, node *current_seg, int x, int y, node *current_lz) {
    push_lz(l,r,current_seg,current_lz);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        current_lz->val=1;
        push_lz(l,r,current_seg,current_lz);
    } else {
        int mid=(l+r)/2;
        current_lz->create();
        current_seg->create();
        update(l,mid,current_seg->L,x,y,current_lz->L);
        update(mid+1,r,current_seg->R,x,y,current_lz->R);
        current_seg->val = current_seg->L->val + current_seg->R->val;
    }
}

ll query(int l, int r, node *current_seg, int x, int y, node *current_lz) {
    push_lz(l,r,current_seg,current_lz);
    if (x>r || y<l) return 0;
    if (x<=l && r<=y) return current_seg->val;
    int mid=(l+r)/2;

    ll ans=0;
    if (current_lz->L) current_seg->create_L(), ans+=query(l,mid,current_seg->L,x,y,current_lz->L);
    if (current_lz->R) current_seg->create_R(), ans+=query(mid+1,r,current_seg->R,x,y,current_lz->R);
    return ans;
}

void update_fen(int x, int l, int r) {
    while (x<=n+5) {
        update(0,n-1,&s[x],l,r,&lz[x]);
        x+=(x&-x);
    }
}

ll query_fen(int x, int l, int r) {
    ll sum=0;
    while (x) {
        sum+=query(0,n-1,&s[x],l,r,&lz[x]);
        x-=(x&-x);
    }
    return sum;
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
    for (int i=0; i<n; ++i) update_fen(i+1,0,P[i]-1);

/*
    for (int i=n-1; i>=0; --i) {
        for (int j=1; j<n; ++j) cout<<query_fen(j,0,i)<<" ";
        cout<<"\n";
    } */

}

ll minimum_branches(int L, int R){
    A h=query_period(0,n-1,1,L,R);
    if (h.mmax>R || h.mmin<L || h.bef>=L) return -1;

    if (L==0) return qs[R];
    else return qs[R]-qs[L-1]-query_fen(L,L,R);
}

/*
7
3 4 0 5 2 1 6
0
*/

