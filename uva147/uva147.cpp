// uva147 dp
// 硬币共多少种方案 和uva674、uva357很像
// 注意，数字很大，用long long。输入的小数部分用整型代替，不然精度缺失。
 
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
 
#define len 30005
long long f[len][12];
int visit[len][12];
int coin[12] = {0, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
long long dp(int money, int type);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int money_1, money_2;
    while (scanf("%d.%d", &money_1, &money_2) && (money_1 || money_2))
    {
        int money = money_1 * 100 + money_2;
 
        printf("%3d.%.2d%17lld\n", money_1, money_2, dp(money, 11));
    }
 
    return 0;
}
 
long long dp(int money, int type)
{
    if (type == 1)
        return 1;
 
    if (visit[money][type])
        return f[money][type];
 
    int temp_money = money;
    long long ways = 0;
 
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