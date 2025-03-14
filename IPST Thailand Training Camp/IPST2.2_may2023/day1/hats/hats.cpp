#include "hats.h"
//#include "autograder.cpp"
#include <bits/stdc++.h>
using namespace std;

int think(int N, int id, vector<int> hats) {

    vector<string> v;
    int cnt[20];
    memset(cnt,0,sizeof(cnt));

    if (N==3) {
        v.push_back("111");
        v.push_back("000");
    } else {
        v.push_back("1000000");
        v.push_back("0110000");
        v.push_back("0001100");
        v.push_back("0000011");

        v.push_back("0101010");
        v.push_back("0100101");
        v.push_back("0011001");
        v.push_back("0010110");

        v.push_back("0111111");
        v.push_back("1001111");
        v.push_back("1110011");
        v.push_back("1111100");

        v.push_back("1010101");
        v.push_back("1011010");
        v.push_back("1100110");
        v.push_back("1101001");
    }

    for (int i=0; i<N; ++i) {
        if (hats[i]==-1) continue;

        for (int j=0; j<v.size(); ++j) {
            if (hats[i]==v[j][i]-'0') ++cnt[j];
        }
    }

    for (int j=0; j<v.size(); ++j) {
        if (cnt[j]==N-1) return 1-(v[j][id]-'0');
    }
    return -1;
}
