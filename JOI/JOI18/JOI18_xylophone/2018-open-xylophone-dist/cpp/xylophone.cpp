#include "xylophone.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int dif[5001][5001],c[5001],st,ans[5001];

void solve(int n) {
    for (int i=1; i<n; ++i) dif[i][i+1]=query(i,i+1);
    for (int i=1; i<n-1; ++i) dif[i][i+2]=query(i,i+2);

    //first let c[1]>0
    c[1]=dif[1][2];

    for (int i=2; i<n; ++i) {
        c[i]=dif[i][i+1];
        if (dif[i-1][i]+dif[i][i+1]==dif[i-1][i+1]) {
            if (c[i-1]<0) c[i]=-c[i];
        } else {
            if (c[i-1]>0) c[i]=-c[i];
        }
    }

    for (int i=1; i<n; ++i) {
        int sum=0;
        bool have=false;
        for (int j=i; j<n; ++j) {
            sum+=c[j];
            if (abs(sum)==n-1) {
                have=true;
                st=i;
                ans[st]=1;
                if (sum==1-n) for (int i=1; i<n; ++i) c[i]=-c[i];
                break;
            }
        }
        if (have) break;
    }
    for (int i=st+1; i<=n; ++i) ans[i]=ans[i-1]+c[i-1];
    for (int i=st-1; i>=1; --i) ans[i]=ans[i+1]-c[i];
    for (int i=1; i<=n; ++i) answer(i,ans[i]);
}
/*
7
2 3 4 5 6 1 7
*/
