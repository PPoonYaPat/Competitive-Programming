#include "spectrophotometer.h"
#include <bits/stdc++.h>
using namespace std;

int f1,f2;

void sort_lasers(int n) {
    for (int i=1; i<3*n; ++i) if (!call_swap(f1,i)) ++f1;
    for (int i=1; i<2*n; ++i) if (!call_swap(f2,i)) ++f2;
}
