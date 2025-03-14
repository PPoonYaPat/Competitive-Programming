#include "abc.h"
#include <bits/stdc++.h>
#include "time.h"
using namespace std;

int main() {
    srand(time(0));
    int n; //cin>>n;

    string S;
    for (int i=0; i<n; ++i) {
        int h=rand()%3;
        if (h==0) S+="a";
        else if (h==1) S+="b";
        else S+="c";
    }
    cin>>S;

    pair<int,int> ans = max_unbalance(S);
    cout << ans.first << " " << ans.second << std::endl;
}
