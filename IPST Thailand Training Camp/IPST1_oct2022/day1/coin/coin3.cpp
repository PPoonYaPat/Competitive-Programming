#include "coin.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int,int> tu;
typedef pair<int,int> pii;

int s[1<<20],lz[1<<20],n,L;

void push_lz(int l, int r, int idx) {
    s[idx]+=lz[idx];
    if (l!=r) {
        lz[2*idx]+=lz[idx];
        lz[2*idx+1]+=lz[idx];
    }
    lz[idx]=0;
}

void update(int l, int r, int idx, int x, int y, int val) {
    push_lz(l,r,idx);
    if (x>r || y<l) return;
    if (x<=l && r<=y) {
        lz[idx]+=val;
        push_lz(l,r,idx);
    } else {
        int mid=(l+r)/2;
        update(l,mid,2*idx,x,y,val);
        update(mid+1,r,2*idx+1,x,y,val);
        s[idx]=max(s[2*idx],s[2*idx+1]);
    }
}

int query(int l, int r, int idx, int x, int y) {
    push_lz(l,r,idx);
    if (x>r || y<l) return 0;
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return max(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

int ans[200010],fen[200010];

void upd(int x, int val) {
    ++x;
    while (x<=n+5) {
        fen[x]+=val;
        x+=(x&-x);
    }
}

int find(int x) {
    ++x;
    int sum=0;
    while (x) {
        sum+=fen[x];
        x-=(x&-x);
    }
    return sum;
}

vector<pii> v;

void initialize(int N, vector<int> Rail, int lenght) {
    L=lenght;
    n=N;
    for (int i=0; i<Rail.size(); ++i) v.push_back(pii(Rail[i],i));
    sort(v.begin(),v.end(),greater<pii>());
}

int bs(int l, int r, int val) {
    --l;
    int st=find(l);
    while (l<r) {
        int mid=(l+r+1)/2;
        if (find(mid)-st<=val) l=mid;
        else r=mid-1;
    }
    return l;
}

vector<int> max_dist(vector<vector<int>> Coins) { //position, jump, size
    vector<tu> vv;
    for (int i=0; i<Coins.size(); ++i) {
        vv.push_back(tu(Coins[i][2],Coins[i][0],Coins[i][1],i));
    }
    sort(vv.begin(),vv.end(),greater<tu>());

    int idx=0;
    for (auto ss : vv) {
        int sz=get<0>(ss), start=get<1>(ss), jump=get<2>(ss), ord=get<3>(ss);

        while (v[idx].first>sz && idx<v.size()) {
            int pos=v[idx].second;
            upd(pos,1);
            if (L) update(0,n-1,1,max(0,pos-L+1),pos,1);
            ++idx;
        }

        int no_tape=bs(start,n-1,jump);
        int mmax=query(0,n-1,1,start,min(n-1,no_tape+1));
        ans[ord]=bs(start,n-1,jump+mmax)+1;
    }

    vector<int> Answer;
    for (int i=0; i<Coins.size(); ++i) Answer.push_back(ans[i]);
    return Answer;
}
/*
20 5 0
10929 27228 31330 24684 8814 7353 22226 12233 18581 9933 5951 21960 5884 6053 22736 23564 3472 22794 24954 9921
18 8 1385
0 5 16314
9 3 4688
9 3 18854
18 9 4055
*/
