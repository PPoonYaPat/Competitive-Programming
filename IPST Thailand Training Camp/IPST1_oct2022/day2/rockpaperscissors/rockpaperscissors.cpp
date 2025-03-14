#include "rockpaperscissors.h"
//#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;


int find_cheater1(int n){
    int l=1, r=3*n;

    if (n<=3) {
        for (int i=1; i<=3*n; ++i) {
            vector<int> test;

            for (int j=0; j<=3*n; ++j) if (j!=i) test.push_back(j);

            if (tournament(test)!=test.size()-1) return i;
        }
    }

    while (l<r) {
        vector<int> test;
        int mid=(l+r)/2;

        for (int i=1; i<=3*n; ++i) {
            if (i<l || i>mid) test.push_back(i);
        }

        int w=tournament(test);

        if (w==test.size()-1) l=mid+1;
        else r=mid;

        test.clear();
    }

    return l;
}

queue<vector<int>> q;
vector<int> pre,ans;

int find_cheater2(int n){

    if (n<=10) return find_cheater1(n);

    while (!q.empty()) q.pop();
    pre.clear();
    ans.clear();

    for (int i=0; i<n; ++i) {
        vector<int> temp;
        temp.push_back(3*i+1);
        temp.push_back(3*i+2);
        temp.push_back(3*i+3);
        int k=tournament(temp);
        if (k==2) q.push(temp);
        if (k==1 && pre.size()==0) pre=temp;
    }

    while (!q.empty()) {
        if (q.size()>=2) {
            vector<int> a=q.front(); q.pop();
            vector<int> b=q.front(); q.pop();
            vector<int> temp;
            for (auto s : a) temp.push_back(s);
            for (auto s : b) temp.push_back(s);


            int k=tournament(temp);
            if (k==5) {
                ans=temp;
                break;
            }
            if (k && k<=4 && pre.size()==0) pre=temp;
        } else {
            ans=q.front(); q.pop();
        }
    }

    pre.push_back(0);
    for (auto s : ans) {
        pre[pre.size()-1]=s;
        if (tournament(pre)==pre.size()-1) return s;
    }
}
/*
1
3 1
1 2 0 3 3 2 1 3 2 1
*/
