#include "citymapping.h"
#include "grader.cpp"

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pii;
typedef tuple<int,int,int> t;

int n;
vector<int> v[1001];
vector<t> ans;
ll dis[1001][1001];

ll get(int  x, int y) {
    if (!dis[x][y]) dis[x][y]=dis[y][x]=get_distance(x,y);
    return dis[x][y];
}

void find(int x) {
    int r,l;
    ll longest=0;
    vector<pii> temp; //dis and node in backbone
    vector<int> tree;

    v[x].push_back(x);
    for (auto s : v[x]) if (get(x,s)>longest) longest=get(x,s), r=s;
    longest=0;
    for (auto s : v[x]) if (get(r,s)>longest) longest=get(r,s), l=s;
    for (auto s : v[x]) {
        if (r==s) continue;
        if (get(r,s)+get(s,l)==get(r,l)) temp.push_back(pii(get(r,s),s));
        else tree.push_back(s);
    }

    sort(temp.begin(),temp.end());
    ans.push_back(t(r,temp[0].second,temp[0].first));

    for (int i=1; i<temp.size(); ++i) {
        ans.push_back(t(temp[i-1].second,temp[i].second,temp[i].first-temp[i-1].first));
    }
    v[x].clear();
    for (auto s : tree) {
        for (auto b : temp) {
            if (dis[r][s]-(dis[r][s]+dis[s][l]-dis[r][l])/2==b.first) {
                v[b.second].push_back(s);
                dis[b.second][s]=dis[s][b.second]=(dis[r][s]+dis[s][l]-dis[r][l])/2;
                break;
            }
        }
    }

    for (auto s : temp) if (v[s.second].size()) find(s.second);
}

void find_roads(int N, int Q, int A[], int B[], int W[]) {
    n=N;
    for (int i=2; i<=n; ++i) v[1].push_back(i);
    find(1);

    for (int i=0; i<ans.size(); ++i) tie(A[i],B[i],W[i])=ans[i];
	return;
}
/*
5 500000 1
4 5 1
1 2 1
2 3 1
3 4 1

10 500000 2
1 4 678352431
4 2 867263542
3 4 986735463
5 3 564837284
6 2 103434343
6 7 127684574
8 1 765787345
1 9 578493867
2 10 678587475

10 500000 2
1 4 8
4 2 1
3 4 7
5 3 3
6 2 10
6 7 12
8 1 7
1 9 12
2 10 3

15 500000 2
1 4 8
4 2 1
3 4 7
5 3 3
6 2 10
6 7 12
8 1 7
1 9 12
2 10 3
11 12 13
12 14 14
8 13 15
15 3 10
13 12 10

15 500000 2
10 11 345
5 11 45
11 7 77
10 15 34
15 9 543
8 9 657
13 9 987
15 12 3422
12 14 546
14 6 666
14 1 333
12 2 444
2 3 222
2 4 333
*/
