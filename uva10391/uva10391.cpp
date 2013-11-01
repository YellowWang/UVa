// uva10391 hash 
// 经典字符串哈希

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

#define len 120000
#define str_len 16
char g_d[len][str_len];

struct Node
{
    char* d;
    Node(char* d)
    {
        this->d = d;
    }
    friend bool operator<(const Node& l, const Node& r)
    {
        if (&l == &r)
            return false;

        const char* p1 = l.d;
        const char* p2 = r.d;
        while (*p1 && *p2)
        {
            if (*p1 > *p2)
                return false;
            else if (*p1 < *p2)
                return true;
            p1++;
            p2++;
        }

        if (*p2)
            return true;
        return false;
    }
};
set<Node> g_set;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int idx = 0;
    while (gets(g_d[idx]))
    {
        // 插入set
        g_set.insert(Node(g_d[idx]));
        idx++;
    }

    vector<int> vAns;
    // 对于每个单词，遍历所有拆分情况
    for (int i = 0; i < idx; i++)
    {
        int length = strlen(g_d[i]);
        for (int k = 1; k < length; k++)
        {
            char str1[str_len];
            strncpy(str1, g_d[i], k);
            str1[k]=0;
            if (g_set.count(Node(str1)) > 0 &&
                g_set.count(Node(g_d[i]+k)) > 0)
            {
                vAns.push_back(i);
                break;
            }
        }
    }

    // 输出
    for (int i = 0; i < vAns.size(); i++)
    {
        printf("%s\n", g_d[vAns[i]]);
    }

    return 0;
}