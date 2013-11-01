// uva10487 贪心
// 网上基本都是优先计算所有总和+二分查找。
// 这里是一个贪心算法。先从小到大排序，然后计算首个和末尾的和，如果大于目标，末尾指针向前移动一个；否则，首指针向后移动一个；
// 耗时O(n)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory.h>
using namespace std;

int query_sum_min3(int in_query, int* d, int n);
int cmp(const void* a,const void* b)
{
    return *((int*)(a)) > *((int*)(b));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int input_num = 0;
    int input_data[1000];

    int case_num = 1;
    while (scanf("%d",&input_num)  && input_num)
    {
        memset(input_data, 0, sizeof(input_data));
        for (int i = 0; i < input_num; i++)
        {
            scanf("%d", &input_data[i]);
        }

        qsort(input_data, input_num, sizeof(int), cmp);

        int input_qnum = 0;
        int input_query = 0;

        printf("Case %d:\n", case_num++);
        scanf("%d", &input_qnum);
        while (input_qnum--)
        {
            scanf("%d", &input_query);
            printf("Closest sum to %d is %d.\n", input_query, query_sum_min3(input_query, input_data, input_num));
        }

    }

    return 0;
}

int query_sum_min3(int in_query, int* d, int n)
{
    if (n == 1)
    {
        return d[0];
    }

    int near_sum = d[0]+d[1];
    int l = 0;
    int u = n-1;
    while (l < u)
    {
        int sum = d[l]+d[u];
        if (sum == in_query)
        {
            return in_query;
        }

        if (abs(sum-in_query) < abs(near_sum-in_query))
        {
            near_sum = sum;
        }

        if (sum < in_query)
        {
            l++;
        }
        else
        {
            u--;
        }
    }

    return near_sum;
}