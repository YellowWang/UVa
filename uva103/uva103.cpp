// uva103 dp DAG
// ����󣬾Ϳ��Խ���DAG�����Բο����㷨���š�������Ѱ棩9.2.1
 
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
 
#define box_len 30
#define di_len 10
int g_boxes[box_len][di_len];//�洢ÿ��box������
int g_m[box_len][box_len];//DAG
int g_visit[box_len];//�����Ƿ����
int g_f[box_len];//�����Ѿ�����õ�ֵ�������ظ�����
int g_road[box_len];//����·��
int g_box_num, dimension_num;
void proc();
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    while (scanf("%d %d", &g_box_num, &dimension_num)!=EOF)
    {
        // ����
        for (int i = 0; i < g_box_num; i++)
        {
            for (int k = 0; k < dimension_num; k++)
            {
                scanf("%d", &g_boxes[i][k]);
            }
        }
 
        proc();
    }
 
    return 0;
}
 
int comp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}
 
// ����i��box���·��
int dp(int i)
{
    if (g_visit[i])
        return g_f[i];
 
    int ans = 1;
    int ans_i = -1;
    for (int k = 0; k < g_box_num; k++)
    {
        if (g_m[k][i])
        {
            int t = dp(k)+1;
            if (ans < t)
            {
                ans = t;
                ans_i = k;
            }
        }
    }
 
    g_visit[i] = 1;
    g_f[i] = ans;
    g_road[i] = ans_i;
    return ans;
}
 
void proc()
{
    memset(g_m, 0, sizeof(g_m));
    memset(g_visit, 0, sizeof(g_visit));
    memset(g_f, 0, sizeof(g_f));
    memset(g_road, -1, sizeof(g_road));
 
 
    // ����
    for (int i = 0; i < g_box_num; i++)
    {
        qsort(g_boxes[i], dimension_num, sizeof(int), comp);
    }
 
    // �������Ƕ��
    for (int i = 0; i < g_box_num; i++)
    {
        for (int k = 0; k < g_box_num; k++)
        {
            if (i == k)
                continue;
 
            bool matched = true;
            for (int di = 0; di < dimension_num; di++)
            {
                if (g_boxes[i][di] >= g_boxes[k][di])
                {
                    matched = false;
                    break;
                }
            }
            if (matched)
                g_m[i][k]=1;
        }
    }
 
    // �����·��
    int max_road = 0;
    int max_road_i = 0;
    for (int i = 0; i < g_box_num; i++)
    {
        int t = dp(i);
        if (max_road < t)
        {
            max_road = t;
            max_road_i = i;
        }
    }
 
    // ���
    deque<int> v;
    v.push_front(max_road_i);
    int road_i = max_road_i;
    for (int i = 1; i < max_road; i++)
    {
        v.push_front(g_road[road_i]);
        road_i = g_road[road_i];
    }
    printf("%d\n", max_road);
    printf("%d", v[0]+1);
    for (int i = 1; i < v.size(); i++)
    {
        printf(" %d", v[i]+1);
    }
    printf("\n");
}