// uva10054 ̰��
// ��ʼ��ÿһ�����������������෴����ӡ��������ǳ��󣬹��ƻᳬʱ
// ��������ֻҪ����һ�ξ����ˣ�ÿ��������ۼӡ�

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

typedef long long ll;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int num;
    while (scanf("%d", &num) && num)
    {
        ll wine;
        ll total = 0;
        ll cost = 0;
        for (int i = 0; i < num; i++)
        {
            scanf("%lld", &wine);

            total += wine;
            if (total > 0)
                cost += total;
            else
                cost += -total;
        }
        printf("%lld\n", cost);
    }

    return 0;
}