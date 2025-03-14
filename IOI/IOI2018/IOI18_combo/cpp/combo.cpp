#include "combo.h"
//#include "grader.cpp";
#include <bits/stdc++.h>
using namespace std;

//int press()

string guess_sequence(int N) {
    string ans,first;

    if (press("AB")>=1) {
        if (press("A")==1) first="A";
        else first="B";
    } else {
        if (press("X")==1) first="X";
        else first="Y";
    }
    ans+=first;

    vector<string> lt; //A,B,X
    if (first!="A") lt.push_back("A");
    if (first!="B") lt.push_back("B");
    if (first!="X") lt.push_back("X");
    if (first!="Y") lt.push_back("Y");

    for (int i=1; i<N-1; ++i) {
        int cnt=press(ans+lt[0]+lt[0]+ans+lt[0]+lt[1]+ans+lt[0]+lt[2]+ans+lt[1]);
        int sz=ans.size();

        if (cnt==sz) ans+=lt[2];
        else if (cnt==sz+1) ans+=lt[1];
        else ans+=lt[0];
    }

    if (N>1) {
        if (press(ans+lt[1]+ans+lt[2])==ans.size()+1) {
            if (press(ans+lt[1])==ans.size()+1) ans+=lt[1];
            else ans+=lt[2];
        } else ans+=lt[0];
    }

    return ans;
}
