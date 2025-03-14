#include <bits/stdc++.h>
#include <time.h>
using namespace std;
typedef pair<int,int> pii;

vector<int> v;
vector<pii> edge;

void gen(int n) {
    vector<int> temp;
    for (int i=0; i<n; ++i) temp.push_back(i);

    while (temp.size()) {
        int k=temp.size();
        int h=rand()%k;
        v.push_back(temp[h]);
        swap(temp[h],temp[k-1]);
        temp.pop_back();
    }
}

int main() {
    srand(time(0));

    freopen("in.txt","w",stdout);

    int n=100000,m=n+9,q=100000;
    cout<<n<<" "<<m<<" "<<q<<" "<<1<<"\n";
    gen(n);

    edge.push_back({v[0],v[1]});
    for (int i=2; i<n; ++i) {
        int pref=rand()%(i-1);
        edge.push_back({v[pref],v[i]});
    }

    for (int i=0; i<10; ++i) edge.push_back({rand()%n,rand()%n});

    for (auto s : edge) cout<<s.first<<" "<<s.second<<"\n";

    v.clear();
    gen(n-1);
    int cnt=0;

    for (int i=0; i<q; ++i) {
        int mode=rand()%2+1;
        if (mode==2) cout<<"2 "<<rand()%n<<" "<<rand()%n<<"\n";
        else {
            if (cnt<=m-1) cout<<"1 "<<v[cnt++]<<" "<<0<<"\n";
            else cout<<"2 "<<rand()%n<<" "<<rand()%n<<"\n";
        }
    }
}
