// uva 442
// 耗时0.08s ，最快0s
// 栈的用法

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;


struct node
{
    int x;
    int y;
    int sum; // x*y ，保存重复计算的值
};

// 因为题目说是26个大写字母，所以用这个数组来保存
#define len 26
node input[len];

// 字符串的长度
#define len_str 256
char a[len_str];

int main()
{
    //ifstream cin("1.txt");

    //读入数据
    int num = 0;
    cin >> num;

    char c;
    for (int i = 0; i < num; i++)
    {
        cin >> c;
        cin >> input[c-'A'].x >> input[c-'A'].y;
        input[c-'A'].sum = input[c-'A'].x * input[c-'A'].y;
    }

    //用栈来运算
    int si = 0; // 栈顶位置
    node st[len_str];//只保存每个矩阵的数据
    while (cin >> a)
    {
        // 如果只有一个元素，直接返回0
        if (a[0] != '(')
        {
            cout << 0 << endl;
            continue;;
        }

        int total = 0;// 记录所有计算次数
        char* p = a;
        si = 0;
        while (*p)
        {
            if (*p == ')')
            {
                // 计算
                int tsi = si-2;
                // 矩阵不匹配，就输出error
                if (st[tsi].y != st[tsi+1].x)
                {
                    cout << "error" << endl;
                    break;
                }


                total += st[tsi].sum * st[tsi+1].y;
                // 将结果保存在栈顶
                st[tsi].sum = st[tsi].x * st[tsi+1].y;
                st[tsi].x = st[tsi].x;
                st[tsi].y = st[tsi+1].y;

                // 所有都计算完成
                if (tsi == 0 && *(p+1) == 0)
                {
                    cout << total << endl;
                    break;
                }

                // 设置栈顶
                si = tsi+1;
                p++;
                continue;
            }

            // 设置栈数据
            if (*p != '(' && *p != ')')
            {
                st[si].x = input[*p-'A'].x;
                st[si].y = input[*p-'A'].y;
                st[si].sum = input[*p-'A'].sum;
                si++;
            }
            p++;
        }
    }

    return 0;
}