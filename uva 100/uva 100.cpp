// uva 100
// ע�����⣬��һ��i�ͱ�j��
// ��ʼ���100w�����ֵ�cycleȫ�����棬

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
using namespace std;

int main()
{
    //ifstream cin("1.txt");

    long int i,j;
    long int m,n;
    while (cin >> i >> j)
    {
        if (i > j)
        {
            m = j;
            n = i;
        }
        else
        {
            m = i;
            n = j;
        }
        int max = 0;
        for (;m <= n; m++)
        {
            int times = 1;
            int n = m;
            while (n!=1)
            {
                if (n%2==1)
                    n = n+n+n+1;
                else
                    n = n/2;
                ++times;
            }
            if (times > max)
                max = times;
        }
        printf("%d %d %d\n",i ,j ,max);
    }

    return 0;
}