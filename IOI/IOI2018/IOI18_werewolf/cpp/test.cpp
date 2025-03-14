#include <bits/stdc++.h>
#include <time.h>
using namespace std;

vector<int> ans,temp;
int n,m,q;

int main() {
    srand(time(0));

    freopen("in.txt","w",stdout);

    n=10;
    m=15;
    q=40;
    cout<<n<<" "<<m<<" "<<q<<"\n";
    m-=(n-1);

    for (int i=0; i<n; ++i) temp.push_back(i);

    for (int i=0; i<n; ++i) {
        int k=0;
        if (i!=n-1) k=rand()%(n-i-1);
        ans.push_back(temp[k]);
        swap(temp[k],temp[n-i-1]);
    }

    cout<<ans[0]<<" "<<ans[1]<<"\n";
    for (int i=2; i<ans.size(); ++i) cout<<ans[rand()%i]<<" "<<ans[i]<<"\n";
    for (int i=0; i<m; ++i) cout<<rand()%n<<" "<<rand()%n<<"\n";
    for (int i=0; i<q; ++i) cout<<rand()%n<<" "<<rand()%n<<" "<<rand()%n<<" "<<rand()%n<<"\n";
}
