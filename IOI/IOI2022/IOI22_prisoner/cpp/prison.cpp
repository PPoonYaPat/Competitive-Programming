#include "prison.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

vector<int> v[5001];
int s[5001][5001];
vector<int> a={3,3,3,3,3,2,2,1};

void trans(int x, int l, int r, int cnt) {
    if (x==l) v[x].push_back(-1);
    else if (x==r) v[x].push_back(-2);
    else {
        int par=(r-l-1)/a[cnt];
        if (x<=l+par) {
            v[x].push_back(1);
            trans(x,l+1,l+par,cnt+1);
        } else if (x<=l+2*par) {
            v[x].push_back(2);
            trans(x,l+par+1,l+2*par,cnt+1);
        } else {
            v[x].push_back(3);
            trans(x,l+2*par+1,r-1,cnt+1);
        }
    }
}

vector<vector<int>> devise_strategy(int n) {
    for (int i=1; i<=n; ++i) trans(i,1,5588,0);

    s[0][0]=1; //look at B
    for (int i=1; i<=n; ++i) {
        if (v[i][0]==-1) s[0][i]=-2;
        else if (v[i][0]==-2) s[0][i]=-1;
        else s[0][i]=v[i][0];
    }

    int idx=0;
    for (int k=0; k<a.size(); ++k) {
        for (int i=idx+1; i<=idx+a[k]; ++i) {

            s[i][0]=k%2;

            //read i -> range i-idx
            for (int j=1; j<=n; ++j) {
                //open bag then see j

                if (v[j].size()<k+1) s[i][j]=0;
                else if (v[j][k]==-1 || (v[j][k]<i-idx && v[j][k]>0)) {
                    if (k%2==0) s[i][j]=-1;
                    else s[i][j]=-2;

                } else if (v[j][k]==-2 || (v[j][k]>i-idx && v[j][k]>0)) {

                    if (k%2==0) s[i][j]=-2;
                    else s[i][j]=-1;

                } else { //v[j][k]==i-idx

                    if (v[j][k+1]==-1) {
                        if (k%2==0) s[i][j]=-1;
                        else s[i][j]=-2;

                    } else if (v[j][k+1]==-2) {
                        if (k%2==0) s[i][j]=-2;
                        else s[i][j]=-1;

                    } else s[i][j]=v[j][k+1]+idx+a[k];

                }
            }

        }
        idx+=a[k];
    }

    vector<vector<int>> ans;
    for (int i=0; i<=20; ++i) {
        vector<int> temp;
        for (int j=0; j<=n; ++j) temp.push_back(s[i][j]);
        ans.push_back(temp);
    }
    return ans;
}
/*
int main() {
    devise_strategy(250);

    for (auto x : v[5]) cout<<x<<" ";
    cout<<"\n";
    for (auto x : v[209]) cout<<x<<" ";
    cout<<"\n\n";

    cout<<s[10][209];
    //cout<<s[7][5];
} */

/*
3
1 2
1 3
2 1
2 3
3 1
3 2
-1

3
3 2
-1
*/
