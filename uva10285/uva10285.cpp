// uva10285 dp
// 图4方向寻路，只要比所在区域地势低，就可以过去。每个地如果搜索过，那么就保存起来，如在遇到不用重复计算。
 
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
 
#define len 100
int g_n[len][len];
int f[len][len];
int rows,cols;
char name[64];
 
int dp(int i, int k);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        scanf("%s %d %d", name, &rows, &cols);
        for (int i = 0; i < rows; i++)
        {
            for (int k = 0; k < cols; k++)
            {
                scanf("%d", &g_n[i][k]);
            }
        }
 
        memset(f, 0, sizeof(f));
 
        int max_runs = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int k = 0; k < cols; k++)
            {
                int runs = dp(i,k);
                max_runs = max(max_runs, runs);
            }
        }
        printf("%s: %d\n", name, max_runs);
    }
 
    return 0;
}
 
int dir[8]={0,-1, -1,0, 0,1, 1,0};
 
int dp(int i, int k)
{
    if (f[i][k])
        return f[i][k];
 
    int runs = 0, max_runs = 1;
    int newi,newk;
 
    for (int d = 0; d < 4; d++)
    {
        newi = i+dir[d+d]; newk = k+dir[d+d+1];
        if (newi >= 0 && newi < rows && newk >= 0 && newk < cols
            && g_n[i][k] > g_n[newi][newk])
        {
            runs = dp(newi, newk)+1;
            max_runs = max(runs, max_runs);
        }
    }
 
    f[i][k]=max_runs;
    return max_runs;
}