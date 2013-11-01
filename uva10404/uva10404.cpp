// uva10404 dp
// 背包问题变形，有点技巧。

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
#define len 1000001
#define m_len 10
int g_m[m_len];
int f[len];
int n,m;
void dp();

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
    while (scanf("%d", &n) != EOF)
    {
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d", &g_m[i]);
        }
        dp();
        if (f[n] == 1)
            printf("Stan wins\n");
        else
            printf("Ollie wins\n");
    }
    return 0;
}

void dp()
{
    memset(f, 0, sizeof(int)*(n+1));

    for (int k = 0; k <= n; k++)
    {
        for (int i = 0; i < m; i++)
        {
            if (k - g_m[i] >= 0 && f[k - g_m[i]] != 1)
            {
                f[k] = 1;
                break;
            }
        }
    }

}