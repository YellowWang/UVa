// uva10405 dp ƥ���������
// ״̬ת�ƣ�if str[i] == str[k] then f(i+1,k+1) = f(i,k)+1; else f(i+1,k+1) = max{f(i,k), f(i+1,k), f(i,k+1)};
// �ҵ�һ�εĴ��󷽷����ӵ�һ���ַ����ĵ�һ���ַ���ʼ���ڵڶ����ַ������ң��õ��ڵڶ����ַ�����λ�ã�Ȼ��������ַ���1����һ���ַ���
// ����һ�а��ã�֪�������������
//131
//31
// ����Ľ��Ϊ1����ȷ��2.
 
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