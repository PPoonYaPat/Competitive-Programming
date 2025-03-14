#include "askask.h"
#include <bits/stdc++.h>
#include "grader.cpp"
using namespace std;

void find(int l, int r, int cnt)


vector<int> find_bombs(int N){
    vector<vector<int>> z;

    for (int i=0; i<=7; ++i) {
        vector<int> test;
        for (int j=i; j<=63; j+=8) test.push_back(j);
        z.push_back(test);
        test.clear();
    }

    for (int i=0; i<7; ++i) {
        vector<int> test;
        for (int j=i; j<=63; j+=9) test.push_back(j);
        z.push_back(test);
        test.clear();
    }

    for (int i=0; i<8; ++i) {
        vector<int> test;
        for (int j=0; j<8; ++j) test.push_back(8*i+j);
        z.push_back(test);
        test.clear();
    }

}
