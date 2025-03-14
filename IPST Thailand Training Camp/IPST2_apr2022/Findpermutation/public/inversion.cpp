#include "inversion.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll sum_pre,sum_now;
int ord_pre,ord_now;

struct node {
    int sz,prior,val;
    struct node *l, *r;
    node(int v) {
        prior=rand();
        sz=1;
        val=v;
        l=r=NULL;
    }
};
typedef node* pnode;

int find_sz(pnode t) {
    if (t) return t->sz;
    else return 0;
}

void update(pnode t) {
    if (t) t->sz=find_sz(t->l)+find_sz(t->r)+1;
}

void split(pnode t, pnode &l, pnode &r, int k) {
    if (!t) l=r=NULL;
    else if (find_sz(t->l)<k) split(t->r,t->r,r,k-find_sz(t->l)-1), l=t;
    else split(t->l,l,t->l,k), r=t;
    update(t);
}

void merge(pnode l, pnode r, pnode &t) {
    if (l==NULL) t=r;
    else if (r==NULL) t=l;
    else if (l->prior>r->prior) merge(l->r,r,l->r), t=l;
    else merge(l,r->l,r->l), t=r;
    update(t);
}

int c,ord[100001];
void answer(pnode t) {
    if (t==NULL) return;
    answer(t->l);
    ord[t->val]=++c;
    answer(t->r);
}

std::vector<int> find_permutation(int n, long long sum) {
    sum_pre=sum;
    ord_pre=0;
    pnode treap=new node(0);

    for (int i=1; i<n; ++i) {
        sum_now=swap_and_report(0,i);
        ord_now=(sum_now-sum_pre+2*ord_pre+1)/2;

        pnode A;
        split(treap,treap,A,ord_now);
        merge(treap,new node(i),treap);
        merge(treap,A,treap);

        swap(sum_pre,sum_now);
        swap(ord_pre,ord_now);
    }

    answer(treap);
    vector<int> ans;
    for (int i=0; i<n; ++i) ans.push_back(ord[i]);
    return ans;
}
/*
5
4 1 3 5 2
*/
