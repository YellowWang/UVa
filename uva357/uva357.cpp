// uva357 dp
// 硬币共多少种方案 和uva674、uva147很像
// 这里用更快速递推方法
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <queue> 
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;
 
#define len 32005
long long f[len];
int coin[5] = {1,5,10,25,50};
 
void dp();
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    dp();
 
    int money;
    while (scanf("%d", &money)!=EOF)
    {
        if (f[money] == 1)
            printf("There is only 1 way to produce %d cents change.\n", money);
        else
            printf("There are %lld ways to produce %d cents change.\n", f[money], money);
    }
 
    return 0;
}
 
void dp()
{
    f[0]=1;
    for (int i = 0; i < 5; i++)
    {
        for (int k = coin[i]; k < len; k++)
        {
            f[k] += f[k - coin[i]];
        }
    }
}