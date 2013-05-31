// uva10132 贪心
// 最长的和最短的进行匹配，然后遍历剩余串是否符合
// 注意格式

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

#define str_len 260
#define file_len 144

char g_d[file_len<<1][str_len];
int visit[file_len<<1];
int g_num;
void proc();
bool match(char* match_str);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int cases;
    char in_str[str_len];
    gets(in_str);
    cases = atoi(in_str);
    // blank line
    gets(in_str);

    while (cases--)
    {
        g_num = 0;
        while (gets(g_d[g_num]) && g_d[g_num][0] != 0)
        {
            g_num++;
        }

        // 
        proc();
        if (cases)
            printf("\n");
    }

    return 0;
}

int comp(const void* a, const void* b)
{
    return strlen((char*)a) - strlen((char*)b);
}

void proc()
{
    // 排序
    qsort(g_d[0], g_num, str_len, comp);
    // 最长的开始找
    char* max_str = g_d[g_num-1];
    //visit[g_num-1]=1;
    int min_len = strlen(g_d[0]);

    // 匹配最短的所有串
    int idx=0;
    char match_str[str_len];
    while (min_len == strlen(g_d[idx]))
    {
        //visit[idx]=1;
        // 余下的是否匹配
        strcpy(match_str, max_str);
        strcat(match_str, g_d[idx]);
        if (match(match_str))
        {
            printf("%s\n", match_str);
            break;
        }

        // 反向生成，并判断余下的是否匹配
        strcpy(match_str, g_d[idx]);
        strcat(match_str, max_str);
        if (match(match_str))
        {
            printf("%s\n", match_str);
            break;
         }
        idx++;
        //visit[idx]=0;
    }


}

bool match(char* match_str)
{
    int match_len = strlen(match_str);
    // 每个串是否满足其它的
    char match_str2[str_len];
    bool match_found = true;
    for (int i = 0; i < (g_num>>1); i++)
    {
        memset(visit, 0, sizeof(visit));
        int len1 = strlen(g_d[i]);
        int len2 = match_len - len1;
        bool found = false;
        for (int k = g_num-1; k >= (g_num>>1); k--)
        {
            if (!visit[k])
            {
                int templen = strlen(g_d[k]);
                if (len2 == templen)
                {
                    visit[k] = 1;
                    strcpy(match_str2, g_d[i]);
                    strcat(match_str2, g_d[k]);
                    if (strcmp(match_str, match_str2)==0)
                    {
                        found = true;
                        break;
                    }

                    // 反过来再来一遍
                    strcpy(match_str2, g_d[k]);
                    strcat(match_str2, g_d[i]);
                    if (strcmp(match_str, match_str2)==0)
                    {
                        found = true;
                        break;
                    }
                }
                else if (templen < len2)
                    break;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}