#include "supertrees.h"
#include "grader.cpp"

#include <bits/stdc++.h>
using namespace std;

int head[1001],hc[1001];
bool ans[1001][1001];
vector<int> cycle[1001];

int construct(vector<vector<int>> p) {

	int n = p.size();
	vector<vector<int>> answer;
	memset(head,-1,sizeof(head));
	memset(hc,-1,sizeof(hc));

	//create tree
	for (int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) {
            if (p[i][j]==1) {

                if (head[i]!=-1 && head[j]!=-1) {
                    if (head[i]!=head[j]) return 0;
                }
                else if (head[i]!=-1) head[j]=head[i], ans[head[i]][j]=ans[j][head[i]]=true;
                else if (head[j]!=-1) head[i]=head[j], ans[head[j]][i]=ans[i][head[j]]=true;
                else {
                    head[i]=i; head[j]=i; ans[i][j]=ans[j][i]=true;
                }
            }
        }
	}
	for (int i=0; i<n; ++i) {
        if (head[i]==-1) head[i]=i;
	}

    //create cycle
    for (int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) {
            if (p[i][j]!=1 && head[i]==head[j]) return 0;
            if (p[i][j]==2) {
                int x=head[i], y=head[j];

                if (hc[x]!=-1 && hc[y]!=-1) {
                    if (hc[x]!=hc[y]) return 0;
                }
                else if (hc[x]!=-1) hc[y]=hc[x], cycle[hc[x]].push_back(y);
                else if (hc[y]!=-1) hc[x]=hc[y], cycle[hc[y]].push_back(x);
                else {
                    hc[i]=i; hc[j]=i;
                    cycle[i].push_back(i);
                    cycle[i].push_back(j);
                }
            }
        }
	}

	for (int i=0; i<n; ++i) {
        if (cycle[i].size()) {
            for (int j=1; j<cycle[i].size(); ++j) ans[cycle[i][j]][cycle[i][j-1]]=ans[cycle[i][j-1]][cycle[i][j]]=true;
            ans[cycle[i][cycle[i].size()-1]][cycle[i][0]]=ans[cycle[i][0]][cycle[i][cycle[i].size()-1]]=true;
        }
	}

	//check component
	for (int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) {
            if (p[i][j]==3) return 0;
            if (p[i][j]==0 && hc[head[i]]==hc[head[j]] && hc[head[i]]!=-1) return 0;
        }
	}

	for (int i=0; i<n; ++i) {
        vector<int> row;
        for (int j=0; j<n; ++j) row.push_back(ans[i][j]);
        row.resize(n);
        answer.push_back(row);
    }
    build(answer);
	return 1;
}
/*
3
2 2 0
2 2 2
0 2 2

4
1 1 2 2
1 1 2 2
2 2 1 2
2 2 2 1

2
1 0
0 1

2
1 3
3 1
*/
