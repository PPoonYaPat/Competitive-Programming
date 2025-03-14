#include "grader.h"
#include "cluedo.h"
#include <bits/stdc++.h>
using namespace std;

void Solve(){
   int cnt1=1, cnt2=1, cnt3=1;
   while (1) {
        int h=Theory(cnt1,cnt2,cnt3);
        if (h==1) ++cnt1;
        else if (h==2) ++cnt2;
        else if (h==3) ++cnt3;
        else return ;
   }
}
