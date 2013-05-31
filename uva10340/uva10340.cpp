// uva10340 简单题
// 注意字符串大小要很大，不然会re。只怪题目没有说明。

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

#define len 102400

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    char str1[len], str2[len];
    while (scanf("%s %s", str1, str2) != EOF)
    {
        char* p1 = str1;
        char* p2 = str2;

        while (*p1)
        {
            while (*p2 != *p1 && *p2)
            {
                p2++;
            }
            if (*p2 == 0)
            {
                printf("No\n");
                break;
            }
            p1++;
            p2++;
        }
        if (*p1 == 0)
            printf("Yes\n");
    }


    return 0;
}