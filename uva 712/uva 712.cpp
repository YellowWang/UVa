// uva 712
// 耗时0.012s

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

#define len 130

char d[len];

int order[len];

int order_idx[len]; //保存x1等位置的索引

int g_data[8]; // 保存每层的数量

int main()
{
    //ifstream cin("1.txt");

    g_data[0] = 1;
    g_data[1] = 2;
    g_data[2] = 4;
    g_data[3] = 8;
    g_data[4] = 16;
    g_data[5] = 32;
    g_data[6] = 64;
    g_data[7] = 128;


    int input_num;
    char sx[16];
    int caseidx = 0;
    while (cin >> input_num && input_num)
    {
        caseidx++;
        int orderi = 0;
        while (input_num--)
        {
            cin >> sx;
            order_idx[atoi(sx+1)] = orderi++;
        }
        cin >> d;

        cout << "S-Tree #" << caseidx << ":" << endl;

        cin >> input_num;
        while (input_num--)
        {
            cin >> sx;

            char* p = sx;
            int idx = 1;
            int layer = orderi-1;
            while (*p) // 根据x1、x2等值，计算一个最后一层（叶子节点）的索引
            {
                int pos = order_idx[idx];
                order[pos] = (*p-'0') * g_data[layer--];
                idx++;
                p++;
            }
            int sum = 0;
            for (int i = 0; i < orderi; i++)
            {
                sum += order[i];
            }
            cout << d[sum]; // 直接索引到计算的位置
        }
        cout << endl << endl;
    }

    return 0;
}