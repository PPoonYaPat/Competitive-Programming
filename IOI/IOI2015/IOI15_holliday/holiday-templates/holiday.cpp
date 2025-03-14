#include"holiday.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;

int n,st,d,p[100001];
ll dpL[250005][3],dpR[250005][3],val[100001];
vector<pii> v;

struct Node {
    ll sum;
    int cnt;
} s[1<<18];

Node merge(Node a, Node b) {return {a.sum+b.sum,a.cnt+b.cnt};}

void update(int l, int r, int idx, int x, int val) {
    if (x>r || x<l) return;
    if (l==r) {
        if (val!=-1) s[idx]={val,1};
        else s[idx]={0,0};
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val);
        update(mid+1,r,2*idx+1,x,val);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

ll query(int l, int r, int idx, int want) {
    if (want==0) return 0;
    if (l==r) return s[idx].sum;
    int mid=(l+r)/2;
    if (s[2*idx].cnt<=want) return s[2*idx].sum+query(mid+1,r,2*idx+1,want-s[2*idx].cnt);
    else return query(l,mid,2*idx,want);
}

struct NN {
    int ld,rd,l,r,w;
};

int now;

void fL(int Ld, int Rd, int L, int R, int W) {
    now=st;
    for (int i=0; i<n; ++i) update(0,n-1,1,i,-1);

    queue<NN> q;
    q.push({Ld,Rd,L,R,W});

    while (!q.empty()) {
        int ld=q.front().ld, rd=q.front().rd, l=q.front().l, r=q.front().r, w=q.front().w;
        q.pop();

        int day=(ld+rd)/2;

        //consider in range l to r
        if (now<r) {
            for (int i=0; i<n; ++i) update(0,n-1,1,i,-1);
            for (int i=st-1; i>r; --i) update(0,n-1,1,p[i],val[i]);
        }

        int best=st;
        for (int i=r; i>=l; --i) {
            int tour=day-(st-i)*w;
            if (i!=st) update(0,n-1,1,p[i],val[i]);
            if (tour<=0) continue;

            ll h=query(0,n-1,1,tour);
            if (h>dpL[day][w]) {
                dpL[day][w]=h;
                best=i;
            }
        }

        if (ld<=rd) {
            q.push({ld,day-1,best,r,w});
            q.push({day+1,rd,l,best,w});
        }
        now=l;
    }
}

void fR(int Ld, int Rd, int L, int R, int W) {
    now=st;
    for (int i=0; i<n; ++i) update(0,n-1,1,i,-1);

    queue<NN> q;
    q.push({Ld,Rd,L,R,W});

    while (!q.empty()) {
        int ld=q.front().ld, rd=q.front().rd, l=q.front().l, r=q.front().r, w=q.front().w;
        q.pop();

        int day=(ld+rd)/2;

        //consider in range l to r
        if (now>l){
            for (int i=0; i<n; ++i) update(0,n-1,1,i,-1);
            for (int i=st+1; i<l; ++i) update(0,n-1,1,p[i],val[i]);
        }

        int best=st;
        for (int i=l; i<=r; ++i) {
            int tour=day-(i-st)*w;
            if (i!=st) update(0,n-1,1,p[i],val[i]);
            if (tour<=0) continue;

            ll h=query(0,n-1,1,tour);
            if (h>dpR[day][w]) {
                dpR[day][w]=h;
                best=i;
            }
        }

        if (ld<=rd) {
            q.push({ld,day-1,l,best,w});
            q.push({day+1,rd,best,r,w});
        }
        now=r;
    }
}

ll findMaxAttraction(int N, int start, int D, int att[]) {
    n=N; st=start; d=D;
    for (int i=0; i<n; ++i) val[i]=att[i], v.push_back(pii(att[i],i));
    sort(v.begin(),v.end(),greater<pii>());
    for (int i=0; i<n; ++i) p[v[i].second]=i;

    fR(0,d,st+1,n-1,1);
    fR(0,d,st+1,n-1,2);
    fL(0,d,0,st-1,1);
    fL(0,d,0,st-1,2);

    ll ans=0;
    for (int i=0; i<=d; ++i) { //go right for i days

        //go right first
        ans=max(ans,dpR[i][2]+dpL[d-i][1]);
        if (i!=d) ans=max(ans,dpR[i][2]+dpL[d-i-1][1]+val[st]);

        //go left first
        ans=max(ans,dpL[d-i][2]+dpR[i][1]);
        if (i!=d) ans=max(ans,dpL[d-i-1][2]+dpR[i][1]+val[st]);
        
    }

    return ans;
}
