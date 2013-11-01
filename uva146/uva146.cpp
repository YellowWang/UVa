// uva146 下一个个排列
// 简单题，找规律

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

#define len 51

int comp(const void* a, const void* b)
{
    return *((char*)a) > *((char*)b);
}

int main()
{
    //freopen("1.txt", "r", stdin);

    char d[len];

    while (scanf("%s", d)!=EOF && d[0] != '#')
    {

        int l = strlen(d);
        // 找到后面字母大于前面字母的点
        int start = -1;
        for (int i = l-1; i > 0; i--)
        {
            if (d[i] > d[i-1])
            {
                start = i-1;
                break;
            }
        }
        if (start == -1)
        {
            printf("No Successor\n");
            continue;
        }
        // 找到后面刚大于前面字母的字母
        int replace = -1;
        for (int i = l-1; i > start; i--)
        {
            if (d[i] > d[start])
            {
                replace = i;
                break;
            }
        }
        // 后面的排序
        char t = d[start];
        d[start] = d[replace];
        d[replace] = t;
        qsort(&d[start+1], l-start-1, sizeof(char), comp);

        printf("%s\n", d);
    }

    return 0;
}