// uva10602 贪心
// 每次优先选择和上个字符串相同字符多de

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

#define len 101
char g_s[len][len];
int g_visit[len];
vector<int> g_v;
int g_press_num;
void proc(int num);

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
        int num;
        scanf("%d", &num);

        for (int i = 0; i < num; i++)
        {
            scanf("%s", g_s[i]);
        }

        memset(g_visit, 0, sizeof(g_visit));

        proc(num);

        printf("%d\n", g_press_num);
        for (int i = 0; i < g_v.size(); i++)
        {
            printf("%s\n", g_s[g_v[i]]);
        }
    }


    return 0;
}

// 计算两个串相同数目
int comp(char* s1, char* s2)
{
    int lens = 0;
    while (*s1 == *s2 && *s1 && *s2)
    {
        s1++;
        s2++;
        lens++;
    }
    return lens;
}

void proc(int num)
{
    g_v.clear();

    g_visit[0] = 1;
    g_press_num = strlen(g_s[0]);
    g_v.push_back(0);

    int str_idx = 0;
    while (true)
    {
        char* str = g_s[str_idx];
        int match_len = 0;
        int match_idx = 0;
        int first_idx = 0;
        for (int i = 1; i < num; i++)
        {
            if (!g_visit[i])
            {
                if (!first_idx)
                    first_idx = i;
                int l = comp(g_s[i], str);
                if (match_len < l)
                {
                    match_len = l;
                    match_idx = i;
                }
            }
        }

        // 优先选择有共同数目的
        if (match_len)
        {
            g_visit[match_idx]=1;
            str_idx = match_idx;
            g_v.push_back(match_idx);
            g_press_num += strlen(g_s[match_idx]) - match_len;
        }
        // 都已经选择，就退出
        else if (first_idx==0)
            break;
        // 没有的话，优先选择没选择的第一个
        else
        {
            g_visit[first_idx]=1;
            str_idx = first_idx;
            g_v.push_back(first_idx);
            g_press_num += strlen(g_s[first_idx]) - match_len;
        }
    }
}