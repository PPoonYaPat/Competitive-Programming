#include "towers.h"
#include "stub.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int R[100010],L[100010],h[100010],n,s[1<<18];
pii sm[1<<18];
vector<pii> v;

void build_sm(int l, int r, int idx) {
    if (l==r) sm[idx]={h[l],l};
    else {
        int mid=(l+r)/2;
        build_sm(l,mid,2*idx);
        build_sm(mid+1,r,2*idx+1);

        if (sm[2*idx].first<=sm[2*idx+1].first) sm[idx]=sm[2*idx];
        else sm[idx]=sm[2*idx+1];
    }
}

pii query_sm(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {INT_MAX,0};
    if (x<=l && r<=y) return sm[idx];
    int mid=(l+r)/2;
    pii LL=query_sm(l,mid,2*idx,x,y), RR=query_sm(mid+1,r,2*idx+1,x,y);
    if (LL.first<=RR.first) return LL;
    else return RR;
}

struct ss {
    int mmin,mmax,sl,sr;
} sg[1<<18]; // i<j -> sl = j-i, sr=i-j

ss merge(ss l, ss r) {
    if (l.mmin==-1 && r.mmin==-1) return {-1,0,0,0};
    if (l.mmin==-1) return r;
    if (r.mmin==-1) return l;

    ss ans;
    ans.mmax=max(l.mmax,r.mmax);
    ans.mmin=min(l.mmin,r.mmin);
    ans.sl=max({l.sl,r.sl,r.mmax-l.mmin});
    ans.sr=max({l.sr,r.sr,l.mmax-r.mmin});
    return ans;
}

void build_sg(int l, int r, int idx) {
    if (l==r) sg[idx]={h[l],h[l],0,0};
    else {
        int mid=(l+r)/2;
        build_sg(l,mid,2*idx);
        build_sg(mid+1,r,2*idx+1);
        sg[idx]=merge(sg[2*idx],sg[2*idx+1]);
    }
}

ss query_sg(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {-1,0,0,0};
    if (x<=l && r<=y) return sg[idx];
    int mid=(l+r)/2;
    return merge(query_sg(l,mid,2*idx,x,y),query_sg(mid+1,r,2*idx+1,x,y));
}

struct node {
    int mmin,mmax,cnt;
    node *l, *r;

    node() : mmin(INT_MAX), mmax(-INT_MAX), cnt(0), l(NULL), r(NULL) {}

    node(int val) : mmin(val), mmax(val), cnt(1), l(NULL), r(NULL) {}

    node(node *L, node *R) : mmin(INT_MAX), mmax(-INT_MAX), cnt(0) , r(R), l(L) {
        if (L) {
            mmin=min(L->mmin,mmin);
            mmax=max(L->mmax,mmax);
            cnt+=L->cnt;
        }

        if (R) {
            mmin=min(R->mmin,mmin);
            mmax=max(R->mmax,mmax);
            cnt+=R->cnt;
        }
    }
};
typedef pair<int,node*> pin;
vector<pin> arr;

struct N {
    int mmin,mmax,cnt;
};

node* build(int l, int r) {
    if (l==r) return new node();
    int mid=(l+r)/2;
    return new node(build(l,mid),build(mid+1,r));
}

node* update(int l, int r, int x, node* pnode) {
    if (x>r || x<l) return pnode;
    if (l==r) return new node(l);
    int mid=(l+r)/2;
    return new node(update(l,mid,x,pnode->l),update(mid+1,r,x,pnode->r));
}

N query(int l, int r, int x, int y, node *pnode) {
    if (x>r || y<l) return {INT_MAX,-INT_MAX,0};
    if (x<=l && r<=y) return {pnode->mmin,pnode->mmax,pnode->cnt};
    int mid=(l+r)/2;
    N ans,L=query(l,mid,x,y,pnode->l),R=query(mid+1,r,x,y,pnode->r);
    ans.mmax=max(L.mmax,R.mmax);
    ans.mmin=min(L.mmin,R.mmin);
    ans.cnt=L.cnt+R.cnt;
    return ans;
}

