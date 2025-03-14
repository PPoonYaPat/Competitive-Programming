#include "capybara.h"
#include "public.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fen[200010];
int n;

void update(int x, ll val) {
    ++x;
    while (x<=n+5) {
        fen[x]+=val;
        x+=x&-x;
    }
}

ll find(int x) {
    ++x;
    ll sum=0;
    while (x) {
        sum+=fen[x];
        x-=x&-x;
    }
    return sum;
}

void capybara(int N, int Q, vector<int> M, vector<int> K){
    n=N;
    for (int i=0; i<n-1; ++i) update(i,K[i]);

    cout<<"yes";
}

long long travel(int A,int B){
    return find(B-1)-find(A);
}
/*
6 3
0 0 0 0 0 0
4 2 1 5 3
1 3
2 4
3 5
*/
