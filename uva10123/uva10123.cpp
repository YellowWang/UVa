// uva10123.cpp : Defines the entry point for the console application.
// 剪枝策略1：优先总和最大的
// 剪枝策略2：优先总和最大，并且优先小于-1.5或大于1.5的节点。不在中间的点全部遍历仍然没有成功，那么直接减掉。
// 剪枝策略3：成功。参考http://www.cppblog.com/a542343910/archive/2012/04/04/170047.html，每次移动都是左右两边扭转力（torque）最大值，两者选一。所以规模一下子降到了O(n^2)。

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;

#define len 20
struct Pack
{
    int l;//距离
    int w;//重量
    float left1,left2,right1,right2;//中间变量
};
Pack g_pack[len];
int visit[len];
int g_res[len];
int board_length;
int board_kilo, packs;
bool search(int cur, float left1, float left2, float right1, float right2);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases = 1;
    while (scanf("%d %d %d", &board_length, &board_kilo, &packs) && board_kilo)
    {
        memset(g_pack, 0, sizeof(g_pack));
        // 计算中间变量，方便是否平衡计算
        // left1是左边支点往左的torque总和，left2是左边支点往右的torque总和。
        // right1是右边支点网左的torque总和，right2是右边支点往右的torque总和
        for (int i = 0; i < packs; i++)
        {
            scanf("%d %d", &g_pack[i].l, &g_pack[i].w);
            if (g_pack[i].l < 0)
            {
                if (g_pack[i].l < -1.5f)
                    g_pack[i].left1 = -(g_pack[i].l+1.5f)*g_pack[i].w;
                else
                    g_pack[i].left2 = (g_pack[i].l+1.5f)*g_pack[i].w;
                g_pack[i].right1 = (1.5f-g_pack[i].l)*g_pack[i].w;
            }
            else
            {
                if (g_pack[i].l > 1.5f)
                    g_pack[i].right2 = (g_pack[i].l-1.5f)*g_pack[i].w;
                else
                    g_pack[i].right1 = (1.5f-g_pack[i].l)*g_pack[i].w;
                g_pack[i].left2 = (g_pack[i].l+1.5f)*g_pack[i].w;
            }
        }

        memset(visit, 0, sizeof(visit));
        float left1=0,left2=0,right1=0,right2=0;
        for (int i = 0; i < packs; i++)
        {
            left1 += g_pack[i].left1;
            left2 += g_pack[i].left2;
            right1 += g_pack[i].right1;
            right2 += g_pack[i].right2;
        }
        // 木板torque
        left2 += 1.5f*board_kilo;
        right1 += 1.5f*board_kilo;

        // 输出
        printf("Case %d:\n", cases++);
        if (search(0, left1, left2, right1, right2))
        {
            for (int i = 0; i < packs; i++)
            {
                printf("%d %d\n", g_pack[g_res[i]].l, g_pack[g_res[i]].w);
            }
        }
        else
            printf("Impossible\n");
    }

    return 0;
}

bool search(int cur, float left1, float left2, float right1, float right2)
{
//     if (left1 > left2 || right2 > right1)
//         return false;

    if (cur == packs)
    {
        return true;
    }

    int max_idx1 = -1;
    int max_idx2 = -1;
    // torque可能计算为负数，所以需要默认最小值很小。WA原因之一
    float max_sum1 = -9999999;
    float max_sum2 = -9999999;
    // 找左边和右边的最大torque点
    for (int i = 0; i < packs; i++)
    {
        if (!visit[i])
        {
            if (g_pack[i].l > 0)
            {
                int torque = (g_pack[i].l-3)*g_pack[i].w;
                if (torque > max_sum2)
                {
                    max_sum2 = torque;
                    max_idx2 = i;
                }
            }
            else
            {
                int torque = (-3-g_pack[i].l)*g_pack[i].w;
                if (torque > max_sum1)
                {
                    max_sum1 = torque;
                    max_idx1 = i;
                }
            }
        }
    }
    bool match1 = true;
    bool match2 = true;
    // 右边是否符合
    if (max_idx1 >= 0)
    {
        if ((left1-g_pack[max_idx1].left1) > (left2-g_pack[max_idx1].left2) || 
            (right2-g_pack[max_idx1].right2) > (right1-g_pack[max_idx1].right1))
            match1 = false;
    }
    // 左边是否符合
    if (max_idx2 >= 0)
    {
        if ((left1-g_pack[max_idx2].left1) > (left2-g_pack[max_idx2].left2) || 
            (right2-g_pack[max_idx2].right2) > (right1-g_pack[max_idx2].right1))
            match2 = false;
    }
    // 都不符合，无解
    if (!match1 && !match2)
        return false;

    // 右边有解，则继续
    if (max_idx1 >= 0 && match1)
    {
        int idx = max_idx1;
        visit[idx] = 1;
        g_res[cur] = idx;
        if (search(cur+1, left1-g_pack[idx].left1, left2-g_pack[idx].left2,
            right1-g_pack[idx].right1, right2-g_pack[idx].right2))
            return true;
        visit[idx] = 0;
    }
    // 左边有解，则继续
    if (max_idx2 >= 0 && match2)
    {
        int idx = max_idx2;
        visit[idx] = 1;
        g_res[cur] = idx;
        if (search(cur+1, left1-g_pack[idx].left1, left2-g_pack[idx].left2,
            right1-g_pack[idx].right1, right2-g_pack[idx].right2))
            return true;
        visit[idx] = 0;
    }

    return false;
}