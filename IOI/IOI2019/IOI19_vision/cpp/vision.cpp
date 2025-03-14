#include "vision.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii; //(x,y)

int h,w,k,Aor[400],Bor[400],Axor[400],Bxor[400];
vector<int> a[400],b[400];

int cor(pii c) {return c.first*w+c.second;}

int check(int p) {
    vector<int> v;
    for (int i=0; i<h+w-p-1; ++i) {
        vector<int> temp1,temp2;
        for (int j=i; j<=i+p; ++j) temp1.push_back(Aor[j]), temp2.push_back(Axor[j]);

        int x=add_or(temp1), y=add_xor(temp2);
        y=add_not(y);
        x=add_and({x,y});
        v.push_back(x);
    }
    int fir=add_or(v);

    v.clear();
    for (int i=0; i<h+w-p-1; ++i) {
        vector<int> temp1,temp2;
        for (int j=i; j<=i+p; ++j) temp1.push_back(Bor[j]), temp2.push_back(Bxor[j]);

        int x=add_or(temp1), y=add_xor(temp2);
        y=add_not(y);
        x=add_and({x,y});
        v.push_back(x);
    }
    int sec=add_or(v);

    return add_and({fir,sec});
}

void construct_network(int H, int W, int K) {
    h=H; w=W; k=K;
    for (int i=0; i<h; ++i) {
        for (int j=0; j<w; ++j) {
            a[i+j].push_back(cor({i,j}));
            b[i-j+w-1].push_back(cor({i,j}));
        }
    }

    for (int i=0; i<h+w-1; ++i) {
        Aor[i]=add_or(a[i]);
        Axor[i]=add_xor(a[i]);
        Bor[i]=add_or(b[i]);
        Bxor[i]=add_xor(b[i]);
    }

    int x=check(k), y=check(k-1);
    y=add_not(y);
    add_and({x,y});
}
/*
4 5 3
0 0 3 0
-1
*/
