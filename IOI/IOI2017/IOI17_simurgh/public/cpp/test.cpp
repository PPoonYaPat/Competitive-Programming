#include <bits/stdc++.h>
#include <time.h>
using namespace std;
typedef pair<int,int> pii;

vector<pii> v;
map<pii,bool> have;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    srand(time(0));
    freopen("test.txt","w",stdout);

    int n=7;
    v.push_back(pii(0,1));
    for (int i=2; i<n; ++i) {
        int k=rand()%i;
        v.push_back(pii(k,i));
        have[pii(k,i)]=have[pii(i,k)]=true;
    }
    
    int cnt=10;
    while (cnt--) {
        int a=rand()%n, b=rand()%n;
        if (a==b) continue;
        if (have[pii(a,b)]) continue;
        v.push_back(pii(a,b));
        have[pii(a,b)]=have[pii(b,a)]=true;
    }
    
    cout<<n<<" "<<v.size()<<"\n";
    for (auto s : v) cout<<s.first<<" "<<s.second<<"\n";
    for (int i=0; i<n-1; ++i) cout<<i<<" ";

}