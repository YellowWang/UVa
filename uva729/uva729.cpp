// uva729 枚举子集
// 直接套用枚举子集函数，没有进行更一步优化。能过了就行。

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

// 枚举子集函数
void collection(int start, int idx, int num, int max, int* p);

#define len 17
int d[len];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        int num,max;
        scanf("%d %d", &max, &num);
        collection(0, 0, max-num, max, d);
        if (cases != 0)
            printf("\n");
    }

    return 0;
}

void collection(int start, int idx, int num, int max, int* p)
{
    if (idx == num)
    {
        int ans[len];
        for (int i = 0; i < max; i++)
            ans[i]=1;
        for (int i = 0; i < num; i++)
            ans[p[i]] = 0;
        for (int i = 0; i < max; i++)
            printf("%d", ans[i]);
        printf("\n");
        return;
    }

    for (int i = start; i < max; i++)
    {
        p[idx] = i;
        collection(i+1, idx+1, num, max, p);
    }

}