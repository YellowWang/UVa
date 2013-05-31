// uva10700 贪心
// 注意数字很大，所以用long long

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

typedef long long ll;
#define len 128
void proc(char* str, ll& minimum, ll& maximum);

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
        char str[len];
        scanf("%s", str);

        ll minimum, maximum;
        proc(str, minimum, maximum);

        printf("The maximum and minimum are %lld and %lld.\n", maximum, minimum);
    }

    return 0;
}

ll prior_mul(char*& p)
{
    char str_num[len];
    ll sum = 1;
    ll i=0;
    while (1)
    {
        if (*p < '0' || *p > '9')
        {
            str_num[i]=0;
            sum *= atoi(str_num);
            i = 0;

            if (*p == '+' || *p == 0)
                return sum;
            p++;
            continue;
        }
        str_num[i++] = *p;
        p++;
    }
    return 0;
}

ll prior_plus(char*& p)
{
    char str_num[len];
    ll sum = 0;
    ll i=0;
    while (1)
    {
        if (*p < '0' || *p > '9')
        {
            str_num[i]=0;
            sum += atoi(str_num);
            i = 0;

            if (*p == '*' || *p == 0)
                return sum;
            p++;
            continue;
        }
        str_num[i++] = *p;
        p++;
    }
    return 0;
}

void proc(char* str, ll& minimum, ll& maximum)
{
    char* p = str;

    // 优先乘法
    minimum = 0;
    while (*p)
    {
        minimum += prior_mul(p);
        if (*p == 0)
            break;
        p++;
    }

    // 优先加法
    p = str;
    maximum = 1;
    while (*p)
    {
        maximum *= prior_plus(p);
        if (*p == 0)
            break;
        p++;
    }
}