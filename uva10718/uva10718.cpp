// uva10718 贪心
// 有点难度。根据N，从高位到低位。如果是1，尽量使M为0；如果是0，尽量使M为1.
// 参考http://m80126colin.blog.fc2.com/blog-entry-35.html
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
            // 如果为1，尽量选0
            if (((N>>i) & 0x01) == 1)
            {
                t = (ans|((1ll<<i)-1));
                // 如果为0的话，会小于L，那么就必须选择1.
                if (t < L)
                    ans = (ans|((1ll<<i)));
            }
            // 如果为0，尽量选1
            else
            {
                t = (ans|(1ll<<i));
                // 如果为1的话，会大于U，那么就选择0；
                // 如果小于U，那么就选择1；
                if (t <= U)
                    ans = t;
            }
        }

        printf("%lld\n", ans);
    }

    return 0;
}