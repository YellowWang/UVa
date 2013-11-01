// uva531 dp
// 最长公共子序列。需要递归打印路径。
 
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
 
#define word_len 31
#define len 101
char g_words1[len][word_len];
char g_words2[len][word_len];
int f[len][len];
int road[len][len]; // road 记录路径
void dp(int n1, int n2);
void output(int i, int k, deque<int>& q);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    while (scanf("%s", g_words1[0])!=EOF)
    {
        int n1 = 1;
        while (scanf("%s", g_words1[n1]) && g_words1[n1][0] != '#')
        {
            n1++;
        }
 
        int n2 = 0;
        while (scanf("%s", g_words2[n2]) && g_words2[n2][0] != '#')
        {
            n2++;
        }
 
        dp(n1, n2);
 
        deque<int> q;
        output(n1, n2, q);
        printf("%s", g_words1[q[0]]);
        for (int i = 1; i < q.size(); i++)
        {
            printf(" %s", g_words1[q[i]]);
        }
        printf("\n");
    }
 
    return 0;
}
 
void output(int i, int k, deque<int>& q)
{
    if (i < 0 || k < 0)
        return;
 
    if (road[i][k] == 3)
    {
        output(i-1, k-1, q);
        q.push_back(i-1);
    }
    else if (road[i][k] == 2)
    {
        output(i, k-1, q);
    }
    else if (road[i][k] == 1)
    {
        output(i-1, k, q);
    }
    else
    {
        output(i-1, k-1, q);
    }
}
 
void dp(int n1, int n2)
{
    memset(f, 0, sizeof(f));
 
    for (int i = 0; i < n1; i++)
    {
        for (int k = 0; k < n2; k++)
        {
            if (strcmp(g_words1[i], g_words2[k])==0)
            {
                f[i+1][k+1] = f[i][k]+1;
                road[i+1][k+1] = 3; // 只有这种情况需要打印
            }
            else
            {
                int max_sum = f[i+1][k];
                road[i+1][k+1] = 2;
                if (max_sum < f[i][k+1])
                {
                    max_sum = f[i][k+1];
                    road[i+1][k+1] = 1;
                }
                if (max_sum < f[i][k])
                {
                    max_sum = f[i][k];
                    road[i+1][k+1] = 0;
                }
                f[i+1][k+1] = max_sum;
            }
        }
    }
}