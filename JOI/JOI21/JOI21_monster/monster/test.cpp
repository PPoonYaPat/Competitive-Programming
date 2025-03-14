#include <bits/stdc++.h>
#include <time.h>
using namespace std;

vector<int> v;

void shuf(int x) {
    if (x==0) return;
    swap(v[rand()%x],v[x-1]);
    shuf(x-1);
}

int main() {
    int n=1000;
    freopen("test.txt","w",stdout);
    srand(time(0));
    for (int i=0; i<n; ++i) v.push_back(i);
    shuf(n);

    cout<<n<<"\n";
    for (auto s : v) cout<<s<<" ";
}