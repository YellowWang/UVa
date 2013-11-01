// uva10422 回溯、暴力
// 八数码问题变种，注意骑士走‘日’字

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

#define INT_MAX 99999999
#define len 5
char g[len][len];
char g_final[len][len];
typedef long long ll;
set<ll> g_set;
bool bfs(char arr[len][len], int blankx, int blanky, int moves);
int g_min;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    //init global data
    char final[len][len] = {
        {'1','1','1','1','1'},
        {'0','1','1','1','1'},
        {'0','0',' ','1','1'},
        {'0','0','0','0','1'},
        {'0','0','0','0','0'}
    };
    memcpy(g_final, final, sizeof(g_final));

    int cases;
    scanf("%d\n", &cases);
    while (cases--)
    {
        int x,y;
        char str[len+1];
        for (int i = 0; i < len; i++)
        {
            gets(str);
            memcpy(g[i], str, sizeof(str));
            for (int k = 0; k < len; k++)
            {
                if (g[i][k] == ' ')
                {
                    x = i;
                    y = k;
                }
            }
        }

         if (bfs(g, x, y, 0))
         {
             printf("Solvable in %d move(s).\n", g_min);
         }
         else
             printf("Unsolvable in less than 11 move(s).\n");

    }

    return 0;
}

struct Node
{
    char arr[len][len];
    int x,y;
    int moves;
    Node(char arr[len][len], int x, int y, int moves)
    {
        memcpy(this->arr, arr, sizeof(this->arr));
        this->x = x;
        this->y = y;
        this->moves = moves;
    }
};

bool is_visit_insert(char arr[len][len])
{
    ll sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum *= 100;
        for (int k = 0; k < len; k++)
        {
            if (arr[i][k] == '1')
                sum+= (1<<k)*2;
            else if (arr[i][k] == '0')
                sum+= (1<<k)*1;
            else
                sum+=0;
        }
    }

    if (g_set.count(sum) > 0)
        return true;

    g_set.insert(sum);
    return false;
}

bool is_visit(char arr[len][len])
{
    ll sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum *= 100;
        for (int k = 0; k < len; k++)
        {
            if (arr[i][k] == '1')
                sum+= (1<<k)*2;
            else if (arr[i][k] == '0')
                sum+= (1<<k)*1;
            else
                sum+=0;
        }
    }

    if (g_set.count(sum) > 0)
        return true;

    return false;
}

bool bfs(char arr[len][len], int blankx, int blanky, int moves)
{
    g_set.clear();
    g_min = INT_MAX;
    int dir[] = {-1,-2, -2,-1, -2,1, -1,2, 2,1, 1,2, 2,-1, 1,-2};

    deque<Node> q;
    q.push_back(Node(arr, blankx, blanky, moves));

    while (!q.empty())
    {
        Node& node = q.front();

        // 是否到终点
        if (memcmp(node.arr, g_final, sizeof(g_final))==0)
        {
            g_min = node.moves;
            return true;
        }

        // 是否达到10
        if (node.moves >= 10)
        {
            q.pop_front();
            continue;
        }

        // 状态是否走过
        if (is_visit_insert(node.arr))
        {
            q.pop_front();
            continue;
        }

        // 遍历所有状态
        for (int i = 0; i < 8; i++)
        {
            int newx = node.x + dir[i*2];
            int newy = node.y + dir[i*2+1];
            if (newx >= 0 && newx < len && newy >= 0 && newy < len)
            {
                // 移动一格
                int t = node.arr[newx][newy];
                node.arr[newx][newy] = node.arr[node.x][node.y];
                node.arr[node.x][node.y] = t;
                if (!is_visit(node.arr))
                {
                    q.push_back(Node(node.arr, newx, newy, node.moves+1));
                }
                // 还原
                t = node.arr[newx][newy];
                node.arr[newx][newy] = node.arr[node.x][node.y];
                node.arr[node.x][node.y] = t;
            }
        }

        q.pop_front();
    }

    return false;
}