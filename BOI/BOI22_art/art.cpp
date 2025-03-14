#include "art.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

//
// --- Sample implementation for the task art ---
//
// To compile this program with the sample grader, place:
//     art.h art_sample.cpp sample_grader.cpp
// in a single folder, then open the terminal in this directory (right-click onto an empty spot in the directory,
// left click on "Open in terminal") and enter e.g.:
//     g++ -std=c++17 art_sample.cpp sample_grader.cpp
// in this folder. This will create a file a.out in the current directory which you can execute from the terminal
// as ./a.out
// See task statement or sample_grader.cpp for the input specification
//

void solve(int n) {
    vector<int> v,temp;
    v.push_back(n);

    for (int i=1; i<=n; ++i) temp.push_back(i);
    int pre=publish(temp),now,c=0;


    for (int i=n-1; i>=1; --i) {
        swap(temp[i-1],temp[n-1]);
        now=publish(temp);
        int x=(now-pre+2*c+1)/2;

        vector<int> h;
        if (x==0) h.push_back(i);
        for (int j=0; j<v.size(); ++j) {
            h.push_back(v[j]);
            if (j==x-1) h.push_back(i);
        }

        swap(h,v);
        swap(pre,now);
        c=x;
    }

    reverse(v.begin(),v.end());
    answer(v);
}
