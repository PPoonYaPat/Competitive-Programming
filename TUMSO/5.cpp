#include <bits/stdc++.h>
using namespace std;

int main() {
    int ax,ay,bx,by,n;
    cin>>n>>ax>>ay>>bx>>by;
    if (ax==bx && ay==by-1) cout<<0;
    else if (ax==bx && ay==by+1) cout<<0;
    else if (ax==bx+1 && ay==by) cout<<bx-by+bx;
    else if (ax==bx+1 && ay==by+1) cout<<bx+by-1;
    else if (ax==bx-1 && ay==by-1) cout<<n-bx+n-by+1;
    else if (ax==bx-1 && ay==by) cout<<n-bx+by;
}
