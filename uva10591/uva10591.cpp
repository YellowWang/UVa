// uva10591 hash
// 简单题

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
#include <map>
using namespace std;

#define len 10
int g_d[len];
map<int, int> g_m;
bool proc(int num);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    freopen("2.txt","w",stdout);
#endif

    for (int i = 0; i <= 9; i++)
    {
        g_d[i]=i*i;
    }

    int cases;
    scanf("%d", &cases);
    for (int i = 0; i < cases; i++)
    {
        int num;
        scanf("%d", &num);
        if (proc(num))
        {
            printf("Case #%d: %d is a Happy number.\n",i+1, num);
        }
        else
            printf("Case #%d: %d is an Unhappy number.\n",i+1, num);
    }

    return 0;
}

bool proc(int num)
{
    int n = num;
    vector<int> v;
    map<int , int> m_un;
    while (n)
    {
        m_un[n]=1;
        // 是否有重复,最后到1
        if (g_m.find(n) != g_m.end())
        {
            if (g_m[n] == 1)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    g_m[v[i]] = n;
                }
                return true;
            }
        }

        // 累加
        int sum = 0;
        while (n)
        {
            sum += g_d[n%10];
            n = n / 10;
        }
        n = sum;
        // 如果是一位数1，退出
        if (n == 1)
        {
            for (int i = 0; i < v.size(); i++)
            {
                g_m[v[i]] = n;
            }
            return true;
        }
        // 如果是出现重复，退出
        if (m_un.find(n) != m_un.end())
        {
            return false;
        }
        v.push_back(n);
    }
}