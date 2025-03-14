#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

Vertex* build(int l, int r) { 
    if (l==r) return new Vertex(0); 
    int mid=(l+r)/2; 
    return new Vertex(build(l,mid),build(mid+1,r),0,0); 
} 

Vertex* update(Vertex *v, int l, int r, int x, int y, int cnt, int val) { 
    if (x>r || y<l) return new Vertex(v->L, v->R, v->val+(r-l+1)*cnt, v->lz+cnt); 
    if (x<=l && r<=y) return new Vertex(v->L, v->R, v->val+(r-l+1)*(cnt+val), v->lz+cnt+val); 
    int mid=(l+r)/2; 
    return new Vertex(update(v->L,l,mid,x,y,v->lz+cnt,val),update(v->R,mid+1,r,x,y,v->lz+cnt,val)); 
} 
  
ll query(Vertex *v, int l , int r, int x, int y, int cnt) { 
    if (x>r || y<l) return 0; 
    if (x<=l && r<=y) return v->val+(r-l+1)*cnt; 
    int mid=(l+r)/2; 
    return query(v->L,l,mid,x,y,cnt+v->lz)+query(v->R,mid+1,r,x,y,cnt+v->lz); 
} 