// uva10714 贪心
// 找规律。
// 最小时间：找到距离中间点最近的蚂蚁，它距离两端的最小距离就是答案。
// 最大时间：设蚂蚁初始位置为x1，x2...xn，len为pole的长度。两只蚂蚁的时候，有两种情况，时间分别为x2和len-x1。只要比较两个时间，最大的为答案。
// 三只蚂蚁的时候，我们可以继续推断出，时间可能为len-x1、x2、x3（其它情况没有相遇，不予考虑）。发现仍需要比较len-x1和x3.所以找到最左边和最右边的蚂蚁即可。

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
        int x_mid=0,x_left=0,x_right=0;
        int pole_len, num;
        scanf("%d %d", &pole_len, &num);
        x_left = pole_len;
        int mid = pole_len >> 1;
        for (int i = 0; i < num; i++)
        {
            int n;
            scanf("%d", &n);
            // 找到最左蚂蚁
            if (n < x_left)
                x_left = n;
            // 找到最右蚂蚁
            if (n > x_right)
                x_right = n;
            // 找到最中间蚂蚁
            if (abs(n-mid) < abs(x_mid-mid))
                x_mid = n;
        }

        printf("%d %d\n", x_mid>mid?pole_len-x_mid:x_mid, 
            (pole_len-x_left)>x_right?pole_len-x_left:x_right);
    }

    return 0;
}