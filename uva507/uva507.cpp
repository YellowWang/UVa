// uva507 贪心
// 最大连续子串和。特殊要求：1，和相同，匹配更长串；

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

#define len 20000
int g_n[len];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    freopen("2.txt","w",stdout);
#endif

    int cases;
    scanf("%d", &cases);
    for (int icase = 0; icase < cases; icase++)
    {
        int s;
        scanf("%d", &s);
        for (int i = 1; i < s; i++)
        {
            scanf("%d", &g_n[i]);
        }

        int sum_front= 0;
        int front_1 = 0, front_2 = 0;
        int sum_back = 0;
        int back_1 = 0, back_2 = 0;
        // 为当和相同，并匹配最长串准备
        int max_val = 0, max_1=0, max_2=0;
        for (int i = 1; i < s; i++)
        {
            sum_back += g_n[i];
            back_2 = i;
            if (sum_front <= sum_back)
            {
                sum_front = sum_back;
                front_1 = back_1;
                front_2 = back_2;
                if (sum_front == max_val && (front_2-front_1) > (max_2-max_1))
                {
                    max_1 = front_1;
                    max_2 = front_2;
                }
                else if (sum_front > max_val)
                {
                    max_val = sum_front;
                    max_1 = front_1;
                    max_2 = front_2;
                }
            }
            else if (sum_back < 0)
            {
                sum_back = 0;  
                back_1 = i;
            }
        }

        if (front_2)
            printf("The nicest part of route %d is between stops %d and %d\n",
                icase+1, max_1+1, max_2+1);
        else
            printf("Route %d has no nice parts\n", icase+1);
    }

    return 0;
}