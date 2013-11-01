// uva10167 暴力
// 不假思索的暴力

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

#define len 51
struct node
{
    int x,y;
};

node d[len];
bool half(int a, int b, int n);

int main()
{
    //freopen("1.txt", "r", stdin);

    int n;
    while (scanf("%d",&n) && n)
    {
        memset(d, 0, sizeof(d));

        for (int i = 0; i < 2*n; i++)
        {
            scanf("%d %d", &d[i].x, &d[i].y);
        }

        bool match=false;
        int ans_a,ans_b;
        for (int a = -500; a <= 500; a++)
        {
            for (int b = -500; b <= 500; b++)
            {
                if (half(a, b, n))
                {
                    match=true;
                    ans_a = a;
                    ans_b = b;
                    break;
                }
            }
            if (match)
                break;
        }

        printf("%d %d\n", ans_a, ans_b);
    }

    return 0;
}

bool half(int a, int b, int n)
{
    int left=0,right=0;
    int h = n*2;
    for (int i = 0; i < h; i++)
    {
        int res = d[i].x * a + d[i].y * b;
        if (res == 0)
            return false;
        if (res > 0)
        {
            ++right;
            if (right > n)
                return false;
        }
        else
        {
            ++left;
            if (right > n)
                return false;
        }
    }

    return (left == right) && (left == n);
}