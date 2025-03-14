#include "friend.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

int c[100001],nc[100001];

int findSample(int n, int confidence[], int host[], int protocol[]){
    for (int i=0; i<n; ++i) c[i]=confidence[i];
    for (int i=n-1; i>0; --i) {
        if (protocol[i]==0) {
            c[host[i]]+=nc[i];
            nc[host[i]]+=max(c[i],nc[i]);
        } else if (protocol[i]==1) {
            c[host[i]]=max({c[host[i]]+c[i],nc[host[i]]+c[i],c[host[i]]+nc[i]});
            nc[host[i]]+=nc[i];
        } else {
            c[host[i]]=max(c[host[i]]+nc[i],nc[host[i]]+c[i]);
            nc[host[i]]+=nc[i];
        }
    }
    return max(c[0],nc[0]);
}
