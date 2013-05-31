// uva11100 贪心
// 开始想的是一次遍历，可以尽力填充一次包裹。但这样不符合每个包裹里面的数量要保证最小这个条件。
// 后来思维禁锢住，总是想着怎么怎么一次遍历，可以跳着填充包裹，就一直解决不了。
// 正确的解决方法：
// 先找出最后有几个包裹。通过相同尺寸最大数量可得知。
// 然后根据尺寸从大到小排序，不断的挨个放进这几个包裹里。


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

#define len 10000
int g_n[len];

int comp(const void* a, const void* b)
{
    return *((int*)b) - *((int*)a);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int num;
    while (scanf("%d", &num) && num)
    {
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_n[i]);
        }
        // 排序
        qsort(g_n, num, sizeof(int), comp);

        // 找出最大相同的数量
        int t=g_n[0];
        int same_num = 1;
        int same_max = 1;
        for (int i = 1; i < num; i++)
        {
            if (t == g_n[i])
                same_num++;
            else
            {
                same_max = max(same_num, same_max);
                t= g_n[i];
                same_num = 1;
            }
        }
        same_max = max(same_num, same_max);
        printf("%d\n", same_max);

        // 挨个放进包裹里
        vector<int> bags[len];
        int pos=0;
        for (int i = 0; i < num; i++)
        {
            bags[pos].push_back(g_n[i]);
            pos++;
            if (pos >= same_max)
                pos = 0;
        }

        // 输出
        for (int i = 0; i < same_max; i++)
        {
            printf("%d", bags[i][0]);
            for (int k = 1; k < bags[i].size(); k++)
            {
                printf(" %d", bags[i][k]);
            }
            printf("\n");
        }

        printf("\n");
    }

    return 0;
}