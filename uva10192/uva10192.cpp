// uva10192 dp
// 公共最长子序列
// 注意：空格也算
 
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
 
#define len 101
char g_d1[len];
char g_d2[len];
int f[len][len];
void dp(int n1, int n2);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int cases = 1;
    while (gets(g_d1) && g_d1[0] != '#')
    {
        gets(g_d2);
 
        memset(f, 0, sizeof(f));
        int n1 = strlen(g_d1);
        int n2 = strlen(g_d2);
        dp(n1, n2);
        printf("Case #%d: you can visit at most %d cities.\n", cases, f[n1][n2]);
 
        cases++;
    }
 
    return 0;
}
 
void dp(int n1, int n2)
{
    for (int i = 0; i < n1; i++)
    {
        for (int k = 0; k < n2; k++)
        {
            if (g_d1[i] == g_d2[k])
            {
                f[i+1][k+1] = f[i][k]+1;
            }
            else
            {
                int max_sum = max(f[i+1][k], f[i][k+1]);
                f[i+1][k+1] = max(max_sum, f[i][k]);
            }
        }
    }
}