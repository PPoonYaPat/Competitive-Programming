#include <bits/stdc++.h>
using namespace std;

int n;
set<int> s;

void solve(int val, int sum, int pre) {
    if (val==1) s.insert(sum);
    else {
        for (int i=1; i*i<=val; ++i) {
            if (val%i==0) {
                if (i!=1 && i>=pre) solve(val/i,sum+i-1,i);
                if (val/i>=pre && val!=i*i) solve(i,sum+val/i-1,val/i);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    solve(n,0,0);
    cout<<s.size()<<"\n";
    for (auto k : s) cout<<k<<" ";
}