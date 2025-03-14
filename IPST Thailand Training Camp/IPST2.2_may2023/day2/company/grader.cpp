#include <stdio.h>
#include <vector>
#include "company.h"
int main()
{
	int N,M,P;
    scanf("%d %d %d",&N,&M,&P);
    std::vector<int> C(N);
    for(int i = 0;i < N;i++)
    {
        scanf("%d",&C[i]);
    }
    std::vector<std::vector<int> > Road(M,std::vector<int> (2,0)), Group;
    for(int i = 0;i < M;i++)
    {
        scanf("%d %d",&Road[i][0],&Road[i][1]);
    }
    for(int i = 0;i < P;i++)
    {
        int P_i;
        scanf("%d",&P_i);
        std::vector<int> group(P_i);
        for(int j = 0;j < P_i;j++)
        {
            scanf("%d",&group[j]);
        }
        Group.push_back(group);
    }
    init(N,M,C,Road);
    std::vector<int> Ans = dissolve(Group);
    for(auto i:Ans)
    {
        printf("%d\n",i);
    }
}
