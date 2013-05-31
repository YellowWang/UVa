// uva11129 贪心 二分
// 详细
// 题意：要求不能含有3个或3个以上的等差数列。中间隔着其它数字也不允许。
// 二分举例：例如6。
// 把偶数项和奇数项分为两堆。结果：0 2 4 和 1 3 5.
// 把 0 2 4继续分为偶数奇数两堆。结果：0 4 和 2。0 4输出为4 0, 2 直接输出。
// 把 1 3 5继续分为偶数奇数两堆。结果：1 5 和 3.输出为5 1 3.
// 总输出为：4 0 2 5 1 3.
// 总结：对一个有序序列，不断奇偶二分，剩下2个或1个的时候就输出结果。

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
void binary_proc(int start_i, int num, int inter);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    for (int i = 0; i < len; i++)
    {
        g_n[i] = i;
    }

    int num;
    while (scanf("%d", &num) && num)
    {
        printf("%d:", num);
        binary_proc(0, num, 1);
        printf("\n");
    }

    return 0;
}

void binary_proc(int start_i, int num, int inter)
{
    if (num <= 0)
        return;
    if (num == 1)
    {
        printf(" %d", g_n[start_i]);
        return;
    }
    if (num == 2)
    {
        printf(" %d %d", g_n[start_i+inter], g_n[start_i]);
        return;
    }

    if (num & 0x01)
        binary_proc(start_i, (num>>1)+1, inter<<1);
    else
        binary_proc(start_i, num>>1, inter<<1);

    binary_proc(start_i+inter, num>>1, inter<<1);
}