// uva 10050
// 主要在找出不同party的hartal之间的联系和规律
// 耗时0.008s，最快0s

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

#define  len 3650
int d[len]; // 每一天是否是罢工的日子

int main()
{
    //ifstream cin("1.txt");

    // 题目不能有7的倍数，所以计算了1到6.
    // 每个数累加自身7次，又回到对应的星期，也就是一个循环
    // 0代表不能计算罢工（因为周五、周六算休假）。1算罢工
    // 例如h=1，分别对应星期 7,1,2,3,4,5,6（从周日算起）
    int h[6][7] = {
        {1,1,1,1,1,0,0},
        {1,1,0,1,1,1,0},
        {1,0,1,1,1,1,0},
        {1,1,1,1,0,1,0},
        {1,1,1,0,1,1,0},
        {0,1,1,1,1,1,0}
    }; 

    int cases = 0;
    cin >> cases;
    while (cases--)
    {
        memset(d, 0, sizeof(d));// 清空
        int days = 0;
        cin >> days;

        int p = 0;
        cin >> p;
        // 设置每个party的罢工日子
        int input= 0;
        for (int i = 0; i < p; ++i)
        {
            cin >> input;
            int base = input % 7;
            int cur = input;
            int base_idx = 0;
            while (cur <= days)
            {
                d[cur-1] = h[base-1][base_idx++];
                if (base_idx >= 7)
                    base_idx = 0;
                cur += input;
            }
        }

        // 累加所有罢工日子
        int sum = 0;
        for (int i = 0; i < len; ++i)
        {
            if (d[i])
                ++sum;
        }

        // 输出
        cout << sum << endl;
    }

    return 0;
}