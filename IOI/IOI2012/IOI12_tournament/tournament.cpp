#include <bits/stdc++.h>
#include "grader.cpp"
using namespace std;

int s[1<<18],n,cnt[100001];

void build(int l, int r, int idx, int *c) {
    if (l==r) s[idx]=c[l];
    else {
        int mid=(l+r)/2;
        build(l,mid,2*idx,c);
        build(mid+1,r,2*idx+1,c);
        s[idx]=max(s[2*idx],s[2*idx+1]);
    }
}

int query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return 0;
    if (x<=l && r<=y) return s[idx];

    int mid=(l+r)/2;
    return max(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

struct node {
    int prior,val,sz; //val is the max position contained in that node
    struct node *l,*r;
    node(int x) : prior(rand()), val(x), sz(1), l(NULL), r(NULL) {}
};
typedef node* pnode;

int get_sz(pnode t) {
    if (t==NULL) return 0;
    else return t->sz;
}

void upd(pnode t) {
    if (t) t->sz=get_sz(t->l)+get_sz(t->r)+1;
}

void split(pnode t, pnode &l, pnode &r, int k) {
    if (t==NULL) l=r=NULL;
    else if (get_sz(t->l)<k) split(t->r,t->r,r,k-get_sz(t->l)-1), l=t;
    else split(t->l,l,t->l,k), r=t;
    upd(t);
}

void merge(pnode &t, pnode l, pnode r) {
    if (l==NULL) t=r;
    else if (r==NULL) t=l;
    else if (l->prior > r->prior) merge(l->r,l->r,r), t=l;
    else merge(r->l,l,r->l), t=r;
    upd(t);
}

int find_max(pnode t) {
    if (t==NULL) return -1;
    while ((t->r)!=NULL) t=t->r;
    return t->val;
}

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
    n=N;
    build(0,n-2,1,K); //build segment

    pnode treap=0;
    for (int i=0; i<n; ++i) merge(treap,treap,new node(i)); //build treap

    for (int i=0; i<C; ++i) {
        //start at S[i], end at E[i]
        pnode A,B,C;
        split(treap,A,B,S[i]);
        split(B,B,C,E[i]-S[i]+1);
        int mmin=find_max(A)+1, mmax=find_max(B);
        if (query(0,n-2,1,mmin,mmax-1)<R) ++cnt[mmin], --cnt[mmax+1];
        merge(treap,A,new node(mmax));
        merge(treap,treap,C);
    }

    int sum_best=0,sum=0,ans=0;
    for (int i=0; i<=n-1; ++i) {
        sum+=cnt[i];
        if (sum>sum_best) {
            sum_best=sum;
            ans=i;
        }
    }
    return ans;
}
/*
5 3 3
1
0
2
4
1 3
0 1
0 1
*/
