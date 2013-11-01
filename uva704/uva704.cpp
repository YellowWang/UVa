// uva704 双向bfs
// 双向各8次，满足题目要求，步数小于等于16次

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

#define len 24
int g_final_state[len];
deque<int> g_qMove;
deque<int> g_qMove_reverse;
//正向bfs
bool bfs(int first_state[len]);
//反向bfs。保存当前状态和步骤。
bool bfs_reverse(int first_state[len]);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    freopen("2.txt","w",stdout);
#endif

    set<int> ss;
    ss.insert(99);
    ss.count(99);
    ss.count(88);
    ss.count(100);
    // 最终状态
    int final_state[len] = {
        0,3,4,3,0,5,6,5,0,1,2,1,0,7,8,7,0,9,10,9,0,1,2,1
    };
    memcpy(g_final_state, final_state, sizeof(g_final_state));
    // 先进行反向的bfs，因为是不变的。
    bfs_reverse(g_final_state);
    // 反向转为正向的旋转方法
    int rot_reverse[5]={0,3,4,1,2};

    int data[len];
    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        for (int i = 0; i < len; i++)
        {
            scanf("%d", &data[i]);
        }

        if (bfs(data))
        {
            if (g_qMove.size() > 0 || g_qMove_reverse.size() > 0)
            {
                for (int i = 0; i < g_qMove.size(); i++)
                {
                    printf("%d", g_qMove[i]);
                }
                // 反向结果需要反向输出
                for (int i = g_qMove_reverse.size()-1; i >= 0; i--)
                {
                    printf("%d", rot_reverse[g_qMove_reverse[i]]);
                }
                printf("\n");
            }
            else
                printf("PUZZLE ALREADY SOLVED\n");
        }
        else
        {
            printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
        }
    }

    return 0;
}


struct Node
{
    int state[len]; // 状态
    long long sum1,sum2; // 中间值
    deque<int> qMove; // 步骤
    // stl set需要
    friend bool operator<(const Node& lhs, const Node& rhs)
    {
        if (&lhs == &rhs)
            return false;
        if (lhs.sum1 < rhs.sum1)
        {
            return true;
        }
        else if (lhs.sum1 == rhs.sum1 && lhs.sum2 < rhs.sum2)
        {
            return true;
        }
        return false;
    }
    // 方便比较
    void calc()
    {
        sum1 = 0;
        sum2 = 0;
        for (int i = 0; i < 12; i++)
        {
            sum1 += state[i]<<(4*i);
            sum2 += state[i+12]<<(4*i);
        }
    }
    Node(){qMove.clear();}
    Node(int state[len], deque<int> qMove)
    {
        this->qMove = qMove;
        for (int i = 0; i < len; i++)
            this->state[i] = state[i];
        calc();
    }
};
set<Node> g_set;
set<Node> g_set_reverse;

// 旋转处理
void rotate(int rot_type, int in_state[len], int out_state[len])
{
    int half_len = len>>1;
    if (rot_type == 1)
    {
        memcpy(out_state+2, in_state, sizeof(int)*(half_len-2));
        memcpy(out_state, in_state+(half_len-2), sizeof(int)*2);
        memcpy(out_state+len-3, out_state+(half_len-3), sizeof(int)*3);
    }
    else if (rot_type == 2)
    {
        memcpy(out_state+half_len, in_state+half_len+2, sizeof(int)*(half_len-2));
        memcpy(out_state+len-2, in_state+half_len, sizeof(int)*2);
        memcpy(out_state+(half_len-3), out_state+len-3, sizeof(int)*3);
    }
    else if (rot_type == 3)
    {
        memcpy(out_state, in_state+2, sizeof(int)*(half_len-2));
        memcpy(out_state+half_len-2, in_state, sizeof(int)*2);
        memcpy(out_state+len-3, out_state+(half_len-3), sizeof(int)*3);
    }
    else
    {
        memcpy(out_state+half_len+2, in_state+half_len, sizeof(int)*(half_len-2));
        memcpy(out_state+half_len, in_state+len-2, sizeof(int)*2);
        memcpy(out_state+(half_len-3), out_state+len-3, sizeof(int)*3);
    }
}

bool bfs(int first_state[len])
{
    g_set.clear();
    g_qMove.clear();
    deque<Node> q;
    q.push_back(Node(first_state, g_qMove));

    while (!q.empty())
    {
        Node& node = q.front();

        // 是否检测过
        if (g_set.count(node))
        {
            q.pop_front();
            continue;
        }
        g_set.insert(node);

        // 是否到终点
        if (memcmp(g_final_state, node.state, len*4) == 0)
        {
            g_qMove = node.qMove;
            return true;
        }

        // 反向结果是否有
        set<Node>::iterator it = g_set_reverse.find(node);
        if (it != g_set_reverse.end())
        {
            g_qMove = node.qMove;
            g_qMove_reverse = (*it).qMove;
            return true;
        }

        // 是否到达8次
        if (node.qMove.size() >= 8)
        { 
            q.pop_front();
            continue;
        }

        // 遍历所有情况
        Node new_node;
        for (int i = 1; i <= 4; i++)
        {
            new_node = node;
            new_node.qMove.push_back(i);
            rotate(i, node.state, new_node.state);
            new_node.calc();
            if (!g_set.count(new_node))
                q.push_back(new_node);
        }

        q.pop_front();
    }

    return false;
}

bool bfs_reverse(int first_state[len])
{
    g_set_reverse.clear();
    g_qMove_reverse.clear();
    deque<Node> q;
    q.push_back(Node(first_state, g_qMove_reverse));

    while (!q.empty())
    {
        Node& node = q.front();
        int qsize = q.size();

        // 是否检测过
        if (g_set_reverse.count(node))
        {
            q.pop_front();
            continue;
        }
        g_set_reverse.insert(node);

        // 是否到达8次
        if (node.qMove.size() >= 8)
        {
            q.pop_front();
            continue;
        }

        // 遍历所有情况
        Node new_node;
        for (int i = 1; i <= 4; i++)
        {
            new_node = node;
            new_node.qMove.push_back(i);
            rotate(i, node.state, new_node.state);
            new_node.calc();
            if (!g_set_reverse.count(new_node))
                q.push_back(new_node);
        }

        q.pop_front();
    }
    return true;
}