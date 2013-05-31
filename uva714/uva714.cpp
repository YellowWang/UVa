// uva714 贪心 分治
// 经典

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

typedef long long ll;
#define len 500
int g_n[len];
vector<int> g_split;
void proc(int num, int k, ll r);

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
        int num,k;
        scanf("%d %d", &num, &k);
        ll sum = 0;
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_n[i]);
            sum += g_n[i];
        }

        proc(num, k, sum);

        // 输出，注意格式
        for (int i = 0; i < num-1; i++)
        {
            printf("%d ", g_n[i]);
            for (int j = 0; j < g_split.size(); j++)
            {
                if (i == g_split[j])
                {
                    printf("/ ");
                    break;
                }
            }
        }
        if (num > 0)
            printf("%d", g_n[num-1]);
        printf("\n");
    }

    return 0;
}

// 每个人的任务不能超过m。
int match_min3(int num, int k, ll m, ll& minimum, vector<int>& split)
{
    int j = num-1;
    minimum = 0;
    // 遍历所有人
    for (int i = k-1; i >= 0; i--)
    {
        ll sum = 0;
        // 根据题意，说如果有多个可能，那么第一个人的任务要最小。
        // 那么任务从右往左，尽可能给右边的人放最多的任务。
        while (j >= i)
        {
            if (sum + g_n[j] > m)
                break;
            sum += g_n[j];
            j--;
        }
        if (i > 0)
            split.push_back(j);
        if (i == 0 && j >= 0) // 还有书，但是人满了
            return 2;
        if (sum > minimum) // 找到最大的人任务量
            minimum = sum;
    }
    if (minimum == m)
        return 0;
    else if (minimum > m)
        return 2;
    else
        return 1;
}

void proc(int num, int k, ll r)
{
    ll l,m;
    l = 0;
    // 二分，从0到上限（所有页数和）
    while (l + 1 < r)
    {
        m = (l+r)>>1;

        vector<int> split;
        ll minimum;
        // 猜数字。看m是否符合题目要求
        int match_state = match_min3(num, k, m, minimum, split);
        if (match_state == 0)
        {
            g_split = split;
            return;
        }
        else if (match_state == 1)
            r = m;
        else
            l = m;
    }
    return;
}