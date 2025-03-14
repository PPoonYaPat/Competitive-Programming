#include <bits/stdc++.h>
using namespace std;

struct node {
    int prior,val,sz;
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