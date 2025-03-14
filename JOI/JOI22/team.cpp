#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int n,a[150001],b[150001],c[150001];
multiset<int, greater<int>> ms[3];
map<pii,vector<int>> mp[3];
bool del[150001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=0; i<n; ++i) {
        cin>>a[i]>>b[i]>>c[i];
        ms[0].insert(a[i]);
        ms[1].insert(b[i]);
        ms[2].insert(c[i]);
        mp[0][pii(a[i],b[i])].push_back(i);
        mp[1][pii(b[i],c[i])].push_back(i);
        mp[2][pii(c[i],a[i])].push_back(i);
    }

    while (true) {

        int A=*(ms[0].begin()), B=*(ms[1].begin()), C=*(ms[2].begin());

        vector<int> temp;
        for (auto s : mp[0][pii(A,B)]) if (!del[s]) temp.push_back(s);
        for (auto s : mp[1][pii(B,C)]) if (!del[s]) temp.push_back(s);
        for (auto s : mp[2][pii(C,A)]) if (!del[s]) temp.push_back(s);

        if (temp.size()==0) {
            cout<<A+B+C;
            return 0;
        }

        for (auto s : temp) {
            if (del[s]) continue;
            del[s]=true;
            ms[0].erase(ms[0].find(a[s]));
            ms[1].erase(ms[1].find(b[s]));
            ms[2].erase(ms[2].find(c[s]));
        }

        if (ms[0].size()==0 || ms[1].size()==0 || ms[2].size()==0) break;
    }
    cout<<-1;
}