#include "cheatsheet.h"
#include <bits/stdc++.h>
#include "stub.cpp"
using namespace std;
typedef long long ll;

struct bignum {
    ll c[501];
};

const ll mod=350001;

bignum add(bignum a, bignum b) {
    bignum res;
    for (int i=0; i<500; ++i) {
        res.c[i]=(a.c[i]+b.c[i])%mod;
        res.c[i+1]+=(a.c[i])
    }
}

vector<int> write_cheatsheet(int n, vector<int> A){
    //find the Ath order of the permutation
	vector<int> ans;
    
    return ans;
}

vector<int> recover_answer(int n, vector<int> r){
    //find the order of r permutation
	vector<int> ans;

    return ans;
}
