// uva111 dp 最长公共子序列
// 重点在理解题意。首先把序列转换为按照时间为顺序。
// 题意参考：http://www.cnblogs.com/yuzhaoxin/archive/2012/03/06/2382109.html
// 不过我用的是保存中间分数的方法。
 
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
 
#define len 21
int g_n[len];
int g_student[len];
int g_score[len];
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int n;
    scanf("%d", &n);
 
    for (int i = 1; i <= n; i++)
    {
        int num;
        scanf("%d", &num);
        g_n[i]=num;
    }
 
    int temp;
    while (scanf("%d", &temp)!=EOF)
    {
        g_student[temp] = 1;
        g_score[1]=0;
        for (int i = 2; i <= n; i++)
        {
            scanf("%d", &temp);
            g_student[temp] = i;
            g_score[i]=0;
        }
 
        int max_score=1;
        for (int i = 1; i <= n; i++)
        {
            int score = 0;
            for (int k = 1; k < i; k++)
            {
                if (g_n[g_student[i]] > g_n[g_student[k]] && score < g_score[k])
                {
                    score = g_score[k];
                }
            }
            g_score[i] = score+1;
            if (max_score < g_score[i])
                max_score = g_score[i];
        }
 
        printf("%d\n", max_score);
    }
 
    return 0;
}
 