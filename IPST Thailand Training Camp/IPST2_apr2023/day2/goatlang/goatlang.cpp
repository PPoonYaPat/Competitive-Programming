#include "goatlang.h"
#include <bits/stdc++.h>
//#include "grader.cpp";
using namespace std;

std::tuple<std::vector<std::vector<int>>, int, int> example1() {
  return {{{1, 0, 0}, {0, 2, 0}, {0, 0, 3}}, 2, 2};
}
std::tuple<std::vector<std::vector<int>>, int, int> example2() {
  return {{{1, 1}, {1, 0}}, 0, 1};
}

std::tuple<std::vector<std::vector<int>>, int, int> task1(std::vector<std::vector<int>> A, int r, int c) {
    int n=A.size()-1;
    const int mod=1e9+7;
    vector<vector<int>> ans;

    for (int i=0; i<=n; ++i) {
        vector<int> temp;
        for (int j=0; j<=n; ++j) temp.push_back(0);
        ans.push_back(temp);
    }

    for (int i=0; i<=n; ++i) for (int j=0; j<=n; ++j) ans[i][j]=(A[i][j]+mod)%mod;

    return {ans,r,c}; // edit this
}


std::tuple<std::vector<std::vector<int>>, int, int> task2(std::vector<std::vector<int>> H, int a, int b) {
    int n=H.size()+1;
    vector<vector<int>> ans;

    for (int i=0; i<=n; ++i) {
        vector<int> temp;
        for (int j=0; j<=n; ++j) temp.push_back(0);
        ans.push_back(temp);
    }

    for (int i=0; i<n-1; ++i) for (int j=0; j<n-1; ++j) ans[i][j]=H[i][j];
    for (int i=0; i<n-1; ++i) {
        ans[i][n-1]=H[i][b];
        ans[i][n]=H[i][b];
    }
    ans[n-1][n-1]=1;
    ans[n-1][n]=1;

    return {ans,a,n}; // edit this
}

int find(vector<int> s, int k) {
    if (s.size()==0) return 0;
    int ans=s[0],h=k;
    for (int i=1; i<s.size(); ++i) {
        ans+=h*s[i];
        h*=k;
    }
    return ans;
}

int find2(vector<int> s, int k) {
    if (s.size()==0) return 0;
    int ans=s[0];

    for (int i=1; i<s.size(); ++i) {
        int mul=s[i];
        for (int j=k-1; j>=k-i; --j) mul*=j;
        ans+=mul;
    }
    return ans;
}

std::tuple<std::vector<std::vector<int>>, int, int> task3(std::vector<int> a) {
    int n=a.size();
    vector<vector<int>> ans;

    for (int i=0; i<=n; ++i) {
        vector<int> temp;
        for (int j=0; j<=n; ++j) temp.push_back(0);
        ans.push_back(temp);
    }

    int fac[11];
    fac[0]=1;
    for (int i=1; i<11; ++i) fac[i]=fac[i-1]*i;

    int b[11];
    vector<int> temp;

    for (int i=0; i<n; ++i) {
        b[i]=(find(a,i+1)-find2(temp,i+1))/fac[i];
        temp.push_back(b[i]);
    }


    for (int i=1; i<=n; ++i) ans[i][i]=1;
    for (int i=0; i<n; ++i) ans[i][i+1]=1;
    for (int i=0; i<n; ++i) ans[i][n]=b[i]*fac[i];

    return {ans,0,n};
}


std::tuple<std::vector<std::vector<int>>, int, int> task4() {

    int n=11;
    vector<vector<int>> ans;

    for (int i=0; i<=n; ++i) {
        vector<int> temp;
        for (int j=0; j<=n; ++j) temp.push_back(0);
        ans.push_back(temp);
    }

    ans[0][1]=2;
    ans[0][6]=2;
    ans[0][7]=1;
    ans[0][9]=1;

    ans[1][1]=1;
    ans[1][2]=1;
    ans[1][3]=1;

    ans[2][1]=1;
    ans[3][4]=1;
    ans[4][5]=1;
    ans[5][1]=1;

    ans[6][1]=1;

    ans[7][8]=1;
    ans[8][1]=1;
    ans[9][10]=1;
    ans[10][11]=1;
    ans[11][1]=1;

    return {ans,0,1};
}

std::tuple<std::vector<std::vector<int>>, int, int> task5(std::vector<int> D) {
    int n=D.size();
    vector<vector<int>> ans;
    for (int i=0; i<=n; ++i) {
        vector<int> temp;
        for (int j=0; j<=n; ++j) temp.push_back(0);
        ans.push_back(temp);
    }

    for (int i=0; i<n-1; ++i) ans[i][i+1]=1;
    for (int i=0; i<n; ++i) {
        if (D[i]==1) ans[i][n]=1;
    }


    return {ans,0,n};
}


std::tuple<std::vector<std::vector<int>>, int, int> task6(int m) {
    int n=m;
    vector<vector<int>> ans;
    for (int i=0; i<=n; ++i) {
        vector<int> temp;
        for (int j=0; j<=n; ++j) temp.push_back(0);
        ans.push_back(temp);
    }

    for (int i=0; i<n; ++i) ans[i][i+1]=1;
    ans[n][1]=1;

    return {ans,0,n};
}
