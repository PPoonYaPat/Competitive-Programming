#include "bombs.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ans,shift,sum;
int pre;
priority_queue<ll> lsq;
priority_queue<ll, vector<ll>, greater<ll>> rsq;

void initialize(int N) {

}

long long max_hp_loss(int X, int T, int A, int P) {
    if (lsq.size()==0) {
        lsq.push(X);
        rsq.push(X);
        pre=T;
        sum+=A;
    } else {
        sum+=A;
        shift+=(T-pre)*P;
        pre=T;

        ll L=lsq.top()-shift, R=rsq.top()+shift;
        if (L<=X && X<=R) {
            lsq.push(X+shift);
            rsq.push(X-shift);
        } else if (X<L) {
            lsq.push(X+shift);
            lsq.push(X+shift);
            rsq.push(lsq.top()-2*shift);
            lsq.pop();
            ans+=(L-X);
        } else {
            rsq.push(X-shift);
            rsq.push(X-shift);
            lsq.push(rsq.top()+2*shift);
            rsq.pop();
            ans+=(X-R);
        }
    }
    return sum-ans;
}
/*
6
30 0 6 1
35 0 10 1
25 1 5 1
10 3 10 20
15 3 7 20
20 3 8 20
*/
