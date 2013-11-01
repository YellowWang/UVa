// uva674 dp
// 硬币共多少种方案 和uva147、uva357很像。
// f(i,k)，i是当前的总钱数，k是当前共有几种类型硬币。f(i,k) = f(i,k-1)+ sum(f(i-coin(k)*n, k-1))； n = [1, 无穷大] 并且 i-coin(k)*n > 0
// 举例：f(11,2) = f(11,1) + (f(11-5*1,1) + f(11-5*2,1)) = 3
 
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
 
#define len 7500
 
int f[len][6];
int visit[len][6];
int coin[6] = {0, 1, 5, 10, 25, 50};
int dp(int money, int type);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    memset(f, 0, sizeof(f));
    memset(visit, 0, sizeof(visit));
 
    int money;
    while (scanf("%d", &money)!=EOF)
    {
        printf("%d\n", dp(money, 5));
    }
 
    return 0;
}
 
int dp(int money, int type)
{
    if (type == 1)
        return 1;
 
    if (visit[money][type])
        return f[money][type];
 
    int temp_money = money;
    int ways = 0;
 
    ways += dp(money, type-1);
    for (int i = 1; ; i++)
    {
        temp_money = money - coin[type]*i;
        if (temp_money < 0)
        {
            break;
        }
        ways += dp(temp_money, type-1);
    }
 
    visit[money][type]=1;
    f[money][type]=ways;
    return ways;
}