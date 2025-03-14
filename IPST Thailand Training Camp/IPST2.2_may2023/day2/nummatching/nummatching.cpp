#include "nummatching.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int num,n,val[1001];
vector<vector<int>> ans;
vector<int> pos;
queue<int> q;
bool mark[1001];

void solve() {
    vector<int> temp;
    for (int i=0; i<n; ++i) if (!mark[i]) temp.push_back(i);

    int m=temp.size();
    if (m==0) return;

    if (!can_match(temp)) {

        for (auto s : temp) {
            vector<int> k;
            k.push_back(q.front()); q.pop();
            k.push_back(s);
            ans.push_back(k);
        }

        while (!q.empty()) {
            vector<int> k;
            k.push_back(q.front()); q.pop();
            k.push_back(q.front()); q.pop();
            ans.push_back(k);
        }

    } else {
        int l=0, r=m-1;
        while (l<r) {
            int mid=(l+r+1)/2;

            vector<int> h;
            for (int i=0; i<=mid; ++i) h.push_back(temp[i]);

            if (can_match(h)) r=mid-1;
            else l=mid;
        }

        int ed=l+1;
        l=0; r=ed;
        while (l<r) {
            int mid=(l+r)/2;

            vector<int> h;
            for (int i=mid; i<=ed; ++i) h.push_back(temp[i]);

            if (can_match(h)) l=mid+1;
            else r=mid;
        }
        int st=l-1;

        mark[temp[st]]=true;
        mark[temp[ed]]=true;

        vector<int> k;
        k.push_back(temp[st]);
        k.push_back(temp[ed]);
        ans.push_back(k);

        solve();
    }
}

vector<vector<int>> find_matching(int N) {
    n=N;

    for (int i=0; i<n-1; ++i) {
        vector<int> temp;
        temp.push_back(i);
        temp.push_back(i+1);
        val[i]=can_match(temp);
    }

    for (int i=0; i<n; ++i) {
        if (i==0) {
            if (!val[i]) num=i;
        } else {
            if (!val[i] && !val[i-1]) num=i;
        }
    }

    for (int i=0; i<n; ++i) {
        if (i==num) continue;

        vector<int> temp;
        temp.push_back(i);
        temp.push_back(num);
        if (can_match(temp)) pos.push_back(i);
    }

    for (auto s : pos) mark[s]=true;

    int another_num;
    for (int i=0; i<n; ++i) if (i!=num && !mark[i]) another_num=i;

    for (auto s : pos) { //check whether s is 0 of not
        vector<int> temp;
        temp.push_back(s);
        temp.push_back(another_num);
        if (!can_match(temp)) mark[s]=false;
    }

    for (int i=0; i<n; ++i) if (mark[i]) q.push(i);

    solve();

    return ans;

}
