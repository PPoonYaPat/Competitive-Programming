#include "rect.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

struct rect {
	int l,r,d;
};

bool comp1(rect a, rect b) {return a.l<b.l;}
struct comp2 {
	bool operator() (rect const &a, rect const &b) {
		return a.r>b.r;
	}
};

int n,m,c[2505][2505],cnt;
vector<rect> rec1[2505],rec2[2505];

int st[2505][2505];
vector<pii> temp;

int fen[2510];

int find(int x) {
	int sum=0;
	while (x) {
		sum+=fen[x];
		x-=x&-x;
	}
	return sum;
}

void update(int x, int val) {
	while (x<=2505) {
		fen[x]+=val;
		x+=x&-x;
	}
}

long long count_rectangles(vector<vector<int>> a) {
	n=a.size();
	m=a[0].size();

	for (int i=0; i<n; ++i) {
		for (int j=0; j<m; ++j) {
			c[i][j]=a[i][j];
		}
	}

	memset(st,-1,sizeof(st));
	for (int i=1; i<n-1; ++i) {
		int bef[2505],aft[2505];
		vector<pii> temp2;
		map<pii,bool> mp;

		for (int j=0; j<m; ++j) {
			int idx=j-1;
			while (idx!=-1 && c[i][idx]<c[i][j]) idx=bef[idx];
			bef[j]=idx;

			if (bef[j]!=-1 && bef[j]<=j-2 && !mp[pii(bef[j]+1,j-1)]) temp2.push_back(pii(bef[j]+1,j-1)), mp[pii(bef[j]+1,j-1)]=true;
		}

		for (int j=m-1; j>=0; --j) {
			int idx=j+1;
			while (idx!=m && c[i][idx]<c[i][j]) idx=aft[idx];
			aft[j]=idx;

			if (aft[j]!=m && aft[j]>=j+2 && !mp[pii(j+1,aft[j]-1)]) temp2.push_back(pii(j+1,aft[j]-1)), mp[pii(j+1,aft[j]-1)]=true;
		}

		for (auto s : temp2) {
			if (st[s.first][s.second]==-1) {
				st[s.first][s.second]=i;
			}
		}
		
		for (auto s : temp) {
			if (!mp[s]) {
				rec1[st[s.first][s.second]].push_back({s.first,s.second,i-1});
				st[s.first][s.second]=-1;
			}
		}

		swap(temp,temp2);
	}
	for (auto s : temp) rec1[st[s.first][s.second]].push_back({s.first,s.second,n-2});
	temp.clear();

	memset(st,-1,sizeof(st));
	for (int j=1; j<m-1; ++j) {
		int bef[2505],aft[2505];
		vector<pii> temp2;
		map<pii,bool> mp;

		for (int i=0; i<n; ++i) {
			int idx=i-1;
			while (idx!=-1 && c[idx][j]<c[i][j]) idx=bef[idx];
			bef[i]=idx;

			if (bef[i]!=-1 && bef[i]<=i-2 && !mp[pii(bef[i]+1,i-1)]) temp2.push_back(pii(bef[i]+1,i-1)), mp[pii(bef[i]+1,i-1)]=true;
		}

		for (int i=n-1; i>=0; --i) {
			int idx=i+1;
			while (idx!=n && c[idx][j]<c[i][j]) idx=aft[idx];
			aft[i]=idx;

			if (aft[i]!=n && aft[i]>=i+2 && !mp[pii(i+1,aft[i]-1)]) temp2.push_back(pii(i+1,aft[i]-1)), mp[pii(i+1,aft[i]-1)]=true;
		}

		for (auto s : temp2) {
			if (st[s.first][s.second]==-1) {
				st[s.first][s.second]=j;
			}
		}

		for (auto s : temp) {
			if (!mp[s]) {
				rec2[s.first].push_back({st[s.first][s.second],j-1,s.second});
				st[s.first][s.second]=-1;
			}
		}

		swap(temp,temp2);
	}
	for (auto s : temp) rec2[s.first].push_back({st[s.first][s.second],m-2,s.second});
	temp.clear();

	for (int i=0; i<n; ++i) {
		sort(rec1[i].begin(),rec1[i].end(),comp1);
		sort(rec2[i].begin(),rec2[i].end(),comp1);
		priority_queue<rect, vector<rect>, comp2> q;
		memset(fen,0,sizeof(fen));

		int idx=0;
		
	}

	return cnt;
}
