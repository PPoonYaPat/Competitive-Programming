#include "trilib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> up,down;
deque<int>  dq;

bool comp(int a, int b) {return is_clockwise(1,a,b);}

void add(int x) {
    while (dq.size()>=2 && !is_clockwise(dq[dq.size()-2],dq[dq.size()-1],x)) dq.pop_back();
    dq.push_back(x);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    n=get_n();
    for (int i=3; i<=n; ++i) {
        if (is_clockwise(1,2,i)) down.push_back(i);
        else up.push_back(i);
    }
    sort(up.begin(),up.end(),comp);
    sort(down.begin(),down.end(),comp);

    add(1);
    for (auto s : up) add(s);
    add(2);
    for (auto s : down) add(s);
    int cnt=dq.size();
    while (cnt--) {
        add(dq.front());
        dq.pop_front();
    }
    give_answer(dq.size());
}