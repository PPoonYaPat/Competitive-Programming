#include "coins.h"
#include "grader.cpp"
#include <bits/stdc++.h>
using namespace std;

vector<int> coin_flips(vector<int> b, int c) {
    vector<int> ans;
    int s=0;
    for (int i=0; i<64; ++i) if (b[i]) s^=i;
    s^=c;
    ans.push_back(s);
    return ans;
}

int find_coin(vector<int> b) {
    int ans=0;
    for (int i=0; i<64; ++i) if (b[i]==1) ans^=i;
    return ans;
}
/*
3
0
11101101
01000010
01011010
11110101
11000010
01011101
01000110
10111111
7
01110010
11110101
00000100
10110001
00010111
00110101
00001110
10101110
7
10100010
01001011
10110101
10100111
00010110
01000010
00111110
01110100
*/
