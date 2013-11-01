// uva10405 dp 匹配最长子序列
// 状态转移：if str[i] == str[k] then f(i+1,k+1) = f(i,k)+1; else f(i+1,k+1) = max{f(i,k), f(i+1,k), f(i,k+1)};
// 我第一次的错误方法：从第一个字符串的第一个字符开始，在第二个字符串查找，得到在第二个字符串的位置，然后继续找字符串1的下一个字符。
// 本来一切安好，知道遇到了这个：
//131
//31
// 错误的结果为1，正确是2.
 
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
 
#define len 1010
char* g_str1;
char* g_str2;
int f[len][len];
void dp(int n1, int n2);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    char str1[len],str2[len];
    while (gets(str1))
    {
        gets(str2);
 
        g_str1 = str1;
        g_str2 = str2;
        int n1 = strlen(str1);
        int n2 = strlen(str2);
 
        memset(f, 0, sizeof(f));
 
        dp(n1, n2);
        printf("%d\n", f[n1][n2]);
    }
 
    return 0;
}
 
void dp(int n1, int n2)
{
    for (int i = 0; i < n1; i++)
    {
        for (int k = 0; k < n2; k++)
        {
            if (g_str1[i] == g_str2[k])
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