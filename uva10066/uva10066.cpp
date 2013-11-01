// uva10066 dp
// 公共最长子序列
 
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
int g_d1[len];
int g_d2[len];
int f[len][len];
void dp(int n1, int n2);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int n1, n2;
    int cases = 1;
    while (scanf("%d %d", &n1, &n2) && n1)
    {
        for (int i = 0; i < n1; i++)
        {
            scanf("%d", &g_d1[i]);
        }
        for (int i = 0; i < n2; i++)
        {
            scanf("%d", &g_d2[i]);
        }
 
        memset(f, 0, sizeof(f));
 
        dp(n1, n2);
        printf("Twin Towers #%d\n", cases);
        printf("Number of Tiles : %d\n", f[n1][n2]);
 
        printf("\n");
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