// uva10400 回溯 dfs
// 收录在刘汝佳贪心分类里，不过没有想出贪心的对策。
// 判重：判断第几步和当前的计算值作为key来判重。

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

#define len 100
#define num_max 32000
int g_n[len];
int g_visit[len][num_max*2+1];
int g_op_num;
int g_ans;
deque<int> g_q;
bool dfs(int cur, int sum, int op);

enum 
{
    e_plus,
    e_minus,
    e_mul,
    e_divide
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int cases;
    scanf("%d", &cases);

    while (cases--)
    {
        int num,ans;
        scanf("%d", &num);
        for (int i = 0 ; i < num; i++)
        {
            scanf("%d", &g_n[i]);
        }
        scanf("%d", &g_ans);

        g_op_num = num-1;
        memset(g_visit, 0, sizeof(g_visit));
        g_q.clear();
        if (dfs(0, g_n[0], e_plus))
        {
            printf("%d", g_n[0]);
            for (int i = 0; i < g_q.size(); i++)
            {
                if (g_q[i] == e_plus)
                    printf("+");
                else if (g_q[i] == e_minus)
                    printf("-");
                if (g_q[i] == e_mul)
                    printf("*");
                if (g_q[i] == e_divide)
                    printf("/");
                printf("%d", g_n[i+1]);
            }
            printf("=%d\n", g_ans);
        }
        else
            printf("NO EXPRESSION\n");
    }

    return 0;
}

bool dfs(int cur, int sum, int op)
{
    if (sum < -num_max || sum > num_max)
    {
        return false;
    }

    if (cur == g_op_num)
    {
        if (sum == g_ans)
            return true;
        return false;
    }

    if (g_visit[cur][sum+num_max])
        return false;
    g_visit[cur][sum+num_max] = 1;

    if (dfs(cur+1, sum+g_n[cur+1], e_plus))
    {
        g_q.push_front(e_plus);
        return true;
    }

    if (dfs(cur+1, sum-g_n[cur+1], e_minus))
    {
        g_q.push_front(e_minus);
        return true;
    }

    if (dfs(cur+1, sum*g_n[cur+1], e_mul))
    {
        g_q.push_front(e_mul);
        return true;
    }

    if (sum % g_n[cur+1] == 0)
    {
        if (dfs(cur+1, sum/g_n[cur+1], e_divide))
        {
            g_q.push_front(e_divide);
            return true;
        }
    }

    return false;
}