#include <bits/stdc++.h> 
using namespace std; 
typedef long long ll; 
  
const int mx=1e9+1, mn=-1e9-1; 
  
struct Line { 
    ll m,c; 
}; 
  
ll f(Line a, ll x) { 
    return a.m*x+a.c; 
} 
  
struct node { 
    Line line; 
    node *l, *r; 

    node(Line li) : l(NULL), r(NULL), line(li) {} 
}; 

void add(Line nw, int l, int r, node *pnode) { 
    int mid=(l+r)/2; 
    bool lef= f(nw,l)<f(pnode->line,l); 
    bool m= f(nw,mid)<f(pnode->line,mid); 
  
    if (m) swap(nw,pnode->line); 
  
    if (r-l==1) return; 
    else if (m!=lef) { 
        if (pnode->l) add(nw,l,mid,pnode->l); 
        else pnode->l=new node(nw); 
    } else { 
        if (pnode->r) add(nw,mid,r,pnode->r); 
        else pnode->r=new node(nw); 
    } 
} 
  
ll get(int l, int r, int x, node *pnode) { 
    int mid=(l+r)/2; 
    if (r-l==1) return f(pnode->line,x); 
    else if (x<mid) { 
        if (pnode->l) return min(f(pnode->line,x),get(l,mid,x,pnode->l)); 
        else return f(pnode->line,x); 
    } else { 
        if (pnode->r) return min(f(pnode->line,x),get(mid,r,x,pnode->r)); 
        else return f(pnode->line,x); 
    } 
} 
  