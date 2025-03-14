#include <bits/stdc++.h> 
using namespace std; 
  
struct node { 
    int val; 
    node *l, *r; 
  
    node(int v) : val(v), l(NULL), r(NULL) {} 
    node(node *L, node *R) : val(0), l(L), r(R) { 
        if (L) val+=L->val; 
        if (R) val+=R->val; 
    } 
}; 

vector<node*> arr; 
  
node* build(int l, int r) { 
    if (l==r) return new node(0); 
    else { 
        int mid=(l+r)/2; 
        return new node(build(l,mid),build(mid+1,r)); 
    } 
} 
  
node* update(int l, int r, int x, int val, node* pnode) { 
    if (x>r || x<l) return pnode; 
    if (l==r) return new node(pnode->val+val); 
    int mid=(l+r)/2; 
    return new node(update(l,mid,x,val,pnode->l),update(mid+1,r,x,val,pnode->r)); 
} 
  
int query(int l, int r, int x, int y, node* pnode) { 
    if (x>r || y<l) return 0;
    if (x<=l && r<=y) return pnode->val;
    int mid=(l+r)/2;
    return query(l,mid,x,y,pnode->l)+query(mid+1,r,x,y,pnode->r);
} 