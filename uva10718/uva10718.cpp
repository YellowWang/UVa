// uva10718 ̰��
// �е��Ѷȡ�����N���Ӹ�λ����λ�������1������ʹMΪ0�������0������ʹMΪ1.
// �ο�http://m80126colin.blog.fc2.com/blog-entry-35.html
// 

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

    ll N,L,U;
    while (scanf("%lld %lld %lld", &N, &L, &U)!=EOF)
    {
        ll ans = 0;
        ll t = 0;
        for (ll i = 31; i >= 0; i--)
        {
            // ���Ϊ1������ѡ0
            if (((N>>i) & 0x01) == 1)
            {
                t = (ans|((1ll<<i)-1));
                // ���Ϊ0�Ļ�����С��L����ô�ͱ���ѡ��1.
                if (t < L)
                    ans = (ans|((1ll<<i)));
            }
            // ���Ϊ0������ѡ1
            else
            {
                t = (ans|(1ll<<i));
                // ���Ϊ1�Ļ��������U����ô��ѡ��0��
                // ���С��U����ô��ѡ��1��
                if (t <= U)
                    ans = t;
            }
        }

        printf("%lld\n", ans);
    }

    return 0;
}