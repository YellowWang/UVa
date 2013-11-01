// uva216 ����
// ��Ϊn<=8�����Կ����ñ�����
// ������һ���򵥵�ö���⣬���������������⡣
/* ����1����Ĭ�ϰѵ�һ���������Ϊ��ʼ�㣬������ò�����С�������ʼ������������㡣
*  ����2�������ǵľ����������ߵĵ�ƽ���ͣ��������ʹ��һֱWA����Ӧ�úͿ�������һһ��Ӧ�ģ����ǽ�����Ǵ���û�취�͸ĳ��˿����汾��
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;

#define len 10
struct node
{
    int x,y;
};
node g_d[len];
int visit[len];
int pre[len];

int g_pre[len];
int num;
float g_min;
// �����Ĭ�ϵ�һ��ֵ����Ϊ��ʼ��
void dfs(int idx, int cur, int* visit, int* pre, int distance);
// �����汾
void dfs2(int idx, int cur, int* visit, int* pre, float distance);
// �������
float calc_dis(int idx1, int idx2);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases = 1;
    while (scanf("%d", &num) && num)
    {
        memset(visit, 0, sizeof(visit));
        memset(pre, 0, sizeof(pre));
        g_min = 100000000;

        int x,y;
        for (int i = 0; i < num; i++)
        {
            scanf("%d %d", &g_d[i].x, &g_d[i].y);
        }

        dfs2(0, 0, visit, pre, 0);

        printf("**********************************************************\n");
        printf("Network #%d\n",cases++);
        float totoal = 0.0f;
        for (int i = 0; i < num-1; i++)
        {
            float dis = calc_dis(g_pre[i], g_pre[i+1])+16.00f;
            printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
                g_d[g_pre[i]].x,g_d[g_pre[i]].y,
                g_d[g_pre[i+1]].x,g_d[g_pre[i+1]].y,
                dis);
            totoal += dis;
        }
        printf("Number of feet of cable required is %.2f.\n", totoal);
    }

    return 0;
}

float calc_dis(int idx1, int idx2)
{
    int x = g_d[idx1].x-g_d[idx2].x;
    int y = g_d[idx1].y-g_d[idx2].y;
    return sqrt((float)(x*x + y*y));
}

void dfs2(int idx, int cur, int* visit, int* pre, float distance)
{
    if (distance >= g_min)
        return;

    if (cur == num)
    {
        g_min = distance;
        memcpy(g_pre, pre, sizeof(g_pre));
        return;
    }

    for (int i = 0; i < num; i++)
    {
        if (!visit[i])
        {
            visit[i] = 1;
            pre[cur] = i;
            if (cur == 0)
                dfs2(i, cur+1, visit, pre, distance);
            else
                dfs2(i, cur+1, visit, pre, distance+calc_dis(idx, i));
            visit[i] = 0;
        }
    }
}

void dfs(int idx, int cur, int* visit, int* pre, int distance)
{
    if (idx >= num)
        return;

    if (distance > g_min)
        return;

    pre[cur] = idx;

    if (cur + 1 == num)
    {
        //         if (!g_min)
        g_min = distance;
        //         else
        //            g_min = min(g_min, distance);
        memcpy(g_pre, pre, sizeof(g_pre));
        return;
    }

    visit[idx] = 1;
    for (int i = 0; i < num; i++)
    {
        if (!visit[i])
        {
            dfs(i, cur+1, visit, pre, distance+calc_dis(idx, i));
        }
    }
    visit[idx] = 0;
}