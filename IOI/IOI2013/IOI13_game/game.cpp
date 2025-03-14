#include "game.h"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int r,c;
map<pii,ll> s;

long long gcd2(long long X, long long Y) {
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

ll gcd(ll x, ll y) {
    if (x==0) return y;
    if (y==0) return x;
    return gcd2(x,y);
}

void init(int R, int C) {
    r=R;
    c=C;
}

void update_y(int lx, int rx, int idx_x, int ly, int ry, int idx_y, int x, int y, ll val) {
    if (ly>y || ry<y) return;
    if (ly==ry) {
        if (lx==rx) {
            s[pii(idx_x,idx_y)]=val;
        } else {
            s[pii(idx_x,idx_y)]=gcd(s[pii(2*idx_x,idx_y)],s[pii(2*idx_x+1,idx_y)]);
        }
    } else {
        int mid=(ly+ry)/2;
        update_y(lx,rx,idx_x,ly,mid,2*idx_y,x,y,val);
        update_y(lx,rx,idx_x,mid+1,ry,2*idx_y+1,x,y,val);
        s[pii(idx_x,idx_y)]=gcd(s[pii(idx_x,2*idx_y)],s[pii(idx_x,2*idx_y+1)]);
    }
}

void update_x(int lx, int rx, int idx_x, int x, int y, ll val) {
    if (lx>x || rx<x) return;
    if (lx!=rx) {
        int mid=(lx+rx)/2;
        update_x(lx,mid,2*idx_x,x,y,val);
        update_x(mid+1,rx,2*idx_x+1,x,y,val);
    }
    update_y(lx,rx,idx_x,1,c,1,x,y,val);
}

void update(int P, int Q, long long K) {
    ++P; ++Q;
    update_x(1,r,1,P,Q,K);
}

ll query_y(int idx_x, int ly, int ry, int idx_y, int y1, int y2) {
    if (y1>ry || y2<ly) return 0;
    if (y1<=ly && ry<=y2) return s[pii(idx_x,idx_y)];
    int mid=(ly+ry)/2;
    return gcd(query_y(idx_x,ly,mid,2*idx_y,y1,y2),query_y(idx_x,mid+1,ry,2*idx_y+1,y1,y2));
}

ll query_x(int lx, int rx, int idx_x, int x1, int y1, int x2, int y2) {
    if (x1>rx || x2<lx) return 0;
    if (x1<=lx && rx<=x2) return query_y(idx_x,1,c,1,y1,y2);
    int mid=(lx+rx)/2;
    return gcd(query_x(lx,mid,2*idx_x,x1,y1,x2,y2),query_x(mid+1,rx,2*idx_x+1,x1,y1,x2,y2));
}

long long calculate(int P, int Q, int U, int V) {
    ++P; ++Q; ++U; ++V;
    if (P>U) swap(P,U);
    if (Q>V) swap(Q,V);
    return query_x(1,r,1,P,Q,U,V);
}

