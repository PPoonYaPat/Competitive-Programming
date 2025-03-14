#include "sequence.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

struct node {
    int sum,L_max,L_min,R_max,R_min;
} s[1<<21];

node merge(node a, node b) {
    node res;
    res.sum=a.sum+b.sum;
    res.R_max=max(b.R_max,a.R_max+b.sum);
    res.R_min=min(b.R_min,a.R_min+b.sum);
    res.L_max=max(a.L_max,b.L_max+a.sum);
    res.L_min=min(a.L_min,b.L_min+a.sum);
    return res;
}

int n,a[5000001];

void update(int l, int r, int idx, int x, int val) {
    if (x>r || x<l) return;
    if (l==r) {
        if (val==1) s[idx]={1,1,0,1,0};
        else if (val==-1) s[idx]={-1,0,-1,0,-1};
        else s[idx]={0,0,0,0,0};
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,val);
        update(mid+1,r,2*idx+1,x,val);
        s[idx]=merge(s[2*idx],s[2*idx+1]);
    }
}

node query(int l, int r, int idx, int x, int y) {
    if (x>r || y<l) return {0,0,0,0,0};
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return merge(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

vector<int> group[500001];
int maL1[500001],maL2[500001],maR1[500001],maR2[500001],sum[500001];

int sequence(int N, vector<int> A) {
    n=N;
    for (int i=0; i<n; ++i) a[i]=A[i], group[a[i]].push_back(i);
    for (int i=0; i<n; ++i) update(0,n-1,1,i,-1);

    for (int i=0; i<n; ++i) {
        for (auto s : group[i]) {
            if (s>0) maR2[s]=-query(0,n-1,1,0,s-1).R_min;
            if (s<n-1) maL2[s]=-query(0,n-1,1,s+1,n-1).L_min;
        }

        for (auto s : group[i]) update(0,n-1,1,s,0);
        for (auto s : group[i]) sum[s]=query(0,n-1,1,0,s).sum;

        for (auto s : group[i]) update(0,n-1,1,s,1);
        for (auto s : group[i]) {
            if (s>0) maR1[s]=query(0,n-1,1,0,s-1).R_max;
            if (s<n-1) maL1[s]=query(0,n-1,1,s+1,n-1).L_max;
        }
    }

    int ans=0;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<group[i].size(); ++j) {
            int l=0,r=j;

            while (l<r) {
                int mid=(l+r)/2;

                bool can=true;

                //is it possible to chose sequence at least from mid to j
                int ss=sum[group[i][j]]-sum[group[i][mid]], c=j-mid+1;

                if (c+ss<0 && maR1[group[i][mid]]+maL1[group[i][j]]+c+ss<0) can=false;
                if (c-ss<0 && maR2[group[i][mid]]+maL2[group[i][j]]+c-ss<0) can=false;

                if (can) r=mid;
                else l=mid+1;
            }

            ans=max(ans,j-l+1);
        }
    }
    return ans;
}