void build_s(int l, int r, int idx) {
    if (l==r) s[idx]=h[l];
    else {
        int mid=(l+r)/2;
        build_s(l,mid,2*idx);
        build_s(mid+1,r,2*idx+1);
        s[idx]=max(s[2*idx],s[2*idx+1]);
    }
}

int query_s(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return 0;
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return max(query_s(l,mid,2*idx,x,y),query_s(mid+1,r,2*idx+1,x,y));
}

void init(int N, vector<int> H) {
    n=N;
    for (int i=0; i<n; ++i) h[i+1]=H[i];

    L[1]=0;
    for (int i=2; i<=n; ++i) {
        int idx=i-1;
        while (h[idx]>=h[i] && idx!=-1) idx=L[idx];
        L[i]=idx;
    }

    R[n]=n+1;
    for (int i=n-1; i>=1; --i) {
        int idx=i+1;
        while (h[idx]>=h[i] && idx!=-1) idx=R[idx];
        R[i]=idx;
    }

    build_s(1,n,1);
    build_sg(1,n,1);
    build_sm(1,n,1);

    for (int i=1; i<=n; ++i) {
        int h1=-1,h2=-1;
        if (L[i]+1<=i-1) h1=query_s(1,n,1,L[i]+1,i-1);
        if (i+1<=R[i]-1) h2=query_s(1,n,1,i+1,R[i]-1);

        if (L[i]==0) h1=INT_MAX;
        if (R[i]==n+1) h2=INT_MAX;

        if (h1!=-1 && h2!=-1) v.push_back(pii(min(h1,h2)-h[i],i));
    }

    sort(v.begin(),v.end(),greater<pii>());

    arr.push_back(pin(INT_MAX,build(1,n)));

    for (int i=0; i<v.size(); ++i) {
        node* pnode=update(1,n,v[i].second,arr.back().second);
        if (arr.back().first==v[i].first) arr.pop_back();
        arr.push_back(pin(v[i].first,pnode));
    }
}

int max_towers(int Le, int Ri, int D) {
    ++Le; ++Ri;

    int l=0, r=arr.size()-1;
    while (l<r) {
        int mid=(l+r+1)/2;
        if (arr[mid].first>=D) l=mid;
        else r=mid-1;
    }

    N res=query(1,n,Le,Ri,arr[l].second);
    int cnt=res.cnt,mi=res.mmin,ma=res.mmax;
    if (cnt==0) {
        ++cnt;
        int sm=query_sm(1,n,1,Le,Ri).second;
        if (sm+1<=Ri && query_sg(1,n,1,sm+1,Ri).sr>=D) ++cnt;
        if (Le<=sm-1 && query_sg(1,n,1,Le,sm-1).sl>=D) ++cnt;
        return cnt;
    }

    int LL=-1;
    if (mi!=Le && query_s(1,n,1,Le,mi-1)>=h[mi]+D) {
        l=Le; r=mi-1;
        while (l<r) {
            int mid=(l+r+1)/2;
            if (query_s(1,n,1,mid,mi-1)>=h[mi]+D) l=mid;
            else r=mid-1;
        }
        LL=l;
    }
    if (LL!=-1 && query_sg(1,n,1,Le,LL).sl>=D) ++cnt;

    int RR=-1;
    if (ma!=Ri && query_s(1,n,1,ma+1,Ri)>=h[ma]+D) {
        l=ma+1; r=Ri;
        while (l<r) {
            int mid=(l+r)/2;
            if (query_s(1,n,1,ma+1,mid)>=h[ma]+D) r=mid;
            else l=mid+1;
        }
        RR=l;
    }
    if (RR!=-1 && query_sg(1,n,1,RR,Ri).sr>=D) ++cnt;

    return cnt;
}
/*
7 3
10 20 60 40 50 30 70
1 5 10
2 2 100
0 6 17
*/
