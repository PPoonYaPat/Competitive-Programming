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
    if (x>r || y<l) return INT_MIN;
    if (x<=l && r<=y) return s[idx];
    int mid=(l+r)/2;
    return max(query(l,mid,2*idx,x,y),query(mid+1,r,2*idx+1,x,y));
}

int ans[200010],fen[200010];

void upd(int x) {
    while (x<=n+5) {
        ++fen[x];
        x+=(x&-x);
    }
}

int find(int x) {
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
    for (int i=0; i<Rail.size(); ++i) v.push_back(pii(Rail[i],i+1));
    sort(v.begin(),v.end(),greater<pii>());
}

int bs(int l, int r, int val) {
    int st=find(l-1);
    while (l<r) {
        int mid=(l+r)/2;
        if (find(mid)-st<=val) l=mid+1;
        else r=mid;
    }
    return l;
}

vector<int> max_dist(vector<vector<int>> Coins) { //position, jump, size
    vector<tu> vv;
    for (int i=0; i<Coins.size(); ++i) {
        vv.push_back(tu(Coins[i][2],Coins[i][0]+1,Coins[i][1],i));
    }
    sort(vv.begin(),vv.end(),greater<tu>());

    int idx=0;

    upd(n+1);
    for (auto ss : vv) {
        int sz=get<0>(ss), start=get<1>(ss), jump=get<2>(ss), ord=get<3>(ss);

        while (v[idx].first>sz && idx<v.size()) {
            int pos=v[idx].second;
            upd(pos);
            if (L) update(1,n,1,max(1,pos-L+1),pos,1);
            ++idx;
        }

        int no_tape=bs(start,n+1,jump);
        assert(start<=no_tape);
        int mmax=query(1,n,1,start,no_tape);
        ans[ord]=bs(start,n+1,jump+mmax)-1;
    }

    vector<int> Answer;
    for (int i=0; i<Coins.size(); ++i) Answer.push_back(ans[i]);
    return Answer;
}
/*
7 3 2
1 2 1 3 1 3 3
1 1 2
1 0 1
1 1 1

7 3 1
1 2 1 3 3 3 4
3 0 3
1 0 1
1 1 1

11 17 34
26500 19169 15724 11478 29358 26962 24464 5705 28145 23281 16827
6 11 2995
7 3 5436
7 0 3902
10 4 12382
8 8 19718
7 11 21726
9 6 1869
2 11 26299
7 6 28703
7 2 30333
7 8 15141
0 5 6868
5 8 32662
10 9 12859
0 9 27529
8 4 3035
3 6 288
*/
