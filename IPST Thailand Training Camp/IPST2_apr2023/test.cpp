#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int f(int x, int k) {
    return (x/k)*(x/k)*(k-(x%k)) + (x/k+1)*(x/k+1)*(x%k);
}

int main() {
    int n=1000;
    for (int i=40; i<80; ++i) cout<<f(n,i)-f(n,i+1)<<" ";
}
