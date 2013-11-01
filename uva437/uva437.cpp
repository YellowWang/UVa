// uva437 dp DAG
// ʯͷ������ת������ÿ��ʯͷ�����3�̶ֹ���ʯͷ����x<y<z������Ϊ��x,y,z  x,z,y  y,z,x��
// �����n��ʯͷ����ô������3*n��ʯͷ��ʯͷi ���� ʯͷj����ô����˵�ڵ�i���Ե��ڵ�j��
// ������ÿ��·�������߶ȡ�
 
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
 
#define len 30
#define len3 90
int g_n[len3][3];
int f[len3];//�����м������
int num;
int dp(int cur);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int cases = 1;
    while (scanf("%d", &num) && num)
    {
        for (int i = 0; i < num*3; i+=3)
        {
            scanf("%d %d %d", &g_n[i][0], &g_n[i][1], &g_n[i][2]);
            // sort
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    if (g_n[i][k] > g_n[i][k+1])
                    {
                        int t = g_n[i][k];
                        g_n[i][k] = g_n[i][k+1];
                        g_n[i][k+1] = t;
                    }
                }
            }
 
            g_n[i+1][0] = g_n[i][0];
            g_n[i+1][1] = g_n[i][2];
            g_n[i+1][2] = g_n[i][1];
 
            g_n[i+2][0] = g_n[i][1];
            g_n[i+2][1] = g_n[i][2];
            g_n[i+2][2] = g_n[i][0];
        }
 
        memset(f, 0, sizeof(f));
 
        int max_height = 0;
        for (int i = 0; i < num*3; i++)
        {
            int height = dp(i);
            max_height = max(max_height, height);
        }
        printf("Case %d: maximum height = %d\n", cases, max_height);
        cases++;
    }
 
    return 0;
}
 
int dp(int cur)
{
    if (f[cur])
        return f[cur];
 
    int max_height = 0;
    int height = 0;
    for (int i = 0; i < num*3; i++)
    {
        if (g_n[cur][0] > g_n[i][0] && g_n[cur][1] > g_n[i][1])
        {
            height = dp(i);
            max_height = max(max_height, height);
        }
    }
 
    f[cur] = max_height+g_n[cur][2];
    return f[cur];
}