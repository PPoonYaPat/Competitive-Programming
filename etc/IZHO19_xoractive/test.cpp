#include <bits/stdc++.h>
#include <time.h>
using namespace std;

map<int,bool> have;

int main() {
    freopen("test.txt","w",stdout);
    srand(time(0));
    int n; cin>>n;
    cout<<n<<"\n";
    for (int i=1; i<=n; ++i) {
        int k=-1;
        while (k==-1) {
            int h=(rand()/2)*(rand()/2);
            if (!have[h]) {
                have[h]=true;
                k=h;
            }
        }
        cout<<k<<" ";
    }
}