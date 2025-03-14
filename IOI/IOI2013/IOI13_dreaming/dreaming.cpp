#include "dreaming.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

int dis_min,mmax1[100001],mmax2[100001],mnode[100001],ans;
bool vis[100001];
vector<pii> adj[100001];
vector<int> v;

void dfs1(int x, int par, int root) {
    vis[x]=true;
    for (auto s : adj[x]) {
        if (s.first==par) continue;
        dfs1(s.first,x,root);
        int dis=mmax1[s.first]+s.second;

        if (mmax1[x]<=dis) {
            mmax2[x]=mmax1[x];
            mmax1[x]=dis;
            mnode[x]=s.first;
        } else if (mmax2[x]<dis) mmax2[x]=dis;
    }
}

void dfs2(int x, int par, int dis) {
    dis_min=min(dis_min,max(mmax1[x],dis));

    ans=max({ans,mmax1[x]+mmax2[x],mmax1[x]+dis,mmax2[x]+dis});

    for (auto s : adj[x]) {
        if (s.first==par) continue;
        if (s.first==mnode[x]) dfs2(s.first,x,max(dis,mmax2[x])+s.second);
        else dfs2(s.first,x,max(dis,mmax1[x])+s.second);
    }
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    for (int i=0; i<M; ++i) {
        adj[A[i]].push_back(pii(B[i],T[i]));
        adj[B[i]].push_back(pii(A[i],T[i]));
    }
    for (int i=1; i<=N; ++i) {
        if (!vis[i]) {
            dfs1(i,-1,i);
            dis_min=mmax1[i];

            for (auto s : adj[i]) {
                if (s.first==mnode[i]) dfs2(mnode[i],i,mmax2[i]+s.second);
            }
            v.push_back(dis_min);
        }
    }

    sort(v.begin(),v.end(),greater<int>());
    if (v.size()==1) return max(ans,v[0]);
    else if (v.size()==2) return max(ans,v[0]+v[1]+L);
    return max({ans,v[0]+v[1]+L,v[1]+v[2]+2*L});
}

int a[1000000],b[1000000],c[1000000];

int main() {
    int n,m,k;
    cin>>n>>m>>k;
    for (int i=0; i<m; ++i) cin>>a[i]>>b[i]>>c[i];
    cout<<travelTime(n,m,k,a,b,c);
}
/*
12 8 2
0 8 4
8 2 2
2 7 4
5 11 3
5 1 7
1 3 1
1 9 5
10 6 3

13 11 4
1 2 9
2 5 8
2 4 5
2 6 6
2 3 4
6 7 2
3 8 3
9 10 8
10 12 6
10 11 2
11 13 12

100 5 10000
95 73 1667
98 34 3851
64 7 2414
49 55 7129
52 43 4781

100 98 1
43 79 282
31 57 4
1 42 1
33 52 2
25 93 1
30 94 1
15 81 2
30 67 2
23 10 4
31 32 1
56 1 1
97 53 5
71 87 2
17 76 4
65 45 3
86 37 3
86 12 2
85 96 1
71 66 2
73 98 5
78 97 3
43 74 1
21 68 5
23 6 5
35 9 1
38 58 2
72 92 1
12 4 5
70 15 2
7 64 5
28 70 2
48 28 5
22 3 2
41 66 5
18 27 4
67 91 4
11 91 3
40 84 4
80 13 5
21 6 1
11 14 5
26 50 3
8 99 2
22 5 1
40 73 5
46 38 4
40 69 2
62 8 1
60 83 1
24 44 2
89 17 3
7 25 3
47 36 2
65 62 2
82 5 4
18 49 4
47 88 1
65 0 3
77 24 3
0 59 2
35 21 1
46 69 3
75 61 1
78 56 2
26 95 2
7 29 2
39 20 2
82 72 3
39 77 3
74 88 4
60 55 3
59 49 1
35 49 3
78 46 2
4 72 1
4 97 1
85 14 5
39 90 5
12 16 4
9 90 3
41 2 4
75 63 1
80 2 1
63 80 1
54 29 2
95 85 3
74 34 3
34 54 4
48 90 5
63 48 5
54 33 4
95 89 5
33 89 1
16 55 1
75 55 3
32 51 5
51 60 3
51 17 4
*/
