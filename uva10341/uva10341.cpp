// uva10341 二分
// 枚举0.0f-1.0f,步进单位0.0001f，共10000个数。
// 函数的单调减的，所以可以用二分法。
// 详解参考：http://www.algorithmist.com/index.php/UVa_10341

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

int p,q,r,s,t,u;
double calc(double x)
{
    double res = p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*x*x+u;
    return res;
}
double binary_proc(double l, double r);
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    while (scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u)!=EOF)
    {
        // 首先判断曲线是否在[0,1]段有交点
        if (calc(0) < 0.0f || calc(1) > 0.0f)
            printf("No solution\n");
        else
            printf("%0.4lf\n", binary_proc(0, 1));
    }

    return 0;
}

double binary_proc(double l, double r)
{
    while (l + 0.0000001f < r)
    {
        double m = (l+r)/2;
        double res = calc(m);
        if (res >= 0.0f)
            l = m;
        else
            r = m;
    }
    return (l+r)/2;
}