// uva105
// 还算是稍微简单的题。感觉有很多解法，最初为了减少不必要的操作，想的很复杂。
// 最后干脆直接建立一个很长的地平线line，所有楼房都映射到这个line上，line存着重叠楼房的最大高度。最后输出所有结果。
// 题目没有明确说明line有多长，所以还是风险的。还好最后ac了。

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

// 以为len很大的话会超时，不过测试数据没有很变态，就ac了
#define len 100000
int line[len];

int main()
{
    //freopen("1.txt", "r", stdin);

    memset(line, 0, sizeof(line));
    int x,y,h;
    while (scanf("%d %d %d", &x, &h, &y)!=EOF)
    {
        for (int i = x; i <= y; i++)
        {
            line[i] = max(line[i], h);
        }
    }

    // 输出，为了一行最后一个没有多余空格，所以代码复杂了一些
    int start = 0;
    for (int i = 0; i < len; i++)
    {
        if (line[i] > 0)
        {
            printf("%d %d", i, line[i]);
            start = i;
            break;
        }
    }
    bool join = true;
    int pre = line[start];
    for (int i = start; i < len; i++)
    {
        if (join && line[i] == pre)
        {
            continue;
        }
        else if (join && line[i] != pre && line[i] > 0)
        {
            if (line[i] > pre)
                printf(" %d %d", i, line[i]);
            else
                printf(" %d %d", i-1, line[i]);
            //join = false;
            pre = line[i];
        }
        else if (join && line[i]==0)
        {
            printf(" %d %d", i-1, 0);
            join = false;
        }
        else if (!join && line[i] > 0)
        {
            printf(" %d %d", i, line[i]);
            pre = line[i];
            join = true;
        }
    }

    printf("\n");
    return 0;
}