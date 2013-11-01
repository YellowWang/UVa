// uva10603 回溯
// 经典倒水问题

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;
#define len 201
#define INT_MAX 999999
int g[len][len][len];
int g_ans[len];
int g_x,g_y,g_z,g_d;
int bfs(int firstx, int firsty, int firstz, int firstpours, int& d);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        memset(g, 0, sizeof(g));
        for (int i = 0; i <= len; i++)
            g_ans[i] = INT_MAX;

        scanf("%d %d %d %d", &g_x, &g_y, &g_z, &g_d);

        int pours, d;
        pours = bfs(0, 0, g_z, 0, d);

        for (int i = g_d; i >= 0; i--)
        {
            if (g_ans[i] != INT_MAX)
            {
                printf("%d %d\n", g_ans[i], i);
                break;
            }
        }
    }

    return 0;
}

struct Node
{
    int x,y,z;
    int pours;
    Node(int x, int y, int z, int pours)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->pours = pours;
    }
};

// 从water1倒入water2，max1是water1的最大容量，left1是倒入后的剩余容量，pours是倒入多少水
bool Pour(int water1, int water2, int max1, int max2, int& left1, int& left2, int& pours)
{
    if (water1 != 0 && water2 != max2)
    {
        int water = water1;
        int left = max2 - water2;
        if (water > left)
        {
            left1 = water1 - left;
            left2 = max2;
            pours = left;
            return true;
        }
        else
        {
            left1 = 0;
            left2 = water2+water;
            pours = water;
            return true;
        }
    }
    return false;
}

int bfs(int firstx, int firsty, int firstz, int firstpours, int& d)
{
    deque<Node> q;
    q.push_back(Node(firstx, firsty, firstz, firstpours));

    while (!q.empty())
    {
        Node& node = q.front();

        // 超过目标处理
        if (node.pours < g_ans[node.x])
            g_ans[node.x] = node.pours;
        if (node.pours < g_ans[node.y])
            g_ans[node.y] = node.pours;
        if (node.pours < g_ans[node.z])
            g_ans[node.z] = node.pours;

        // 判断是否达到目标
        if (node.x == g_d || node.y == g_d || node.z == g_d)
        {
            d = g_d;
            return node.pours;
        }

        // 判断是否出现过此状况
        if (g[node.x][node.y][node.z])
        {
            q.pop_front();
            continue;
        }

        g[node.x][node.y][node.z]=1;

        // 加入下一个阶段的各种情况
        int left1, left2, pours=0;
        if (Pour(node.x, node.y, g_x, g_y, left1, left2, pours))
            if (!g[left1][left2][node.z])
                q.push_back(Node(left1, left2, node.z, node.pours+pours));
        if (Pour(node.x, node.z, g_x, g_z, left1, left2, pours))
            if (!g[left1][node.y][left2])
                q.push_back(Node(left1, node.y, left2, node.pours+pours));
        if (Pour(node.y, node.x, g_y, g_x, left1, left2, pours))
            if (!g[left2][left1][node.z])
                q.push_back(Node(left2, left1, node.z, node.pours+pours));
        if (Pour(node.y, node.z, g_y, g_z, left1, left2, pours))
            if (!g[node.x][left1][left2])
                q.push_back(Node(node.x, left1, left2, node.pours+pours));
        if (Pour(node.z, node.x, g_z, g_x, left1, left2, pours))
            if (!g[left2][node.y][left1])
                q.push_back(Node(left2, node.y, left1, node.pours+pours));
        if (Pour(node.z, node.y, g_x, g_y, left1, left2, pours))
            if (!g[node.x][left2][left1])
                q.push_back(Node(node.x, left2, left1, node.pours+pours));
        q.pop_front();
    }
}