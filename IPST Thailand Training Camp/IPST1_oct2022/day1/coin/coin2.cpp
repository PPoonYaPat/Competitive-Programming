#include <bits/stdc++.h>
#include "coin.h"
#include "grader.cpp"
#define pii pair<int, int>
#define st first
#define nd second
#define pb push_back
using namespace std;

const int NN = 2e5 + 10;

int fw[NN], seg[4*NN], t[4*NN];

void update_fw(int i) {
    for (; i < NN; i += i&-i) fw[i]++;
}

int query_fw(int i) {
    int ret = 0;
    for (; i > 0; i -= i&-i) ret += fw[i];
    return ret;
}

void push(int idx) {
    seg[2*idx] += t[idx];
    t[2*idx] += t[idx];
    seg[2*idx+1] += t[idx];
    t[2*idx+1] += t[idx];
    t[idx] = 0;
}

void update(int l, int r, int a, int b, int val, int idx) {
    if (a > b) return;
    if (a == l && b == r) {
        seg[idx] += val;
        t[idx] += val;
        return;
    }
    push(idx);
    int mid = (l+r)/2;
    update(l, mid, a, min(b, mid), val, 2*idx);
    update(mid+1, r, max(a, mid+1), b, val, 2*idx+1);
    seg[idx] = max(seg[2*idx], seg[2*idx+1]);
}

int query(int l, int r, int a, int b, int idx) {
    if (b < a) return INT_MIN;
    if (a <= l && r <= b) return seg[idx];
    push(idx);
    int mid = (l+r)/2;
    return max(query(l, mid, a, min(b, mid), 2*idx), query(mid+1, r, max(a, mid+1), b, 2*idx+1));
}

pii a[NN];
int idx = 0;
int N;
int L;

void initialize(int n, vector<int> Rail, int l) {
    L = l;
    N = n;
    for (int i = 0; i < N; ++i) {
        a[i] = {Rail[i], i+1};
    }
    sort(a, a+N, greater<pii>());
    return;
}

pair<pii, pii> coin[NN];

int f(int l, int r, int val) {
    int stt = l-1;
    while (l < r) {
        int mid = (l+r)/2;
        int v = query_fw(mid) - query_fw(stt);
        if (v <= val) l = mid+1;
        else r = mid;
    }
    return l;
}

vector<int> max_dist(vector<vector<int>> Coins) {
    int Q = Coins.size();
    for (int i = 0; i < Q; ++i) {
        coin[i] = {{Coins[i][2], i}, {Coins[i][0]+1, Coins[i][1]}};
    }
    sort(coin, coin + Q, greater<pair<pii, pii>>());
    vector<int> Ans(Q);

    update_fw(N+1);
    for (int i = 0; i < Q; ++i) {
        int idxx = coin[i].st.nd;
        int aa = coin[i].nd.st;
        int b = coin[i].nd.nd;
        int c = coin[i].st.st;
        while (idx < N && a[idx].st > c) {
            update_fw(a[idx].nd);
            update(1, N, max(a[idx].nd-L+1, 1), a[idx].nd, 1, 1);
            idx++;
        }
        int max_dis = f(aa, N+1, b);
        int max_cover = query(1, N, aa, max_dis, 1);
        Ans[idxx] = f(aa, N+1, b+max_cover)-1;
    }

    return Ans;
}
/*
13 1 0
18517 27318 13444 11129 21484 21329 18646 13147 24574 27951 17726 21335 26284
5 0 3145
*/
