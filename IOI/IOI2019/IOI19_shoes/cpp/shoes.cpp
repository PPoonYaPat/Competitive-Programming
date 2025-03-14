#include "shoes.h"
//#include "grader.cpp"

#include <bits/stdc++.h>
using namespace std;

queue<int> v[200001];
long long fen[200001];
bool gone[200001];

long long find(int x) {
    if (x==0) return 0;
    long long sum=0;
    while (x) {
        sum+=fen[x];
        x-=(x&-x);
    }
    return sum;
}

void update(int x) {
    while (x<=200000) {
        ++fen[x];
        x+=(x&-x);
    }
}

long long count_swaps(vector<int> s) {
    int n=s.size()/2;
    long long ans=0;

    for (int i=0; i<2*n; ++i) {
        if (s[i]>0) v[s[i]].push(i+1);
        else v[abs(s[i])+n].push(i+1);
    }

    for (int i=0; i<2*n; ++i) {
        if (gone[i+1]) continue;

        //consider at position i+1

        if (s[i]<0) {
            int j=v[abs(s[i])].front();
            v[abs(s[i])].pop();
            v[abs(s[i])+n].pop();

            ans+=(j-i-2-find(j)+find(i));

            gone[j]=true;
            update(j);

        } else {
            int j=v[s[i]+n].front();
            v[s[i]+n].pop();
            v[s[i]].pop();

            ans+=(j-i-1-find(j)+find(i));

            gone[j]=true;
            update(j);
        }
    }

	return ans;
}
