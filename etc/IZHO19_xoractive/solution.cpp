#include "interactive.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int st,ans[105];
map<int,int> mp;

vector<int> guess(int n) {
	st=ask(n);
	ans[n]=st;
	for (int bit=0; bit<7; ++bit) {
		vector<int> temp,res1,res2;
		for (int i=1; i<n; ++i) {
			if (i&(1<<bit)) temp.push_back(i);
		}
		if (temp.size()==0) continue;
		res1=get_pairwise_xor(temp);
		temp.push_back(n);
		res2=get_pairwise_xor(temp);

		map<int,int> cnt;
		for (auto s : res1) ++cnt[s];
		for (auto s : res2) --cnt[s];

		for (auto s : cnt) {
			if (s.first && s.second) mp[s.first^st]+=(1<<bit); 
		}
	}
	for (auto s : mp) {
		if (s.second>0) ans[s.second]=s.first;
	}

	vector<int> Ans;
	for (int i=1; i<=n; ++i) Ans.push_back(ans[i]);
	return Ans;
}
